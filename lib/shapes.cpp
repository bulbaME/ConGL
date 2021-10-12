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
                screen->setPX(PIXEL({x, y}, fill.ch, fill.col));
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
                        screen->setPX(PIXEL({x, y}, fill.ch, fill.col));
                }
            }

    void Ellipse::setFilling(PIXEL _fill) { fill = _fill; }


    // SPRITE

    Sprite::Sprite(COORD _size) { size = _size; }
    Sprite::Sprite(txr::Texture _texture) : Sprite(_texture.size) { storeTexture = _texture; ptexture = &storeTexture; }
    Sprite::Sprite(txr::Texture* _ptexture) : Sprite(_ptexture->size) { ptexture = _ptexture; }
    Sprite::Sprite(std::string texturePath) : Sprite(txr::Texture(texturePath)) {}

    void Sprite::draw(Screen* screen, COORD cameraPOS) {
        short toX = position.X + size.X - cameraPOS.X;
        short toY = position.Y + size.Y - cameraPOS.Y;

        double tstepX = (double) ptexture->size.X / size.X, tstepY = (double) ptexture->size.Y / size.Y;    // stretching texture
        double tX = 0, tY = 0;                                                                              // current x and y on texture

        PIXEL curr;
        short startY = position.Y - cameraPOS.Y, y;
        short startX = position.X - cameraPOS.X, x;
        for (y = startY; y < toY; ++y) {
            for (x = startX; x < toX; ++x) {
                curr = ptexture->data[(int) tY][(int) tX];
                if (curr.ch != L' ' && (curr.col >> 3 * 8)) screen->setPX(PIXEL({x, y}, curr.ch, curr.col));
                tX += tstepX;
            }
            tX = 0;
            tY += tstepY;
        }
    }

    void Sprite::setTexture(txr::Texture* _ptexture) { ptexture = _ptexture; }
}
