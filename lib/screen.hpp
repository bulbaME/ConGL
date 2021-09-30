#ifndef SCREEN_API
#define SCREEN_API

    #ifdef _WIN32
    #include "screen/_win.hpp"
    using Screen = WinScreen;

    namespace keys {
        bool down(char key) {
            return -GetAsyncKeyState(key) == 0x8000;
        }

        bool up(char key) {
            return -GetAsyncKeyState(key) == 0x7FFF;
        }
    }

    #else 
    #include "screen/_unix.hpp"
    using Screen = UnixScreen;
    #endif

#endif