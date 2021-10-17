#include "../congl.h"

namespace ConGL {
    PIXEL::PIXEL(wchar_t _ch) { ch = _ch; }
    PIXEL::PIXEL(COLOR _col) { col = _col; }
    PIXEL::PIXEL(wchar_t _ch, COLOR _col) { ch = _ch, col = _col; }
    PIXEL::PIXEL(COORD _pos, wchar_t _ch, COLOR _col) : PIXEL(_ch, _col) { pos = _pos; }
    PIXEL::PIXEL(COORD _pos) { pos = _pos; }

    bool KEY_STATE::operator==(KEY_STATE& other) const {
        return key == other.key && ctrlState == other.ctrlState;
    }
}

namespace ConGL::keys {
    bool down(char key) {
        return -GetAsyncKeyState(key) == 0x8000;
    }

    bool released(char key) {
        return -GetAsyncKeyState(key) == 0x7FFF;
    }
}