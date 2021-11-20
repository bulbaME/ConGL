class Figure:
    '''
    #### class Figure {
    #### public:
    ####     Figure() = default;

    ####     // implementaion of rendering on to the screen
    ####     virtual void draw(Screen*, COORD) = 0;

    ####     // positioning on the Layout
    ####     void setPos(COORD);
    ####     COORD getPos();
    ####     void movePos(COORD);

    ####     void setSize(COORD);
    ####     COORD getSize();

    #### protected:
    ####     COORD position = {0, 0};
    ####     COORD size = {0, 0};
    #### };
    '''
    
class Rectangle(Figure):
    '''
    #### class Rectangle : public Figure {
    ####     Rectangle() = default;
    ####     Rectangle(COORD size);

    ####     void draw(Screen*, COORD cameraPOS);

    ####     // filling of the rectangle
    ####     void setFilling(PIXEL);
    #### };
    '''
    
class Ellipse(Figure):
    '''
    #### class Rectangle : public Figure {
    ####     Ellipse() = default;
    ####     Ellipse(COORD size);

    ####     void draw(Screen*, COORD cameraPOS);

    ####     // filling of the ellipse
    ####     void setFilling(PIXEL);
    #### };
    '''
    
class Sprite(Figure):
    '''
    #### class Rectangle : public Figure {
    ####     Sprite() = default;
    ####     // define only size
    ####     Sprite(COORD size);
    ####     // define texture with pointer
    ####     Sprite(txr::Texture*);
    ####     // define texture with path
    ####     Sprite(std::string path);

    ####     void draw(Screen*, COORD cameraPOS);

    ####     // set texture with pointer
    ####     void setTexture(txr::Texture*);
    #### };
    '''
    
class Text(Figure):
    '''
    #### class Text : public Figure {
    ####     Text() = default;
    ####     Text(std::string text);

    ####     void draw(Screen*, COORD cameraPOS);

    ####     // filling of the ellipse
    ####     void setFilling(PIXEL);
    ####     // set text
    ####     void setText(std::string);
    #### };
    '''