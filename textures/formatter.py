import sys

def main():
    if (len(sys.argv) < 2):
        print('File name was not specified')
        return

    file = 0
    try:
        file = open(sys.argv[1], 'r+')
    except:
        print(f"No such file named '{sys.argv[1]}'")
        return
    

    texture = []
    size = [0, 0]

    while True:
        chars = file.readline()
        if not chars:
            break
        if chars[-1] == '\n':
            chars = chars[:-1]
        if (len(chars) >= size[0]):
            size[0] = len(chars)
        size[1] += 1
        texture.append(chars)

    texture = map(lambda t: t + ' ' * (size[0] - len(t)), texture)
    texture = ''.join(texture)
    code = f'{size[0]} {size[1]} {texture}'

    if (len(sys.argv) >= 3):
        file = open(sys.argv[2] + '.txr', 'w')
        file.seek(0)
        file.write(code)
    else:
        file.seek(0)
        file.write(code)

if __name__ == '__main__':
    main()