#ifndef _FIGURES_LIB
#define _FIGURES_LIB

#include "screen.hpp"
#include <math.h>
#define PI 3.14159

namespace figures {
    class Figure {
        public:
            Figure() {}

            // realiztion of rendering on to the screen
            virtual void draw(Screen*, COORD) = 0;

            void setPos(COORD _position) { position = _position; }
            COORD getPos() { return position; }

        protected:
            COORD position = {0, 0};
    };

    class Rectangle : public Figure {
        public:
            Rectangle() {}

            Rectangle(COORD _size) { setSize(_size); }

            void draw(Screen* screen, COORD cameraPOS) {
                short toX = position.X + size.X - cameraPOS.X;
                short toY = position.Y + size.Y - cameraPOS.Y;

                for (short x = position.X; x <= toX; ++x) {
                    for (short y = position.Y; y <= toY; ++y) 
                        screen->setPX_s({x, y}, L'X');
                }
            }

            void setSize(COORD _size) { size = _size; }
            COORD getSize() { return size; }
        
        private:
            COORD size = {0, 0};
    };

    class Ellipse : public Figure {
        public:
            Ellipse() {}

            Ellipse(COORD _size) { setSize(_size); }

            // not the best ever realisation 
            void draw(Screen* screen, COORD cameraPOS) {
                short rX = size.X / 2, rY = size.Y / 2;                     // x radius, y radius 
                short centerX = position.X + rX - cameraPOS.X;
                short centerY = position.Y + rY - cameraPOS.Y;

                double aS = PI / size.X / size.Y, aT;                       // step angle
                const short rX_s = rX * rX, rY_s = rY * rY, rXY = rX * rY;  // x radius sqare, y radius sqare, x radius * y radius
                short toX, toY;
                short x, y;

                for (double a = 0; a <= PI; a += aS) {
                    aT = tan(a);
                    toY = rXY / sqrt(rX_s + rY_s * aT * aT);                // ellipse formula
                    toX = toY * aT; 

                    y = centerY - toY;
                    for (x = centerX - toX; x < centerX + toX; ++x)         // top half of the ellipse
                        screen->setPX_s({x, y}, L'X');
                    
                    y = centerY + toY - 1;
                    for (x = centerX - toX; x < centerX + toX; ++x)         // bottom half of the ellipse
                        screen->setPX_s({x, y}, L'X');
                }
            }

            void setSize(COORD _size) { size = _size; }
            COORD getSize() { return size; }
        
        private:
            COORD size = {0, 0};
    };
}

#endif