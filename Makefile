CC = mingw-w64
FLAGS =  -std=c++17
CC_FLAGS = -static -O3
DEBUG_FLAGS = -g

debug:
	@read -p "File Path: " path; \
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $$path.cpp -o $$path.exe

win:
	@read -p "File Path: " path; \
	$(CC) $(FLAGS) $(CC_FLAGS) $$path.cpp -o $$path.exe
