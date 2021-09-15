#ifndef _WIN_SCREEN_API
#define _WIN_SCREEN_API

#include <windows.h>
#include <algorithm>
#include <stdio.h>

class WinScreen {
    public:
        // create new console buffer instead of using default
        WinScreen() : sHandler(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)) {
            SetConsoleActiveScreenBuffer(sHandler);
            setupFont();

            GetConsoleScreenBufferInfo(sHandler, &screenInfo);
            scrSize = screenInfo.dwSize;
            scrSize.Y = 20;
            pixelC = scrSize.X * scrSize.Y;

            setupScreen();
        }

        ~WinScreen() {
            delete [] screen;
        }

        // unsafe setPX
        inline void setPX(COORD coord, char c);
        // safe setPX
        void setPX_s(COORD coord, char c);

        COORD getSize() { return scrSize; }

        // draw screen
        void draw(bool autoClear);
        // clear screen
        void clear();

    private:
        const HANDLE sHandler;
        CONSOLE_SCREEN_BUFFER_INFO screenInfo, oldScreenInfo;
        COORD scrSize;
        size_t pixelC;

        char * screen;
        DWORD dWritten;

        void setupFont();
        void setupScreen();
};

void WinScreen::setPX (COORD coord, char c) {
    screen[coord.Y * scrSize.X + coord.X] = c;
}

void WinScreen::setPX_s (COORD coord, char c) {
    if (coord.X >= 0 && coord.X < scrSize.X && coord.Y >= 0 && coord.Y < scrSize.Y) {
        screen[coord.Y * scrSize.X + coord.X] = c;
    } else throw "Screen buffer index error";
}

void WinScreen::draw(bool autoClear = true) {
    WriteConsoleOutputCharacter(sHandler, screen, pixelC, {0, 0}, &dWritten);
    if (autoClear) clear();
}

void WinScreen::clear() {
    for (size_t c = 0; c < pixelC; ++c) { 
        screen[c] = ' ';
    }
}

// set screen font
void WinScreen::setupFont() {
    CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
    info.dwFontSize = {5, 10};

    SetCurrentConsoleFontEx(sHandler, false, &info);
}

// create screen buffer
void WinScreen::setupScreen() {
    screen = new char[pixelC]();
}


#endif