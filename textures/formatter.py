import sys
import PIL.Image as Img
from tkinter import *
from tkinter import filedialog as FD

FG_RED = 0x0004
FG_GREEN = 0x0002
FG_BLUE = 0x0001

BG_RED = 0x0040
BG_GREEN = 0x0020
BG_BLUE = 0x0010

def fileWrite(path, code):
    file = open(path, 'wb')
    file.seek(0)
    file.write(code.encode('utf8'))

def winInit():
    global file, filepath
    file, filepath = 0, ''

    root = Tk()
    root.geometry('500x300')
    root.title('Texture Formatter')
    
    menu = Menu(root)



    # file menu
    def selectFile():
        global filepath
        filepath = FD.askopenfilename(title='Select your image', filetypes=[("Image Files", ".png .jfif, .jpg, .jpeg")])

    def openImage(path):
        pass

    def openTexture(path):
        pass

    def openFile():
        global file
        selectFile()
        file = open(filepath)

    def saveFile(path = ''):
        fexists = True

        try:
            open(path)
        except:
            fexists = False

        if path:
            path = path[path.rfind('.'):] + 'txr'
        else:
            selectFile()
            path = filepath



    menuFile = Menu(menu, tearoff=0)
    menuFile.add_command(label='Open', command=openFile, accelerator='Ctrl+O')
    menuFile.add_command(label='Save', command=saveFile, accelerator='Ctrl+S')
    menuFile.add_command(label='Save as...', command=saveFile, accelerator='Ctrl+Shift+S')
    menuFile.add_separator()
    menuFile.add_command(label='Exit', command=root.destroy)

    menu.add_cascade(label='File', menu=menuFile)

    root.config(menu=menu)
    root.mainloop()

def readText(filepath):
    file = open(filepath)

    texture = []
    size = [0, 0]

    while True:
        chars = file.readline()
        if not chars:
            break
        if chars[-1] == '\n':
            chars = chars[:-1]
        if len(chars) >= size[0]:
            size[0] = len(chars)

        newChars = ''
        for x in range(len(chars)):
            newChars += chars[x] + '0007'
        
        size[1] += 1
        texture.append(newChars)

    texture = map(lambda t: t + ' ' * (size[0] - len(t)), texture)
    texture = ''.join(texture)
    
    return texture, size

def readImage(filepath):
    image = Img.open(filepath)
    size = image.size
    texture = ''

    for y in range(size[1]):
        for x in range(size[0]):
            px = image.getpixel((x, y))
            cpx = 0x0000
            char = '#'
            
            r, g, b = px[:3]

            if len(px) == 3 or px[3] > 128:
                if r > 85:
                    cpx |= BG_RED
                if r > 165:
                    cpx |= FG_RED

                if g > 85:
                    cpx |= BG_GREEN
                if g > 165:
                    cpx |= FG_GREEN

                if b > 85:
                    cpx |= BG_BLUE
                if b > 165:
                    cpx |= FG_BLUE

                if cpx >> 4 | 0xFFF0 == cpx | 0xFFF0:
                    cpx = cpx >> 4 << 4
                    char = ' '

            spx = hex(cpx)[2:]
            spx = '0' * (4 - len(spx)) + spx
            texture += char + spx

    return texture, size

def getCode(filename) -> str:
    texture, size = '', []

    try: 
        open(filename, 'rb')

        try:
            Img.open(filename)
            texture, size = readImage(filename)
        except:
            texture, size = readText(filename)

    except:
        print(f"No such file named '{filename}'")
        return

    return f'{size[0]} {size[1]} {texture}'

def main():
    code = getCode(sys.argv[1])
    if not code: return
    
    if (len(sys.argv) >= 3):
        filename = sys.argv[2].split('.')[0] + '.txr'
    else:
        filename = sys.argv[1].split('.')[0] + '.txr'

    fileWrite(filename, code)

if __name__ == '__main__':
    if (len(sys.argv) < 2):
        print('No file name specified')
        # winInit()
    else:
        main()