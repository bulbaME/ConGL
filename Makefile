CC = /usr/bin/x86_64-w64-mingw32-g++-posix
FLAGS =  -std=c++17 -D_GLIBCXX_USE_NANOSLEEP
CC_FLAGS = -static -O3
DEBUG_FLAGS = -g

debug:
	@read -p "File Path: " path; \
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $$path.cpp -o $$path.exe

win:
	@read -p "File Path: " path; \
	$(CC) $(FLAGS) $(CC_FLAGS) $$path.cpp -o $$path.exe

rofl:
	$(CC) $(FLAGS) $(CC_FLAGS) roflcopter/rofl.cpp -o roflcopter/rofl.exe

test-unix: 
	g++ $(FLAGS) $(CC_FLAGS) test.cpp -o test.o