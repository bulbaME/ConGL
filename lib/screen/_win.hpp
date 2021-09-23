#ifndef _WIN_SCREEN_API
#define _WIN_SCREEN_API

#include <windows.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>

// sets current output handler
void setCurrentHandler(HANDLE handler) {
    SetConsoleActiveScreenBuffer(handler);
}

class WinScreen {
    public:
        WinScreen() = default;

        WinScreen(HANDLE handler) {
            sHandler = handler;
            setupFont();

            GetConsoleScreenBufferInfo(sHandler, &screenInfo);
            scrSize = screenInfo.dwSize;
            pixelC = scrSize.X * scrSize.Y;

            setupScreen();
        }

        WinScreen(bool newHandler) : WinScreen(newHandler ? 
            CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) : GetStdHandle(STD_OUTPUT_HANDLE)
        ) {};

        ~WinScreen() {
            delete [] screen;
        }

        WinScreen operator=(WinScreen other);

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

    private:
        HANDLE sHandler;
        CONSOLE_SCREEN_BUFFER_INFO screenInfo, oldScreenInfo;
        COORD scrSize;
        size_t pixelC;

        wchar_t* screen;
        DWORD dWritten;

        void setupFont();
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

const wchar_t * WinScreen::getScreen() {
    return screen;
}

// set screen font
void WinScreen::setupFont() {
    CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
    info.dwFontSize = {10, 10};
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