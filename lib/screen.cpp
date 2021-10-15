#include "../congl.h"
#ifdef _WIN32

namespace ConGL {

Screen::Screen() {
    hs = new HScreen(true, true);
}

Screen::~Screen() {
    delete hs;
}

void Screen::setPX(PIXEL px) {
    hs->setPX_s(px);
}

PIXEL Screen::getPX(COORD pos) {
    return hs->getPX(pos);
}

COORD Screen::getScrSize() {
    return hs->getSize();
}

void Screen::setSurfaceSize(COORD size) {
    hs->setSurfaceSize(size);
}

COORD Screen::getSurfaceSize() {
    return hs->getSurfaceSize();
}

void Screen::render() {
    hs->draw();
}

void Screen::flush() {
    hs->flushScreen();
}

void Screen::toggleAutosize(bool toggle) {
    hs->autosizeToggle(toggle);
}


void Screen::toggleMeta(bool toggle) {
    hs->metaToggle(toggle);
}

void Screen::setFont(COORD fontSize) {
    hs->setFont(fontSize);
}

void Screen::_setFpsLimit(int fps) {
    hs->setFpsLimit(fps);
}

int Screen::getFps() {
    return hs->fps;
}

HScreen* Screen::_getHScreen() { return hs; }
}

#else 

// TODO: UNIX IMPLEMETATION 

#endif