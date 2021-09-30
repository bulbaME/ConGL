#ifndef _WIN_SCREEN_API
#define _WIN_SCREEN_API

// sets current output handler
void setCurrentHandler(HANDLE handler) {
    SetConsoleActiveScreenBuffer(handler);
}

class WinScreen {
    public:
        WinScreen() = default;

        WinScreen(HANDLE handler) {
            sHandler = handler;
            resizeScreen();
            setupScreen();
        }

        WinScreen(bool newHandler, bool setCurrent = true) : WinScreen(newHandler ? 
            CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) : GetStdHandle(STD_OUTPUT_HANDLE)
        ) { if (setCurrent) SetConsoleActiveScreenBuffer(sHandler); }

        ~WinScreen() {
            delete [] screen;
        }

        // unsafe setPX ; better use setPX_s
        inline void setPX(COORD coord, wchar_t c);
        // safe setPX
        void setPX_s(COORD coord, wchar_t c);

        // return console screen size
        COORD getSize() { return scrSize; }


        // draw screen
        void draw(bool autoClear);
        // clear screen
        inline void clear();
        // return screen buffer
        const wchar_t* getScreen();

        // set proper colors in terminal
        void initConsoleColors();

        // get output handler
        const HANDLE getHandler() { return sHandler; }

        // sets font
        void setFont(COORD size);

        void setFpsLimit(int fps) { frameTime = 1.0f / fps / 0.9 * 1000; }

        // current fps
        int fps = 0;

        // toggle resizing automaticly 
        void autosizeToggle(bool state) { autoSize = state; }

        // toggle metadata
        void metaToggle(bool state) { showMeta = state; }

    private:
        HANDLE sHandler;
        CONSOLE_SCREEN_BUFFER_INFO screenInfo;
        COORD scrSize;
        size_t pixelC;
        bool showMeta = false;
        bool autoSize = false;

        wchar_t* screen;
        DWORD dWritten;

        void setupScreen();
        void resizeScreen();

        // time
        int frameTime = 0, avgWait = 0;  // in milliseconds
        std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now(), t2 = std::chrono::system_clock::now();
        std::chrono::duration<double> tdiff;
};

void WinScreen::setPX(COORD coord, wchar_t c) {
    screen[coord.Y * scrSize.X + coord.X] = c;
}

void WinScreen::setPX_s(COORD coord, wchar_t c) {
    if (coord.X >= 0 && coord.X < scrSize.X && coord.Y >= 0 && coord.Y < scrSize.Y) {
        screen[coord.Y * scrSize.X + coord.X] = c;
    };
}

void WinScreen::draw(bool autoClear = true) {    
    // FIXME: fails to get correct time 
    // calculate frame time
    t2 = std::chrono::system_clock::now();
    tdiff = t2 - t1;
    t1 = t2;
    double curr_tdiff = tdiff.count();

    // FIXME: Sleep function not working as expected 
    if (frameTime) {
        int waitTime = frameTime - curr_tdiff * 1000;
        avgWait += waitTime;
        if (avgWait > 0) {
            Sleep(avgWait);
        }
    }
    
    // displays metadata
    if (showMeta) {
        // average framerate
        int frame = curr_tdiff > 0 ? 1.0f / curr_tdiff : fps;
        fps = fps - fps / 50 + frame / 50;

        std::string metadata = std::string() + "[" + std::to_string(fps) + "]";
        const char* cmetadata = metadata.c_str(); 

        short min = scrSize.X > metadata.size() ? metadata.size() : scrSize.X;
        short shift = scrSize.X - min;
        for (short m = 0; m < min; ++m) {
            screen[m + shift] = (wchar_t) cmetadata[m];
        }
    }

    WriteConsoleOutputCharacterW(sHandler, screen, pixelC, {0, 0}, &dWritten);
    if (autoSize) resizeScreen();
    if (autoClear) clear();
}

void WinScreen::resizeScreen() {
    GetConsoleScreenBufferInfo(sHandler, &screenInfo);
    if (screenInfo.dwSize.X == scrSize.X && screenInfo.dwSize.Y == scrSize.Y) return;
    scrSize = screenInfo.dwSize;
    pixelC = scrSize.X * scrSize.Y;
    setupScreen();
}

void WinScreen::clear() {
    for(int p = 0; p < pixelC; ++p) screen[p] = L' ';
}

const wchar_t* WinScreen::getScreen() {
    return screen;
}

// set screen font
void WinScreen::setFont(COORD size) {
    CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
    info.dwFontSize = size;
    info.FontWeight = FW_DEMIBOLD;
    info.FontFamily = FF_DECORATIVE;

    SetCurrentConsoleFontEx(sHandler, false, &info);
}

// create screen buffer
void WinScreen::setupScreen() {
    screen = new wchar_t[pixelC]();
}

#endif