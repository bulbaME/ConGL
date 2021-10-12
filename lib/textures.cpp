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

    Texture::Texture(std::string path) {
        Texture texture = loadTexture(path);
        data = texture.data;
        size = texture.size;
    }

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
        PIXEL** data = new PIXEL*[size.Y];

        char ch, r_col[8];
        std::string df("0x");
        COLOR col;

        // parsing file
        for (short y = 0; y < size.Y; ++y) {
            data[y] = new PIXEL[size.X];
            for (short x = 0; x < size.X; ++x) {
                ch = file.get();                        // 1 char byte
                file.get(r_col, 8);                     // 4 color bytes (00 - FF)
                col = std::stoul(df + r_col, nullptr, 16);
                data[y][x] = PIXEL((wchar_t) ch, col);
            }
        }

        texture.data = data;
        texture.size = size;
        return texture;
    }
}