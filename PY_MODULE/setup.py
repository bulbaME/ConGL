from setuptools import setup

from pathlib import Path
this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text()

setup(
    name = 'ConGL',
    packages = ['ConGL'],
    version = '0.2.2',
    license = 'MIT',
    platforms = ['win'],
    description = 'Console Graphics Library',
    author = 'bulba',
    author_email= 'rily.ylir1@gmail.com',
    url = 'https://github.com/bulbaME/ConGL/tree/master/PY_MODULE',
    download_url = '',
    keywords = ['console', 'cmd', 'engine', 'congl', 'terminal'],
    include_package_data = True, 
    package_dir = { 'ConGL': 'ConGL' }, 
    
    long_description = long_description,
    long_description_content_type = 'text/markdown',
    
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