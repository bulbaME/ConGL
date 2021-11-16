#include "../congl.h"

namespace ConGL::eng2D::txr {
    Texture::Texture() {
        data = new PIXEL*[1];
        data[0] = new PIXEL[3]{L'E', L'R', L'R'};
        size = {3, 1};
    };

    Texture::~Texture() {
        delete [] data;
    }

    template <short X, short Y> 
    void Texture::setProper(PIXEL _data[Y][X]) {
        size = {X - 1, Y};
        delete [] data;
        data = new PIXEL*[size.Y];

        for (short y = 0; y < size.Y; ++y) {
            data[y] = new PIXEL[size.X];
            for (short x = 0; x < size.X; ++x) 
                data[y][x] =  _data[y][x];
        }
    }

    template <short X, short Y> 
    void Texture::setProper(wchar_t _data[Y][X], COLOR color) {
        size = {X - 1, Y};
        delete [] data;
        data = new PIXEL*[size.Y];

        for (short y = 0; y < size.Y; ++y) {
            data[y] = new PIXEL[size.X];
            for (short x = 0; x < size.X; ++x) 
                data[y][x] = PIXEL(_data[y][x], color);
        }
    }

    Texture::Texture(const char* filename) {
        std::string path = filename;
        std::ifstream file;

        file.open(path);
        if (!file || file.fail() || !file.is_open()) {
            std::cout << "Unnable to load " << filename << std::endl;
            Texture();
            return;
        }

        file >> size.X >> size.Y;
        file.get();

        char ch, ch_col[4];
        std::string df("0x");
        COLOR col;

        // parsing file
        delete [] data;
        data = new PIXEL*[size.Y];
        for (short y = 0; y < size.Y; ++y) {
            data[y] = new PIXEL[size.X];
            for (short x = 0; x < size.X; ++x) {
                ch = file.get();
                file.get(ch_col, 5);  // 4 color bytes (0000 - FFFF)
                
                data[y][x] = PIXEL(ch == '#' ? L'▒' : (wchar_t) ch, std::stoul(df+ch_col, nullptr, 16));
            }
        }

        file.close();
    }

    Texture Texture::operator=(const Texture& other) {
        if (this == &other) 
            return *this;

        size = other.size;
        delete [] data;
        data = new PIXEL*[size.Y];
        for (short y = 0; y < size.Y; ++y) {
            data[y] = new PIXEL[size.X];
            for (short x = 0; x < size.X; ++x) 
                data[y][x] = other.data[y][x];
        } 

        return *this;
    }
}