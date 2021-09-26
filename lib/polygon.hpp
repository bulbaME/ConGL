#ifndef _POLY_LIB
#define _POLY_LIB

struct POINT {
    int X = 0, Y = 0, Z = 0;
};

struct POLY {
    POINT a, b, c;
};

struct CAM : public POINT {
    double aX = 0.0f, aY = 0.0f, aZ = 0.0f;
};

#endif