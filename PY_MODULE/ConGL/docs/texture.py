class Texture:
    '''
    #### struct Texture {
    ####     Texture();
    ####     Texture(std::string path);
    ####     ~Texture();

    ####     // set texture through arrays of pixels
    ####     template <short X, short Y> 
    ####     void setProper(PIXEL _data[Y][X]);

    ####     // set texture through arrays of characters
    ####     template <short X, short Y> 
    ####     void setProper(wchar_t _data[Y][X], COLOR fill = colors::FG_WHITE);

    ####     Texture operator=(const Texture&);

    ####     PIXEL** data = nullptr;
    ####     COORD size = {0, 0};
    #### };
    '''