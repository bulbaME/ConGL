import sys
import os

if 'win' in sys.platform:
    pass
else:
    print('ConGL supports only Windows at the moment.')
    exit()
    
if sys.version_info.major != 3 or sys.version_info.minor < 6:
    print('ConGL requires Python 3.6 or higher')
    exit()

if __name__ == "__main__":
    if 'win' in sys.platform:
        from bin.congl import __doc__ as doc
        os.system("color")
        
        ENDC = u'\u001b[0m'
        BOLD = u'\u001b[1m'
        FG = u'\u001b[35m'
        
        print('\n' + FG + BOLD + doc + ENDC)
        
else: 
    congl_dir = os.sep.join(os.path.realpath(__file__).split(os.sep)[:-1])
    sys.path.append(congl_dir)
    from congl import *