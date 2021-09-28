#ifndef RECTS_H
#define RECTS_H

#include "screen.hpp"
#include "shapes.hpp"

class Layout {
    public:
        Layout() = default;
        Layout(Screen* _screen) {
            screen = _screen;
        }

        // camera interface
        void setCamera(COORD position) { cameraPOS = position; }
        COORD getCamera() { return cameraPOS; }

        // adds figure to the layout ; returns figure's ID
        int addFigure(shapes::Figure* figure) {
            figures[figureC] = figure;
            validFigures.insert(figureC);
            return figureC++;
        }

        // disables figure on the layout
        void disableFigure(int id) {
            validFigures.erase(id);
        }

        // endbles figure on the layout
        void enableFigure(int id) {
            if (id < figureC) validFigures.insert(id);
        }

        // checks collisions between two figures on the layout
        inline bool collides(int ID1, int ID2);

        // checks collisions between two figures
        inline static bool collides(shapes::Figure* f1, shapes::Figure* f2);

        // checks if two figures on the layout are touching each other
        inline bool onCollision(int ID1, int ID2);

        // checks if two figures are touching each other
        inline static bool onCollision(shapes::Figure* f1, shapes::Figure* f2);

        // draw frame on to the screen 
        void draw();

    private: 
        Screen* screen;
        COORD cameraPOS = {0, 0};

        shapes::Figure* figures[10000];
        std::set<int> validFigures;
        int figureC = 0;
};

bool Layout::collides(int id1, int id2) {
    return Layout::collides(figures[id1], figures[id2]);
}

bool Layout::collides(shapes::Figure* f1, shapes::Figure* f2) {
    COORD s1 = f1->getSize(), s2 = f2->getSize();
    COORD p1 = f1->getPos(), p2 = f2->getPos();
    COORD mp1 = { short (s1.X + p1.X), short (s1.Y + p1.Y) }, mp2 = { short (s2.X + p2.X), short (s2.Y + p2.Y) };
    return ( mp1.X <= p2.X || p1.X >= mp2.X || mp1.Y <= p2.Y || p1.Y >= mp2.Y ) ? false : true;
}

bool Layout::onCollision(int id1, int id2) {
    return Layout::onCollision(figures[id1], figures[id2]);
}

bool Layout::onCollision(shapes::Figure* f1, shapes::Figure* f2) {
    COORD s1 = f1->getSize(), s2 = f2->getSize();
    COORD p1 = f1->getPos(), p2 = f2->getPos();
    COORD mp1 = { short (s1.X + p1.X), short (s1.Y + p1.Y) }, mp2 = { short (s2.X + p2.X), short (s2.Y + p2.Y) };
    return ( mp1.X < p2.X || p1.X > mp2.X || mp1.Y < p2.Y || p1.Y > mp2.Y ) ? false : true;
}

void Layout::draw() {
    for (auto f : validFigures)
        figures[f]->draw(screen, cameraPOS);
    screen->draw();
}

#endif