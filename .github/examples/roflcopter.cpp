#include "congl.h"
using namespace std;
using namespace ConGL;
using namespace eng2D;

int main() {
    Screen screen;
    screen.toggleAutosize(true);
    Layout layout(&screen);

    wchar_t d1[7][24] = {
        L"          LOL:ROFL:ROFL",
        L"        ___^______     ",
        L" L   __/      []  \\    ",
        L" O ===__           \\   ",
        L" L      \\___ ___ ___]  ",
        L"            I   I      ",
        L"         ----------/   "
    };

    wchar_t d2[7][24] = {
        L"ROFL:ROFL:LOL          ",
        L"        ___^______     ",
        L"     __/      []  \\    ",
        L"LOL===__           \\   ",
        L"        \\___ ___ ___]  ",
        L"            I   I      ",
        L"         ----------/   "
    };

    txr::Texture t1, t2;
    t1.setProper<24, 7>(d1, colors::FG::RED);
    t2.setProper<24, 7>(d2, colors::FG::GREEN);

    shapes::Sprite heli(&t1); 
    layout.addFigure(&heli);

    int c = 0;
    int d = 0;
    while (true) {
        if (c > 1000) {
            d++;
            if (d % 2) heli.setTexture(&t1);
            else heli.setTexture(&t2);

            c = 0;
        } else if (c % 100 == 0) {
            if (keys::down(VK_RIGHT)) heli.movePos({1, 0});
            if (keys::down(VK_LEFT)) heli.movePos({-1, 0});            
            if (keys::down(VK_DOWN)) heli.movePos({0, 1});
            if (keys::down(VK_UP)) heli.movePos({0, -1});
        }

        c++;
        layout.draw();
    }

    return 0;
}