#include "../congl.h"

namespace ConGL::eng2D {

Layout::Layout(Screen* _screen) {
    screen = _screen;
}

// camera
void Layout::setCamera(COORD position) { cameraPOS = position; }
COORD Layout::getCamera() { return cameraPOS; }

// figures
int Layout::addFigure(shapes::Figure* figure) {
    figures[figureC] = figure;
    validFigures.insert(figureC);
    return figureC++;
}

shapes::Figure* Layout::getFigure(int id) {
    return figures[id];
}

void Layout::disableFigure(int id) {
    validFigures.erase(id);
}

void Layout::enableFigure(int id) {
    if (id < figureC) validFigures.insert(id);
}


// collisions
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


// rendering
void Layout::draw(bool screenUpdate) {
    for (auto f : validFigures)
        figures[f]->draw(screen, cameraPOS);
    if (screenUpdate) screen->render();
}
}