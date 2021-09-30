//--------------------- (c) BULBA 2021 -------------------------//
//                                                              //                                                          
//        /$$$$$$                       /$$$$$$  /$$            //
//       /$$__  $$                     /$$__  $$| $$            //
//      | $$  \__/  /$$$$$$  /$$$$$$$ | $$  \__/| $$            //
//      | $$       /$$__  $$| $$__  $$| $$ /$$$$| $$            //
//      | $$      | $$  \ $$| $$  \ $$| $$|_  $$| $$            //       
//      | $$    $$| $$  | $$| $$  | $$| $$  \ $$| $$            //
//      |  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$$      //   
//       \______/  \______/ |__/  |__/ \______/ |________/      //      
//                                                              //                                                          
//--------------------------------------------------------------//

#ifndef CONGL
#define CONGL

#include <math.h>
#include <fstream>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <map>

#ifdef _WIN32 
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <wchar.h>
#include <unistd.h>
#endif

namespace ConGL {
    #include "lib/screen.hpp"
}

namespace ConGL::_2D {
    #include "lib/layout.hpp"
    #include "lib/shapes.hpp"
    #include "lib/fonts.hpp"
}

#endif