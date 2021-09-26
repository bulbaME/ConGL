#ifndef _SPACE_H
#define _SPACE_H

#include <limits>
#include <set>
#include "../screen.hpp"
#include "polygon.hpp"

constexpr int DEF_INT = std::numeric_limits<int>::min();
constexpr double DEF_DBL = std::numeric_limits<double>::min();
constexpr int MAX_POLY_COUNT = 10000;

class Space {
    public:
        Space() = default;
        Space(Screen* _screen) {
            screen = _screen;
        }

        // drawing frame
        void render();

        // camera position
        void setCam(CAM _camera) { camera = _camera; }
        void setCam(int, int, int, double, double, double);
        CAM getCam() { return camera; }

        // add polygon to the Space; returns polygon's id
        int addPoly(POLY* polygon) {
            polysBuffer[polyC] = polygon;
            validPolys.insert(polyC);
            return polyC++;
        }

        // remove polygon from the Space
        void remPoly(int ID) {
            validPolys.erase(ID);
        }

    private:
        Screen* screen;
        CAM camera;

        // polygon variables
        POLY* polysBuffer[MAX_POLY_COUNT];
        std::set<int> validPolys;
        int polyC;
};

void Space::setCam(int x = DEF_INT, int y = DEF_INT, int z = DEF_INT, double angleX = DEF_DBL, double angleY = DEF_DBL, double angleZ = DEF_DBL) {
    if (x != DEF_INT) camera.X = x;
    if (y != DEF_INT) camera.Y = y;
    if (z != DEF_INT) camera.Z = z;
    if (angleX != DEF_DBL) camera.aX = angleX;
    if (angleY != DEF_DBL) camera.aY = angleY;
    if (angleZ != DEF_DBL) camera.aZ = angleZ;
}

// TODO: polygon rendering
void Space::render() {
    POLY* polygon;

    for (auto p : validPolys) {
        polygon = polysBuffer[p];
    }
}

#endif