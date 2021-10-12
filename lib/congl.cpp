#include "../congl.h"

namespace ConGL {
    PIXEL::PIXEL(wchar_t _ch) { ch = _ch; }
    PIXEL::PIXEL(COLOR _col) { col = _col; }
    PIXEL::PIXEL(wchar_t _ch, COLOR _col) { ch = _ch, col = _col; }
    PIXEL::PIXEL(COORD _pos, wchar_t _ch, COLOR _col) : PIXEL(_ch, _col) { pos = _pos; }
}

namespace ConGL::keys {
    // FIXME: reacting to keyboard when not focused on console
    bool down(char key) {
        return -GetAsyncKeyState(key) == 0x8000;
    }

    bool released(char key) {
        return -GetAsyncKeyState(key) == 0x7FFF;
    }
}