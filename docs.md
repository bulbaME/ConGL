# ConGL 

## Textures
texture [formatter](textures/formatter.exe) that creates `.txr` files that can be used later
Usage - `formatter <filename> <output>`

texture [example](textures/example) 

## ::Screen (`bool` newHandler\*, `bool` setCurrent\*)

newHandler: if `true`, creates new Handler (only for windows)
setCurrent: if `true`, switches to new handler (only for windows)

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| draw | draws frame on to the screen | `none` | `void` |
| clear | clears screen buffer | `none` | `void` |
| getScreen | returns screen buffer | `none` | `wchar_t*` buffer | 
| getHandler* | returns handler | `none` | `HANDLE` handler |
| getSize | returns terminal size | `none` | `COORD` size |
| setPx* | sets pixel on the screen | `COORD` coord, `wchar_t` character |
| setPx_s | same as setPx, but safe |
| setFont* | sets font size | `COORD` size | `void` | 

`getHandler` (only for windows)
`setPx()` is unsafe. Could cause errors.
`setFont` (only for windows)


## setCurrentHandler(`HANDLE`  handler)

sets console current console handler (only for windows)

## ::\_2D
###  ::Layout (`Screen` screen)

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| setCamera | sets camera position | `COORD` position | `void` |
| getCamera | returns camera position | `none` | `COORD` position |
| addFigure | adds figure to the layout | `Figure*` figure | `int` id |
| disableFigure | disables figure on the layout | `int` id | `void` |
| enableFigure | enables figure on the layout | `int` id | `void` |
| collides | checks collision between two figures on the layout | `int` id1, `int` id2 | `bool` collides |
| `static` collides | checks collision between two figures | `Figure*` f1, `Figure*` f2 | `bool` collides |
| draw | draws frame on to the screen | `none` | `void` |

### ::shapes 

### ::Figure ()
`Figure` parent class that is being drown on the layout

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| draw | draws figure on to the screen | `Screen*` screen | `void` |
| setPos | sets figure position | `COORD` position | `void` |
| getPos | returns figure position | `none` | `COORD` position |
| setSize | sets figure size | `COORD` size | `void` |
| getSize | returns figure size | `none` | `COORD` size | 

### ::Rectangle : Figure (`COORD` size)

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| setFilling | sets filling | `wchar_t` fill | `void` |

### ::Ellipse : Figure (`COORD` size)

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| setFilling | sets filling | `wchar_t` fill | `void` |

### ::Sprite : Figure (`COORD` size, `Texture` texture)


### ::txr 

### Texture (`const char*` path) 
path -> path to .txr file


# Examples
### rendering simple sprite 
```cpp
#include "congl.hpp"
using namespace ConGL;
using namespace _2D;

int main() {
	Screen screen(true);
	Layout layout(&Screen);
	
	Sprite sprite1("textures/example.txr");
	layout.addFigure(&sprite1);
	
	sprite.setPos({10, 10});
	sprite.setSize({15, 15});
	
	while (true) {
		layout.draw();
	}
	
	return 0;
} 
```
