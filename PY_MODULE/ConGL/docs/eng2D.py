class Layout:
    '''
    #### class Layout {
    ####     Layout() = default;
    ####     Layout(Screen* _screen);

    ####     // camera interface
    ####     void setCamera(COORD position);
    ####     COORD getCamera();

    ####     // adds figure to the layout ; returns figure's ID
    ####     int addFigure(shapes::Figure* figure);

    ####     // returns pointer to figure
    ####     shapes::Figure* getFigure(int id);

    ####     // disables figure on the layout
    ####     void disableFigure(int id);

    ####     // endbles figure on the layout
    ####     void enableFigure(int id);

    ####     // checks collisions between two figures on the layout
    ####     inline bool collides(int ID1, int ID2);

    ####     // checks collisions between two figures
    ####     inline static bool collides(shapes::Figure* f1, shapes::Figure* f2);

    ####     // checks if two figures on the layout are touching each other
    ####     inline bool onCollision(int ID1, int ID2);

    ####     // checks if two figures are touching each other
    ####     inline static bool onCollision(shapes::Figure* f1, shapes::Figure* f2);

    ####     // draw frame on to the screen 
    ####     void draw(bool screenUpdate = true);
    #### }
    
    '''
    
import shapes
import texture