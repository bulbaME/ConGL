#include "../congl.h"
namespace ConGL {

// CONSTRUCTORS

WinScreen::WinScreen(HANDLE handler) {
    sHandler = handler;
    resizeScreen();
}

WinScreen::WinScreen(bool newHandler, bool setCurrent) : WinScreen(newHandler ? 
    CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) : GetStdHandle(STD_OUTPUT_HANDLE)
) { if (setCurrent) SetConsoleActiveScreenBuffer(sHandler); }

WinScreen::~WinScreen() {
    screenBuff.clear();
}


// PUBLIC METHODS

void WinScreen::setCurrentHandler(HANDLE handler) {
    SetConsoleActiveScreenBuffer(handler);
}

COORD WinScreen::getSize() { return sSize; }

void WinScreen::setSurfaceSize(COORD size) { 
    dSize = size; 
    autoCalcD = true;

    if (dSize.X < sSize.X) forceScrSize({dSize.X, sSize.Y});
    if (dSize.Y < sSize.Y) forceScrSize({sSize.X, dSize.Y});
    
    calcdOffset();
}

std::vector<PIXEL>::const_iterator WinScreen::getScreen() { return screenBuff.cbegin(); }

void WinScreen::forceScrSize(COORD size) { 
    SetConsoleScreenBufferSize(sHandler, size); 
    sSize = size;
}

const HANDLE WinScreen::getHandler() { return sHandler; }

void WinScreen::setFpsLimit(int fps) { frameTime = 1.0f / fps * 1000; }

void WinScreen::autosizeToggle(bool state) { autoSize = state; }

void WinScreen::metaToggle(bool state) { showMeta = state; }

void WinScreen::setPX_s(PIXEL px) {
    if (px.pos.X >= 0 && px.pos.X < dSize.X && px.pos.Y >= 0 && px.pos.Y < dSize.Y && px.pos.X < sSize.X && px.pos.Y < sSize.Y) {
        screenBuff.push_back(PIXEL({short (px.pos.X + dOff.X), short (px.pos.Y + dOff.Y)}, px.ch, px.col));
    }
}

void WinScreen::flushScreen() {
    wchar_t blank[1] = { L' ' };
    for (PIXEL& c : oldScreenBuff) {
        SetConsoleTextAttribute(sHandler, colors::BG::BLACK | colors::FG::WHITE);
        WriteConsoleOutputCharacterW(sHandler, blank, 1, c.pos, &written);
    }
}

void WinScreen::draw(bool autoClear = true) {
    _render(autoClear);
    if (autoSize) resizeScreen();
}

void WinScreen::setFont(COORD size) {
    CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
    info.dwFontSize = size;
    info.FontWeight = FW_EXTRALIGHT;
    info.FontFamily = FF_DONTCARE;

    SetCurrentConsoleFontEx(sHandler, false, &info);
}


// PRIVATE METHODS

void WinScreen::_render(bool flush) {    
    // FRAME TIME

    // FIXME: fails to get correct time (sometimes frame time is absolute 0) 
    t2 = std::chrono::system_clock::now();
    tdiff = t2 - t1;
    t1 = t2;
    double curr_tdiff = tdiff.count();

    // FIXME: Sleep function not working as expected 
    // FIXME: only working value is 50 fps, but not actual 50 fps 
    if (frameTime) {
        Sleep(frameTime / 2);
        // int waitTime = frameTime - curr_tdiff * 1000;
        // avgWait += waitTime + frameTime / 4;
        // if (avgWait > 0) {
        //     Sleep(avgWait);
        // }
    }
    
    // displays metadata
    if (showMeta) {
        // average framerate
        int frame = curr_tdiff > 0 ? 1.0f / curr_tdiff : fps;
        fps = fps - fps / 50 + frame / 50;

        std::string metadata;

        metadata += std::string() + "[" + std::to_string(fps) + "]";
        const char* cmetadata = metadata.c_str(); 

        // display in top right corner
        short min = sSize.X > metadata.size() ? metadata.size() : sSize.X;
        short shift = sSize.X - min;
        for (short m = 0; m < min; ++m)
            screenBuff.push_back(PIXEL({short (m + shift), 0}, (wchar_t) cmetadata[shift], colors::FG::WHITE));
    }

    // clearing screen before new frame
    if (flush) flushScreen();

    // RENDERING
    wchar_t curr[1];
    for (PIXEL& c : screenBuff) {
        curr[0] = c.ch;

        // FIXME 
        SetConsoleTextAttribute(sHandler, c.col);                           // FIX: colors not working 
        WriteConsoleOutputCharacterW(sHandler, curr, 1, c.pos, &written);   // FIX: overwriting current output 
    }

    oldScreenBuff = screenBuff;
    screenBuff.clear();
}

void WinScreen::resizeScreen() {
    GetConsoleScreenBufferInfo(sHandler, &screenInfo);
    if (screenInfo.dwSize.X == sSize.X && screenInfo.dwSize.Y == sSize.Y) return;
    sSize = screenInfo.dwSize;
    pixelC = sSize.X * sSize.Y;
    if (autoCalcD) calcdOffset();
    else dSize = sSize;
}

void WinScreen::calcdOffset() {
    short x = (sSize.X - dSize.X) / 2;
    short y = (sSize.Y - dSize.Y) / 2;
    dOff = { short (x > 0 ? x : 0), short (y > 0 ? y : 0) };
}
}