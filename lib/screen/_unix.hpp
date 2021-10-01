#ifndef _UNIX_SCREEN_API
#define _UNIX_SCREEN_API

struct COORD {
    short X, Y;
};

class UnixScreen {
    public: 
        UnixScreen() {
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &screenInfo);
            scrSize = { (short) screenInfo.ws_col, (short) screenInfo.ws_row };
            pixelC = scrSize.X * scrSize.Y;
            setupScreen();
        }

        ~UnixScreen() {
            delete [] screen;
            clearCon();
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
    
    private:
        COORD scrSize;
        size_t pixelC;
        winsize screenInfo;

        wchar_t* screen;

        void setupScreen();
        void setupFont();
        void clearCon();
};

void UnixScreen::setPX(COORD coord, wchar_t c) {
    screen[coord.Y * scrSize.X + coord.X] = c;
}

void UnixScreen::setPX_s(COORD coord, wchar_t c) {
    if (coord.X >= 0 && coord.X < scrSize.X && coord.Y >= 0 && coord.Y < scrSize.Y) {
        screen[coord.Y * scrSize.X + coord.X] = c;
    };
}

void UnixScreen::draw(bool autoClear = true) {
    clearCon();
    wprintf(L"\n");
    wprintf(screen);
    if (autoClear) clear();
}

void UnixScreen::clear() {
    std::fill_n(screen, pixelC, L' ');
}

void UnixScreen::clearCon() {
    wprintf(L"\033[0;0H");
    std::system("clear");
}

void UnixScreen::setupScreen() {
    screen = new wchar_t[pixelC]();
}

//TODO: font size
void UnixScreen::setupFont() {

}

#endif