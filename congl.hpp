#ifndef CONGL
#define CONGL

#include <math.h>
#include <fstream>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <iostream>

#ifdef _WIN32 
#include <windows.h>
#endif

#ifdef linux
#include <sys/ioctl.h>
#include <unistd.h>
#include <wchar.h>
#endif

namespace ConGL {
    #include "lib/screen.hpp"
}

namespace ConGL::_2D {
    #include "lib/layout.hpp"
    #include "lib/shapes.hpp"
}

#endif