#include "../congl.h"
namespace ConGL {
    
// CONSTRUCTORS

WinCon::WinCon(HANDLE handler) {
    sHandler = handler;
    resizeScreen();
}

WinCon::WinCon(bool newHandler, bool setCurrent) : WinCon(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)) { 
    if (setCurrent) SetConsoleActiveScreenBuffer(sHandler); 
}

WinCon::~WinCon() {
    frameBuff.clear();
    delete [] screenBuffP;
    delete [] frameBuffP;
}


// PUBLIC METHODS

void WinCon::setCurrentHandler(HANDLE handler) {
    SetConsoleActiveScreenBuffer(handler);
}

COORD WinCon::getSize() { return sSize; }

void WinCon::setSurfaceSize(COORD size) { 
    dSize = size; 
    autoCalcD = true;

    if (dSize.X < sSize.X) forceScrSize({dSize.X, sSize.Y});
    if (dSize.Y < sSize.Y) forceScrSize({sSize.X, dSize.Y});
    
    calcdOffset();
}

PIXEL* WinCon::getScreen() { return screenBuffP; }

void WinCon::forceScrSize(COORD size) { 
    SetConsoleScreenBufferSize(sHandler, size); 
    sSize = size;
}

const HANDLE WinCon::getHandler() { return sHandler; }

void WinCon::setFpsLimit(int fps) { frameTime = 1.0f / fps * 1000; }

void WinCon::autosizeToggle(bool state) { autoSize = state; }

void WinCon::metaToggle(bool state) { showMeta = state; }

void WinCon::setPX_s(PIXEL px) {
    if (px.pos.X >= 0 && px.pos.X < dSize.X && px.pos.Y >= 0 && px.pos.Y < dSize.Y && px.pos.X < sSize.X && px.pos.Y < sSize.Y) {
        px.pos = {short (px.pos.X + dOff.X), short (px.pos.Y + dOff.Y)};
        size_t pos = px.pos.X + px.pos.Y * sSize.X;
        PIXEL* oldPx = screenBuffP + pos;

        frameBuffP[pos] = px;
        if (oldPx->col != px.col || oldPx->ch != px.ch) {
            *oldPx = px;
            frameBuff.push_back(px);
        }
    }
}

PIXEL WinCon::getPX(COORD pos) { return frameBuffP[pos.X + pos.Y * sSize.X]; }

void WinCon::flushScreen() {
    wchar_t* blankBuff = new wchar_t[pixelC];
    std::fill_n(blankBuff, pixelC, L' ');

    SetConsoleCursorPosition(sHandler, {0, 0});
    SetConsoleTextAttribute(sHandler, colors::BG_BLACK | colors::FG_WHITE);
    WriteConsoleW(sHandler, blankBuff, pixelC, &written, buff_res);
}

void WinCon::draw(bool autoClear = true) {

    if (renderDone) {
        renderDone = false;
        renderThreadFunc(autoClear);
        if (autoSize) resizeScreen();
    }

    // clearing buffers
    std::fill_n(frameBuffP, pixelC, PIXEL());
    frameBuff.clear();
}

void WinCon::setFont(COORD size) {
    CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
    info.dwFontSize = size;
    info.FontWeight = FW_EXTRALIGHT;
    info.FontFamily = FF_DONTCARE;

    SetCurrentConsoleFontEx(sHandler, false, &info);
}


// PRIVATE METHODS

void WinCon::initScr() {
    delete [] screenBuffP;
    delete [] frameBuffP;
    screenBuffP = new PIXEL[pixelC];
    frameBuffP = new PIXEL[pixelC];
    std::fill_n(screenBuffP, pixelC, PIXEL());
    std::fill_n(frameBuffP, pixelC, PIXEL());
}

void WinCon::resizeScreen() {
    GetConsoleScreenBufferInfo(sHandler, &screenInfo);
    if (screenInfo.dwSize.X == sSize.X && screenInfo.dwSize.Y == sSize.Y) return;
    sSize = screenInfo.dwSize;
    pixelC = sSize.X * sSize.Y;
    if (autoCalcD) calcdOffset();
    else dSize = sSize;

    flushScreen();
    initScr();
}

void WinCon::calcdOffset() {
    short x = (sSize.X - dSize.X) / 2;
    short y = (sSize.Y - dSize.Y) / 2;
    dOff = { short (x > 0 ? x : 0), short (y > 0 ? y : 0) };
}


// RENDERING

void WinCon::_render(WinCon* t) {
    try {

    // FRAME TIME

    // FIXME: fails to get correct time (sometimes frame time is absolute 0) 
    t->t2 = std::chrono::system_clock::now();
    t->tdiff = t->t2 - t->t1;
    t->t1 = t->t2;
    double curr_tdiff = t->tdiff.count();

    // FIXME: Sleep function not working as expected 
    // only working value is 50 fps, but not actual 50 fps 

    if (t->frameTime) {
        Sleep(t->frameTime / 2);
        // int waitTime = frameTime - curr_tdiff * 1000;
        // avgWait += waitTime + frameTime / 4;
        // if (avgWait > 0) {
        //     Sleep(avgWait);
        // }
    }

    // displays metadata
    if (t->showMeta) {
        // average framerate
        int frame = curr_tdiff > 0 ? 1.0f / curr_tdiff : t->fps;
        t->fps = t->fps - t->fps / 50 + frame / 50;

        std::string metadata;

        metadata += std::string() + "[" + std::to_string(t->fps) + "]";
        const char* cmetadata = metadata.c_str(); 

        // display in top right corner
        short min = t->sSize.X > metadata.size() ? metadata.size() : t->sSize.X;
        short shift = t->sSize.X - min;
        for (short m = 0; m < min; ++m)
            t->tempFrameBuff.push_back(PIXEL({short (m + shift), 0}, (wchar_t) cmetadata[shift], colors::FG_WHITE));
    }

    // RENDERING
    wchar_t curr[1];
    for (PIXEL& c : t->tempFrameBuff) {
        curr[0] = c.ch;
        t->screenBuffP[c.pos.X + c.pos.Y * t->sSize.X] = c;

        SetConsoleCursorPosition(t->sHandler, c.pos);
        SetConsoleTextAttribute(t->sHandler, c.col);
        WriteConsoleW(t->sHandler, curr, 1, &(t->written), t->buff_res);
    }

    t->renderDone = true;

    } catch (...) {}
}

// calls render thread
void WinCon::renderThreadFunc(bool autoClear) {
    // updating pixels that weren't drawn 
    PIXEL *p1 = frameBuffP, *p2 = screenBuffP;
    COORD pos;
    if (autoClear) for (size_t c = 0; c < pixelC; ++c) {
        pos = {short (c % sSize.X), short (c / sSize.X)};

        // remove pixels from previous renders
        if (p1->ch != p2->ch || p1->col != p2->col) {
            frameBuff.push_back(PIXEL(pos));
            screenBuffP[c] = PIXEL();
        }

        ++p1, ++p2;
    } 

    tempFrameBuff = frameBuff;

    // // launching new thread
    std::thread renderThread(_render, this);
    renderThread.detach();
}

}