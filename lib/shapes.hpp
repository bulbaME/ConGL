#ifndef _SHAPE_LIB
#define _SHAPE_LIB

#include "screen.hpp"
#define PI 3.14159

namespace txr {
    struct Texture {
        Texture() {
            data = new wchar_t*[1];
            data[0] = new wchar_t[3]{L'E', L'R', L'R'};
            size = {3, 1};
        };

        Texture(std::string path);

        ~Texture() {
            delete [] data;
        }

        // set your texture through arrays
        template <short X, short Y> 
        void setProper(wchar_t (&_data)[Y][X]) {
            size = {X, Y};
            delete [] data;
            data = new wchar_t*[size.Y];

            for (short y = 0; y < size.Y; ++y) {
                data[y] = new wchar_t[size.X];
                for (short x = 0; x < size.X; ++x) 
                    data[y][x] =  _data[y][x];
            }
        }

        wchar_t** data;
        COORD size = {0, 0};
    };

    Texture loadTexture(std::string filename) {
        std::string path = std::filesystem::current_path().string() + '\\' + filename;
        std::ifstream file;
        Texture texture;

        file.open(path);
        if (!file || file.fail() || !file.is_open()) {
            std::cout << "Unnable to load " << filename << std::endl;
            return texture;
        }

        COORD size;
        file >> size.X >> size.Y;
        file.get();
        wchar_t** data = new wchar_t*[size.Y];

        for (short y = 0; y < size.Y; ++y) {
            data[y] = new wchar_t[size.X];
            for (short x = 0; x < size.X; ++x) 
                data[y][x] = (wchar_t) file.get();
        }

        texture.data = data;
        texture.size = size;
        return texture;
    }

    Texture::Texture(std::string path) {
        Texture texture = loadTexture(path);
        data = texture.data;
        size = texture.size;
    }
}



namespace shapes {
    class Figure {
        public:
            Figure() = default;

            // realiztion of rendering on to the screen
            virtual void draw(Screen*, COORD) = 0;

            // positioning on the Layout
            void setPos(COORD _position) { position = _position; }
            COORD getPos() { return position; }

            void movePos(COORD _position) { 
                position.X += _position.X;
                position.Y += _position.Y;
            }

            void setSize(COORD _size) { size = _size; }
            COORD getSize() { return size; }

        protected:
            COORD position = {0, 0};
            COORD size = {0, 0};
    };

    class Rectangle : public Figure {
        public:
            Rectangle() = default;

            Rectangle(COORD _size) { setSize(_size); }

            void draw(Screen* screen, COORD cameraPOS) {
                short toX = position.X + size.X - cameraPOS.X;
                short toY = position.Y + size.Y - cameraPOS.Y;

                short startY = position.Y - cameraPOS.Y, y;
                for (short x = position.X - cameraPOS.X; x < toX; ++x) {
                    for (y = startY; y < toY; ++y) 
                        screen->setPX_s({x, y}, fill);
                }
            }

            // filling of the rectangle
            void setFilling(wchar_t _fill) { fill = _fill; }

        private:
            wchar_t fill = L'X';
    };

    class Ellipse : public Figure {
        public:
            Ellipse() = default;

            Ellipse(COORD _size) { setSize(_size); }

            // not the best ever realisation 
            void draw(Screen* screen, COORD cameraPOS) {
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
                        screen->setPX_s({x, y}, fill);
                    
                    y = centerY + toY - 1;
                    for (x = centerX - toX; x < centerX + toX; ++x)         // bottom half of the ellipse
                        screen->setPX_s({x, y}, fill);
                }
            }

            // filling of the ellipse
            void setFilling(wchar_t _fill) { fill = _fill; }

        private:
            wchar_t fill = L'X';
    };

    class Sprite : public Figure {
        public:
            Sprite() = default;
            // define only size
            Sprite(COORD _size) { size = _size; }
            // define texture with object
            Sprite(txr::Texture _texture) : Sprite(_texture.size) { storeTexture = _texture; ptexture = &storeTexture; }
            // define texture with pointer
            Sprite(txr::Texture* _ptexture) : Sprite(_ptexture->size) { ptexture = _ptexture; }
            // define texture with path
            Sprite(std::string texturePath) : Sprite(txr::Texture(texturePath)) {}

            void draw(Screen* screen, COORD cameraPOS) {
                short toX = position.X + size.X - cameraPOS.X;
                short toY = position.Y + size.Y - cameraPOS.Y;

                double tstepX = (double) ptexture->size.X / size.X, tstepY = (double) ptexture->size.Y / size.Y;    // stretching texture
                double tX = 0, tY = 0;                                                                              // current x and y on texture

                wchar_t curr;
                short startY = position.Y - cameraPOS.Y, y;
                for (short x = position.X - cameraPOS.X; x < toX; ++x) {
                    for (y = startY; y < toY; ++y) {
                        curr = ptexture->data[(int) tY][(int) tX];
                        if (curr != L' ') screen->setPX_s({x, y}, curr);
                        tY += tstepY;
                    }
                    tY = 0;
                    tX += tstepX;
                }
            }

            // set texture with pointer
            void setTexture(txr::Texture* _ptexture) { ptexture = _ptexture; }

        private:
            txr::Texture* ptexture;
            txr::Texture storeTexture;
    };

    // TODO: text using fonts
    // class Text : public Figure {

    //     public: 
    //         Text() = default;
    //         Text(char* _text) { text = _text; }
    //         Text(COORD _size, char* _text) { text = _text; size = _size; }

    //     private:
    //         char* text;
    // };
}

#endif