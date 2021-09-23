#ifndef RECTS_H
#define RECTS_H

#include <vector>
#include "screen.hpp"
#include "shapes.hpp"

using ID = unsigned int;

class Layout {
    public:
        Layout(Screen* _screen) {
            screen = _screen;
        }

        // camera interface
        void setCameraPos(COORD position);

        // adds figure to layout ; returns figure's ID
        ID addFigure(shapes::Figure* figure);
        // removes figure from layout
        void remFigure(ID id);

        // draw frame on to the screen 
        void draw();

    private: 
        Screen* screen;
        COORD cameraPOS = {0, 0};

        std::vector<shapes::Figure*> shapes;
};

void Layout::setCameraPos(COORD position) {
    cameraPOS = position;
}

// shapes
ID Layout::addFigure(shapes::Figure* figure) {
    shapes.push_back(figure);
    return shapes.size() - 1;
}

void Layout::remFigure(ID id) {
    shapes.erase(shapes.begin() + id);
}


void Layout::draw() {
    for (auto f : shapes)
        f->draw(screen, cameraPOS);
    screen->draw();
}

#endif