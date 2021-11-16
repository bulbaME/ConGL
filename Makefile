CC = /usr/bin/x86_64-w64-mingw32-g++-posix
MINGW = C:/msys64/mingw64.exe
FLAGS =  -std=c++11 -D_GLIBCXX_USE_NANOSLEEP -fPIC
CC_FLAGS = -static -O3
DEBUG_FLAGS = -g -S
BIN_PATH = bin

debug:
	$(CC) $(FLAGS) $(DEBUG_FLAGS) congl.h

debug_p:
	@read -p "File Path: " path; \
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $$path.cpp -o $$path.exe

win:
	@read -p "File Path: " path; \
	$(CC) $(FLAGS) $(CC_FLAGS) $$path.cpp -o $$path.exe

# binary compilation

bin: bin-pre bin-win
	rm ./*.o congl.cpp

bin-win: static-win dynamic-win
bin-unix: static-unix dynamic-unix

bin-pre:
	cp congl.h congl.cpp

static-win:
	$(CC) $(FLAGS) $(CC_FLAGS) -c congl.cpp
	ar rcs $(BIN_PATH)/mingw/libcongl.a congl.o

static-unix:
	g++ $(FLAGS) $(CC_FLAGS) -c congl.cpp
	ar rcs $(BIN_PATH)/g++/libcongl.a congl.o

dynamic-win: 
	$(CC) -c congl.cpp
	$(CC) -shared -Wall congl.o -o $(BIN_PATH)/mingw/libcongl.so 

dynamic-unix: 
	g++ $(FLAGS) $(CC_FLAGS) -c congl.cpp -fPIC
	g++ -shared congl.o -o $(BIN_PATH)/g++/libcongl.so


# tests
wtest-h:
	$(MINGW) $(FLAGS) $(CC_FLAGS) test/test_h.cpp -o test/test.exe

test-h:
	$(CC) $(FLAGS) $(CC_FLAGS) test/test_h.cpp -o test/test.exe

test-static:
	$(CC) $(FLAGS) $(CC_FLAGS) test/test_bin.cpp $(BIN_PATH)/mingw/libcongl.a -o test/test.exe

test-dynamic:
	cp $(BIN_PATH)/mingw/libcongl.so libcongl.dll
	cp $(BIN_PATH)/mingw/libcongl.so test/libcongl.so
	$(CC) -L./ -o test/test.exe test/test_bin.cpp -lcongl
	rm *.dll

test-test:
	$(CC) $(FLAGS) $(CC_FLAGS) test/test.cpp -o test/test.exe