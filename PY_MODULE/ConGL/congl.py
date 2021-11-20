class COORD:
    '''
    #### struct COORD {
    ####    short X, Y;
    #### };
    '''

class PIXEL:
    '''
    #### struct PIXEL {
    ####     PIXEL() = default;
    ####     PIXEL(wchar_t);
    ####     PIXEL(COLOR);
    ####     PIXEL(wchar_t, COLOR);
    ####     PIXEL(COORD, wchar_t, COLOR);
    ####     PIXEL(COORD);

    ####     COORD pos = {0, 0};
    ####     wchar_t ch = L' ';
    ####     COLOR col = colors::FG_WHITE;
    #### };

    '''
    
class Screen:
    '''
    #### class Screen {
    ####    Screen();
    ####    ~Screen();

    ####    // set pixel to a specific position
    ####    void setPX(PIXEL);
    ####    // get pixel from a specific position
    ####    PIXEL getPX(COORD);
    ####    // returns screen size
    ####    COORD getScrSize();
    ####    // set surface size
    ####    void setSurfaceSize(COORD);
    ####    // returns surface size
    ####    COORD getSurfaceSize();

    ####    // render screen
    ####    void render();
    ####    // clears screen
    ####    void flush();
        
    ####    // toggle auto screen resizing
    ####    void toggleAutosize(bool);
    ####    // toggle meta data
    ####    void toggleMeta(bool);

    ####    // set font size
    ####    void setFont(COORD);

    ####    void _setFpsLimit(int);

    ####    // returns current fps 
    ####    int getFps();
    }
    
    '''

W_FF_BLOCK : str
W_HF_BLOCK : str
W_QF_BLOCK : str

# import docs.keys as keys 
# import docs.colors as colors
# import docs.eng2D as eng2D

from bin.congl import *