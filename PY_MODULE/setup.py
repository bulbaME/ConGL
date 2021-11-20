from distutils.core import setup, Extension

setup(
    name = 'ConGL',
    packages = ['ConGL'],
    version = '0.1',
    license = 'MIT',
    platforms = ['win'],
    description = 'Console Graphics Library',
    author = 'bulba',
    author_email= 'rily.ylir1@gmail.com',
    url = 'https://github.com/bulbaME/ConGL/PY_MODULE',
    download_url = '',
    keywords = ['console', 'cmd', 'engine', 'congl', 'terminal'],
    package_dir = { 'ConGL': 'ConGL'}, 
	py_modules = ['ConGL/docs'],
    classifiers = [
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10'
    ]
)