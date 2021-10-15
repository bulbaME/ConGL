# Console Graphics Library 🔮

### open-source rendering engine for console 🖥

## Philosophy
You can use ConGL as game engine, as API for creating apps or even for outputing images!
It allows you to create big porjects keeping code clean and nice.

Interface is simple enough, which means that even begginers won't struggle with it.

ConGL uses multi-threading for rendering, so performance always will be on high level.

Also you can extend some classes by yourself for achieving better performance.

## Documentation

Screen
```cpp
// ConGL namespace
Screen screen;

screen.setFont({5, 5});  // set console font size
screen.toggleAutosize(true);  // apodt automatically to the new console size
screen.toggleMeta(true);  // outputs metadata

// surface is a boundary for screen
// it allows you to have space where everything will be drawn
// surface is always placed in the middle of console
COORD newSurface = {30, 30};

// now we apply our surface to the screen
screen.setSurfaceSize(newSurfaceSize);

```

Figures are objects that are being drawn on the screen.
There are few figure types (rectangle, ellipse, sprite).
```cpp
shapes::Rectangle rect({10, 10});  // rectangle with size of 10 x 10

// we can move our rectangle 
rect.movePos({5, 5});  // X + 5, Y + 5

// we can set its size
rect.setSize({7, 7});


// pixel with 'G' character and purple background
PIXEL fill(L'G', colors::BG::BLUE | colors::BG::RED); 

// and we can set its filling
rect.setFilling(fill);
```

Layout 
```cpp
// eng2D namespace 
Layout main(&screen);

// on the layout are placed all objects that will be drawn
int id = main.addFigure(&rect);

// also we may want to disable it 
main.disableFigure(id);

// and enable it back
main.enableFigure(id);

// finally draw our rectangle!
main.draw();
```

Now we can combine everything we learned so far 
and write a small program which draws rectangle 
```cpp
#include <congl.h>
using namespace ConGL;
using namespace eng2D;

int main() {
    Screen screen;  
    screen.toggleAutosize(true);

    Layout main(&screen);
    shapes::Rectangle rect({30, 30});
    main.addFigure(&rect); 
    
    // create loop for drawing our beatiful rectangle
    while (true) {
        // terminate when escape is pressed
        if (keys::released(VK_ESCAPE)) break;

        main.draw();
    }
}

```


## Reference
#### ConGL latest release -> check out [full reference](.github/docs.md)

## Some ConGL [projects](.github/examples.md) 

## [Contributing](.github/contributing.md)
