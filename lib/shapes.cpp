#include "../congl.h"

namespace ConGL::eng2D::shapes {
    // FIGURE

    void Figure::setPos(COORD _position) { position = _position; }
    COORD Figure::getPos() { return position; }

    void Figure::movePos(COORD _position) { 
        position.X += _position.X;
        position.Y += _position.Y;
    }

    void Figure::setSize(COORD _size) { size = _size; }
    COORD Figure::getSize() { return size; }


    // RECTANGLE

    Rectangle::Rectangle(COORD _size) { setSize(_size); }

    void Rectangle::draw(Screen* screen, COORD cameraPOS) {
        short toX = position.X + size.X - cameraPOS.X;
        short toY = position.Y + size.Y - cameraPOS.Y;

        short startY = position.Y - cameraPOS.Y, y;
        for (short x = position.X - cameraPOS.X; x < toX; ++x) {
            for (y = startY; y < toY; ++y) 
                screen->setPX({{x, y}, fill.ch, fill.col});
        }
    }
    
    void Rectangle::setFilling(PIXEL _fill) { fill = _fill; }


    // ELLIPSE

    Ellipse::Ellipse(COORD _size) { setSize(_size); }

    // not the best implementation ever
    void Ellipse::draw(Screen* screen, COORD cameraPOS) {
                short rX = size.X / 2, rY = size.Y / 2;                     // x radius, y radius 
                short centerX = position.X + rX - cameraPOS.X;
                short centerY = position.Y + rY - cameraPOS.Y;

                double aS = PI / size.X / size.Y, aT;                       // step angle
                const short rX_s = rX * rX, rY_s = rY * rY, rXY = rX * rY;  // x radius square, y radius square, x radius * y radius
                short toX, toY;
                short x, y;

                for (double a = 0; a <= PI; a += aS) {
                    aT = tan(a);
                    toY = rXY / sqrt(rX_s + rY_s * aT * aT);                // ellipse formula
                    toX = toY * aT; 

                    y = centerY - toY;
                    for (x = centerX - toX; x < centerX + toX; ++x)         // top half of the ellipse
                        screen->setPX(PIXEL({x, y}, fill.ch, fill.col));
                    
                    y = centerY + toY - 1;
                    for (x = centerX - toX; x < centerX + toX; ++x)         // bottom half of the ellipse
                        screen->setPX({{x, y}, fill.ch, fill.col});
                }
            }

    void Ellipse::setFilling(PIXEL _fill) { fill = _fill; }


    // SPRITE

    Sprite::Sprite(COORD _size) { size = _size; }
    Sprite::Sprite(txr::Texture* _ptexture) : Sprite(_ptexture->size) { ptexture = _ptexture; }
    Sprite::Sprite(const char* texturePath) : Sprite(new txr::Texture(texturePath)) { }

    void Sprite::draw(Screen* screen, COORD cameraPOS) {
        COORD pSize = ptexture->size;
        short toX = position.X + size.X - cameraPOS.X;
        short toY = position.Y + size.Y - cameraPOS.Y;

        double tstepX = (double) pSize.X / size.X, tstepY = (double) pSize.Y / size.Y;    // stretching texture
        double tX = 0, tY = 0;                                                                              // current x and y on texture

        PIXEL curr;
        short startY = position.Y - cameraPOS.Y, y;
        short startX = position.X - cameraPOS.X, x;
        COORD scrSize = screen->getScrSize();
        for (y = startY; y < toY && y < scrSize.Y; ++y) {
            for (x = startX; x < toX; ++x) {
                curr = ptexture->data[(int) tY][(int) tX];
                PIXEL sPX = screen->getPX({x, y});
                // checking for charachter and color bitmapping
                screen->setPX({{x, y}, curr.ch == L' ' ? sPX.ch : curr.ch, COLOR (sPX.col >> 8 && !curr.col >> 16 ? (sPX.col >> 8 << 8) | curr.col : curr.col)});
                tX += tstepX;
            }
            tX = 0;
            tY += tstepY;
        }
    }

    void Sprite::setTexture(txr::Texture* _ptexture) { ptexture = _ptexture; }


    // TEXT 


    void Text::setFilling(PIXEL _fill) { fill = _fill; }
    void Text::setText(std::string _text) {
        text = _text;
        size = {1, 1};
        short lenC = 0;
        for (char x : _text) {
            if (x == '\n') {
                lenC > size.X ? (size.X = lenC) :0;
                lenC = 0;
                ++size.Y;
            } else ++lenC;
        }

        lenC > size.X ? (size.X = lenC) :0;
    }

    void Text::draw(Screen* screen, COORD cameraPOS) {
        COORD pos = cameraPOS;
        pos.X += position.X;
        pos.Y += position.Y;

        COORD temp = pos;
        PIXEL px = fill;
        for (char x : text) {
            if (x == '\n') {
                ++temp.Y;
                temp.X = pos.X;
            } else {
                ++temp.X;
                px.ch = (wchar_t) x;
                px.pos = temp;
                screen->setPX(px);
            }
        }
    }

    Text::Text(std::string _text) { setText(_text); }
}
