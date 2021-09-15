#ifndef SCREEN_API
#define SCREEN_API

    #ifdef _WIN32
    #include "_win.hpp"
    using Screen = WinScreen;
    #endif

    #ifdef linux
    #include "_unix.hpp"
    using Screen = UnixScreen;
    #endif

#endif