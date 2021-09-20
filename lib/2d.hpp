#ifndef RECTS_H
#define RECTS_H

#include "screen.hpp"
#include "figures.hpp"
#include <vector>

using ID = unsigned int;

class Layout {
    public:
        Layout(Screen _screen) {
            screen = _screen;
            size = screen.getSize();
            construct();
        }

        Layout(Screen _screen, COORD _size) { 
            screen = _screen;
            size = _size;
            construct();
        }

        // camera interface
        void setCameraPos(COORD position);

        // adds figure to layout ; returns figure's ID
        ID addFigure(figures::Figure figure);
        // removes figure from layout
        void remFigure(ID id);

        // draw frame on to the screen 
        void draw();

    private: 
        Screen screen;
        COORD size = {0, 0};
        COORD cameraPOS = {0, 0};

        std::vector<figures::Figure> figures;

        // class contructor
        void construct();
};

void Layout::construct() {
    
}

void Layout::setCameraPos(COORD position) {
    cameraPOS = position;
}

// figures
ID Layout::addFigure(figures::Figure figure) {
    figures.push_back(figure);
    return figures.size() - 1;
}

void Layout::remFigure(ID id) {
    figures.erase(figures.begin() + id);
}

void Layout::draw() {
    for (figures::Figure& f : figures) 
        f.draw(screen);
    
    screen.draw();
}

#endif