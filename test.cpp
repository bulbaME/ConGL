#include "lib/screen.hpp"
#include "lib/2d.hpp"
#include "lib/figures.hpp"
using namespace std;

int main() {
    Screen screen(true);
    setCurrentHandler(screen.getHandler());

    Layout layout(screen);
    figures::Rectangle rect({10, 15});
    layout.addFigure(rect);

    while (true) {
        layout.draw();
    }

    return 0;
}
