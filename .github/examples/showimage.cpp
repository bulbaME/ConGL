#include "congl.h"
using namespace std;
using namespace ConGL;
using namespace eng2D;

int main() {
    Screen screen;
    screen.toggleAutosize(true);
    screen.setFont({5, 5});
    Layout layout(&screen);

    shapes::Sprite spr("/textures/examples/image.txr");
    layout.addFigure(&spr);

    screen.setSurfaceSize(spr.getSize());

    while (true) {
        layout.draw();
    }

    return 0;
}