

//--------------------- (c) BULBA 2021 -------------------------//
//                                                              //
//        /$$$$$$                       /$$$$$$  /$$            //
//       /$$__  $$                     /$$__  $$| $$            //
//      | $$  \__/  /$$$$$$  /$$$$$$$ | $$  \__/| $$            //
//      | $$       /$$__  $$| $$__  $$| $$ /$$$$| $$            //
//      | $$      | $$  \ $$| $$  \ $$| $$|_  $$| $$            //
//      | $$    $$| $$  | $$| $$  | $$| $$  \ $$| $$            //
//      |  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$$      //
//       \______/  \______/ |__/  |__/ \______/ |________/      //
//                                                              //
//--------------------------------------------------------------//


#ifndef CONGL
#define CONGL

#include <math.h>
#include <fstream>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include <bitset>
#include <tuple>

#define PI 3.14159

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <wchar.h>
#include <unistd.h>
struct COORD {
    short X, Y;
};

using DWORD = unsigned long;

// colors

#define FOREGROUND_BLUE 0x0001
#define FOREGROUND_GREEN 0x0002
#define FOREGROUND_RED 0x0004
#define FOREGROUND_INTENSITY 0x0008

#define BACKGROUND_BLUE 0x0010
#define BACKGROUND_GREEN 0x0020
#define BACKGROUND_RED 0x0040
#define BACKGROUND_INTENSITY 0x0080

#define COMMON_LVB_UNDERSCORE 0x8000
#endif

namespace ConGL {
    using COLOR = DWORD;
}

// colors 
namespace ConGL::colors {
    // foreground colors
    constexpr COLOR FG_RED = FOREGROUND_RED;
    constexpr COLOR FG_GREEN = FOREGROUND_GREEN;
    constexpr COLOR FG_BLUE = FOREGROUND_BLUE;
    constexpr COLOR FG_BLACK = 0x0000;
    constexpr COLOR FG_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    constexpr COLOR FG_INTENSE = FOREGROUND_INTENSITY;

    // background colors
    constexpr COLOR BG_RED = BACKGROUND_RED;
    constexpr COLOR BG_GREEN = BACKGROUND_GREEN;
    constexpr COLOR BG_BLUE = BACKGROUND_BLUE;
    constexpr COLOR BG_BLACK = 0x0000;
    constexpr COLOR BG_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    constexpr COLOR BG_INTENSE = BACKGROUND_INTENSITY;

    constexpr COLOR UNDERSCORE = COMMON_LVB_UNDERSCORE;
}

namespace ConGL {
    // full filled block
    constexpr wchar_t W_FF_BLOCK = L'???';
    // half filled block
    constexpr wchar_t W_HF_BLOCK = L'???';
    // quad filled block
    constexpr wchar_t W_QF_BLOCK = L'???';

    // pixel object
    struct PIXEL {
        PIXEL() = default;
        PIXEL(wchar_t);
        PIXEL(COLOR);
        PIXEL(wchar_t, COLOR);
        PIXEL(COORD, wchar_t, COLOR);
        PIXEL(COORD);

        COORD pos = {0, 0};
        wchar_t ch = L' ';
        COLOR col = colors::FG_WHITE;
    };

    struct KEY_STATE {
        bool operator==(KEY_STATE&) const;

        wchar_t key;
        bool released = false;
        DWORD ctrlState = 0;
    };

    using InputCallback = void (*)(KEY_STATE);

    namespace keys {
        // if key is down
        bool down(char key);
        // if key was released
        bool released(char key);

        constexpr DWORD CAPS_ON = 0x0080;
        constexpr DWORD ALT_LEFT = 0x0002;
        constexpr DWORD ALT_RIGHT = 0x0001;
        constexpr DWORD CTRL_LEFT = 0x0008;
        constexpr DWORD CTRL_RIGHT = 0x0004;
        constexpr DWORD SHIFT = 0x0010;
    }
}

#ifdef _WIN32 
namespace ConGL {

    // SCREEN

    class WinCon {
    public:
        WinCon() = default;

        WinCon(HANDLE);

        WinCon(bool, bool);

        ~WinCon();

        static void setCurrentHandler(HANDLE);

        // unsafe setPX ; better use setPX_s
        inline void setPX(PIXEL);
        // safe setPX
        void setPX_s(PIXEL);
        PIXEL getPX(COORD);

        // return console screen size
        COORD getSize();
        // set size of the surface that is being drawn
        void setSurfaceSize(COORD);

        COORD getSurfaceSize() { return dSize; }

        // draw screen
        void draw(bool autoClear);
        // clear screen
        void flushScreen();
        // return screen buffer
        PIXEL* getScreen();

        // set screen buffer size
        void forceScrSize(COORD);

        // get output handler
        const HANDLE getHandler();

        // set font size
        void setFont(COORD);

        // set fps limit
        void setFpsLimit(int);

        // current fps
        int fps = 0;

        // toggle resizing automaticly
        void autosizeToggle(bool);

        // toggle metadata
        void metaToggle(bool);

        HANDLE sHandler;
        CONSOLE_SCREEN_BUFFER_INFO screenInfo;
        COORD sSize;  // screen size
        size_t pixelC;  // count of all pixels on the screen
        bool showMeta = false;
        bool autoSize = false;

        std::vector<PIXEL> frameBuff;  // current frame changed pixels
        PIXEL* frameBuffP = nullptr;  // current frame changed pixels
        PIXEL* screenBuffP = nullptr;  // screen buffer

        std::vector<PIXEL> tempFrameBuff;
        bool renderDone = true;

        void resizeScreen();
        static void _render(WinCon*);
        void renderThreadFunc(bool);
        void initScr();

        COORD dOff = {0, 0};  // offset of surface size
        COORD dSize;  // surface size
        bool autoCalcD = false;
        void calcdOffset();
        DWORD written;
        void* buff_res;
        bool resized = false;

        bool threaded = true;

        // time
        int frameTime = 0, avgWait = 0;  // in milliseconds
        std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now(), t2 = std::chrono::system_clock::now();
        std::chrono::duration<double> tdiff;
    };

    using HScreen = WinCon;


    // INPUT
    
    struct WinInput {
        WinInput(HANDLE);
        ~WinInput();

        HANDLE h;
        std::map<KEY_STATE, InputCallback> binds;
        bool loopTh = true;

        static void _thread(WinInput*);
    };

    using HInput = WinInput;
}

#ifndef BIN_LINK
#include "lib/console_win.cpp"
#include "lib/input_win.cpp"
#endif // BIN_LINK
#else
namespace ConGL {
    // TODO: UnixScreen 
    class UnixScreen {

    };

    class UnixInput {

    };

    using HScreen = UnixScreen;
}

#ifndef BIN_LINK
#include "lib/screen_unix.cpp"
#endif // BIN_LINK
#endif

namespace ConGL {

    // SCREEN

    class Screen {
    public:
        Screen();
        ~Screen();

        // set pixel to a specific position
        void setPX(PIXEL);
        // get pixel from a specific position
        PIXEL getPX(COORD);
        // returns screen size
        COORD getScrSize();
        // set surface size
        void setSurfaceSize(COORD);
        // returns surface size
        COORD getSurfaceSize();

        // render screen
        void render();
        // clears screen
        void flush();
        
        // toggle auto screen resizing
        void toggleAutosize(bool);
        // toggle meta data
        void toggleMeta(bool);

        // set font size
        void setFont(COORD);

        void _setFpsLimit(int);

        // returns current fps 
        int getFps();

        // get main screen object
        HScreen* _getHScreen();
    
    private:
        HScreen* hs;
    };


    // INPUT

    class Input {
    public:
        Input(Screen*);
    
        // bind a callback for key press event
        void bind(KEY_STATE, InputCallback);
        // remove bind
        void unbind(KEY_STATE);

        HInput* _getHInput();
    private:
        HInput* hi;
    };
}

namespace ConGL::eng2D::txr {
    struct Texture {
        Texture();
        Texture(std::string path);
        ~Texture();

        // set texture through arrays of pixels
        template <short X, short Y> 
        void setProper(PIXEL _data[Y][X]);

        // set texture through arrays of characters
        template <short X, short Y> 
        void setProper(wchar_t _data[Y][X], COLOR fill = colors::FG_WHITE);

        Texture operator=(const Texture&);

        PIXEL** data = nullptr;
        COORD size = {0, 0};
    };
}

namespace ConGL::eng2D::shapes {
    class Figure {
    public:
        Figure() = default;

        // implementaion of rendering on to the screen
        virtual void draw(Screen*, COORD) = 0;

        // positioning on the Layout
        void setPos(COORD);
        COORD getPos();
        void movePos(COORD);

        void setSize(COORD);
        COORD getSize();

    protected:
        COORD position = {0, 0};
        COORD size = {0, 0};
    };

    class Rectangle : public Figure {
    public:
        Rectangle() = default;
        Rectangle(COORD size);

        void draw(Screen*, COORD cameraPOS);

        // filling of the rectangle
        void setFilling(PIXEL);

    private:
        PIXEL fill = colors::BG_WHITE;
    };

    class Ellipse : public Figure {
    public:
        Ellipse() = default;
        Ellipse(COORD size);

        void draw(Screen*, COORD cameraPOS);

        // filling of the ellipse
        void setFilling(PIXEL);

    private:
        PIXEL fill = colors::BG_WHITE;
    };

    class Sprite : public Figure {
    public:
        Sprite() = default;
        // define only size
        Sprite(COORD size);
        // define texture with pointer
        Sprite(txr::Texture*);
        // define texture with path
        Sprite(std::string path);

        void draw(Screen*, COORD cameraPOS);

        // set texture with pointer
        void setTexture(txr::Texture*);

    private:
        txr::Texture* ptexture;
    };

    class Text : public Figure {
    public:
        Text() = default;
        Text(std::string text);

        void draw(Screen*, COORD cameraPOS);

        // filling of the ellipse
        void setFilling(PIXEL);
        // set text
        void setText(std::string);

    private:
        PIXEL fill = colors::FG_WHITE;
        std::string text = " ";
    };

    // TODO: text using fonts 
}

namespace ConGL::eng2D {
    class Layout {
        public:
            Layout() = default;
            Layout(Screen* _screen);

            // camera interface
            void setCamera(COORD position);
            COORD getCamera();

            // adds figure to the layout ; returns figure's ID
            int addFigure(shapes::Figure* figure);

            // returns pointer to the figure
            shapes::Figure* getFigure(int id);

            // disables figure on the layout
            void disableFigure(int id);

            // enables figure on the layout
            void enableFigure(int id);

            // checks collisions between two figures on the layout
            inline bool collides(int ID1, int ID2);

            // checks collisions between two figures
            inline static bool collides(shapes::Figure* f1, shapes::Figure* f2);

            // checks if two figures on the layout are touching each other
            inline bool onCollision(int ID1, int ID2);

            // checks if two figures are touching each other
            inline static bool onCollision(shapes::Figure* f1, shapes::Figure* f2);

            // draw frame on to the screen 
            void draw(bool screenUpdate = true);

        private: 
            Screen* screen;
            COORD cameraPOS = {0, 0};

            shapes::Figure* figures[10000];
            std::set<int> validFigures;
            int figureC = 0;
    };
}

#ifndef BIN_LINK
#include "lib/congl.cpp"
#include "lib/screen.cpp"
#include "lib/layout.cpp"
#include "lib/shapes.cpp"
#include "lib/fonts.cpp"
#include "lib/textures.cpp"
#endif // BIN_LINK

#endif