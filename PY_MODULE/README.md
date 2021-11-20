# Python 🐍ConGL 🔮

## Usage: `pip install ConGL`

### Why?
This python package is intended for people who don't know C++ 
and just want to build a console app/game using pythons 
simple syntax 

Python ConGL containcs basically everything you need to create 
something cool using its API

### Usage
Everything is same as [C++ version](../.github/docs.md), except few things:
- Static `eng2D::Layout` methods `collides` and `onCollision` 
were renamed to `collides_S` and `onCollision_S` 
- `WinScreen` class can't be accessed (it can be needed in some rare cases)

### Performance 
Python ConGL is using precompiled binaries which means 
lack of any serios performance hits.
Actually Python ConGL is just a wrapper for the C++ 
version.

### Simple Example
```py
from ConGL import *

screen = Screen()  
screen.toggleAutosize(True)

main = eng2D.Layout(screen)
rect = eng2D.shapes.Rectangle((30, 30))
main.addFigure(rect)

while True:
	# terminate when escape is pressed
	if keys.released(chr(0x1b)): 
		break
		
	main.draw(True)
```

### [More Examples](./examples/)
