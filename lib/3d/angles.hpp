#ifndef _ANGLES_LIB
#define _ANGLES_LIB
#define PI 3.14159

using ANGLE = double;

namespace angle {
    // summing two angles
    ANGLE add(ANGLE a, ANGLE b) {
        a = a > PI || a < -PI : a % PI : a;
        b = b > PI || b < -PI : b % PI : b;

        ANGLE c = a + b;
        return c > PI ? c - PI : c < PI ? c + PI : c;
    }

    // substracting two angles
    ANGLE sub(ANGLE a, ANGLE b) { return add(a, -b); }

    // checks if angle b is between a and c
    bool between(ANGLE a, ANGLE b, ANGLE c) {
        c = c > PI || c < -PI : c % PI : c;

        return add(a, -b) > PI ?  
    }
}

#endif