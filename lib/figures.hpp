#ifndef _FIGURES_LIB
#define _FIGURES_LIB

#include "screen.hpp"

namespace figures {
    class Figure {
        public:
            Figure() {}

            // realiztion of rendering on to the screen
            virtual void draw(Screen& screen) {}

            void setPos(COORD _position) { position = _position; }
            COORD getPos() { return position; }
        protected:
            COORD position = {0, 0};
    };

    class Rectangle : public Figure {
        public:
            Rectangle() {}

            Rectangle(COORD _size) { size = _size; }

            void draw(Screen& screen) {
                short toX = position.X + size.X;
                short toY = position.Y + size.Y;

                for (short x = position.X; x <= toX; ++x) {
                    for (short y = position.Y; y <= toY; ++y) 
                        screen.setPX_s({x, y}, L'#');
                }
            }

        private:
            COORD size = {0, 0};
    };
}

#endif