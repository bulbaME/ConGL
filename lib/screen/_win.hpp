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

            GetConsoleScreenBufferInfo(sHandler, &screenInfo);
            scrSize = screenInfo.dwSize;
            pixelC = scrSize.X * scrSize.Y;

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
        void clear();
        // return screen buffer
        const wchar_t* getScreen();

        // set proper colors in terminal
        void initConsoleColors();

        // get output handler
        const HANDLE getHandler() { return sHandler; }

        // sets font
        void setFont(COORD size);

    private:
        HANDLE sHandler;
        CONSOLE_SCREEN_BUFFER_INFO screenInfo;
        COORD scrSize;
        size_t pixelC;

        wchar_t* screen;
        DWORD dWritten;

        void setupScreen();
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
    WriteConsoleOutputCharacterW(sHandler, screen, pixelC, {0, 0}, &dWritten);
    if (autoClear) clear();
}

void WinScreen::clear() {
    std::fill_n(screen, pixelC, L' ');
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

// void WinScreen::initConsoleColors() {
//     HKEY hKey;
//     long nError = RegOpenKeyExA(HKEY_CURRENT_USER, "Console", 0, KEY_WRITE, &hKey)

//     DWORD color = 252;
//     RegSetValueExA(hKey, "ScreenColors", 0, REG_DWORD, &color , sizeof(color))
// }

#endif