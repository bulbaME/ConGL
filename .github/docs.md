# ConGL 

## ::colors

##### backgorund and foreground colors
#### ::BG and ::FG
 - **RED**
 - **GREEN**
 - **BLUE**
 - **BLACK**
 - **WHITE**
 - **INTENSE**

`wchar_t` **W_FF_BLOCK =  █**
`wchar_t` **W_HF_BLOCK =  ▒**

## struct PIXEL

##### fields
| Name | Description | Type |
| ---- | ----------- | ---- |
| pos | position | `COORD` |
| ch | character | `wchar_t` |
| col | color | `COLOR` |

## Screen ()

##### methods
| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| render | renders frame on to the screen |  |  |
| flush | clears screen |  |  |
| getScrSize | returns console size | `none` | `COORD` size |
| setPX | sets pixel on the screen | `PIXEL` pixel | |
| getPX | returns pixel on the screen | | `PIXEL` pixel |
| setFont | sets font size | `COORD` size | | 
| setSurfaceSize | sets surface size | `COORD` size | |
| getSurfaceSize | returns surface size | | `COORD` size |
| toggleAutosize | screen will resize automaticly when nedeed | `bool` state | |
| toggleMeta | meta data will be shown on the top of screen  | `bool` state | |



### KEY_STATE 
##### fields
| Name | Description | Type |
| ---- | ----------- | ---- |
| key | key | `wchar_t` |
| released | if key was released | `bool` |
| ctrlState | control state | `DWORD` |

### ::keys

##### control states 

| Name | Description | Type |
| ---- | ----------- | ----- |
| CAPS_ON | if capslock is on | `DWORD` |
| ALT_LEFT | if left alt is down | `DWORD` |
| ALT_RIGHT | if right alt is down | `DWORD` |
| CTRL_LEFT | if left control is down | `DWORD` |
| CTRL_RIGHT | if right control is down | `DWORD` |
| SHIFT | if shift is down | `DWORD` |

Also you can combine this control states (e.g. `CAPS_ON | SHIFT`)

## Input (`Screen*` screen)

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| bind | binds function to key press  | `KEY_STATE` key, `InputCallback` |  | 
| unbind | binds function from a key press | `KEY_STATE` key |  | 

`InputCallback` is a user defined function which has single `KEY_STATE` parameter, and returns `void`


`KEY` can be either `char` or [windows.h](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) virtual-key

##### functions
| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| down | checks if key is down | `KEY` | `bool` state | 
| released | cheks if key was released | `KEY` | `bool` state | 

**It's not recomended to use this functions, better use `Input`**



## ::eng2D
####  Layout (`Screen*` screen)

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| setCamera | sets camera position | `COORD` position |  |
| getCamera | returns camera position |  | `COORD` position |
| addFigure | adds figure to the layout | `Figure*` figure | `int` id |
| disableFigure | disables figure on the layout | `int` id |  |
| enableFigure | enables figure on the layout | `int` id |  |
| collides | checks collision between two figures on the layout | `int` id1, `int` id2 | `bool` collides |
| `static` collides | checks collision between two figures | `Figure*` f1, `Figure*` f2 | `bool` collides |
| onCollision | checks if two figures on the layout are touching each other | `int` id1, `int` id2 | `bool` collides |
| `static` onCollision | checks if two figures are touching each other | `Figure*` f1, `Figure*` f2 | `bool` collides |
| draw | draws frame on to the screen |  |  |

#### ::shapes 

#### Figure 
`Figure` parent class that is being drawn on the layout
You can extend this class for your purposes

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| draw | draws figure on to the screen | `Screen*` screen | |
| setPos | sets figure position | `COORD` position | |
| getPos | returns figure position | | `COORD` position |
| setSize | sets figure size | `COORD` size | |
| getSize | returns figure size | | `COORD` size | 

#### Rectangle : Figure (`COORD` size)

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| setFilling | sets filling | `PIXEL` fill | |

#### Ellipse : Figure (`COORD` size)

##### public methods

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| setFilling | sets filling | `PIXEL` fill | |

#### Sprite : Figure ()
##### Sprite : Figure (`COORD` size)
##### Sprite : Figure (`Texture` texture)
##### Sprite : Figure (`Texture*` ptexture)
##### Sprite : Figure (`string` texturePath)

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| setTexture | sets texture | `Texture*` texture | |


## ::txr 
path -> texture path

### loadTexture(`string` path)
Loads texture from file. Returns `Texture`.

### Texture (`string` path) 

| Name | Description | Parameters | Return |
| ---- | ----------- | ---------- | ------ |
| `<short X, short Y>` setProper | loads texture from 2d array | `wchar_t` data`[Y][X]` |  |
| `<short X, short Y>` setProper | loads texture from 2d array | `PIXEL` data`[Y][X]` |  |

#### More about textures [here](textures.md)