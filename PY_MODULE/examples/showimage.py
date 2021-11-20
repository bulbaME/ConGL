from ConGL import *

screen = Screen()  
screen.toggleAutosize(True)
screen.setFont((5, 5))

main = eng2D.Layout(screen)
img = eng2D.shapes.Sprite('image.txr')
main.addFigure(img)

screen.setSurfaceSize(img.getSize())

while True:
    # terminate when escape is pressed
    if keys.released(chr(0x1b)): 
        break
        
    main.draw(True)