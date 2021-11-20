CONGL = "D:\git\ConGL"

CL32 = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x86\cl.exe"
CL64 = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\cl.exe"
W_PY_ = C:\Users\rilyy\AppData\Local\Programs\Python\Python
W_FLAGS = /std:c++17 /O2

W_KITS_LIB = C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0
W_KITS_INCLUDE = C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0
W_MSVC = C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133

W_PY36_INCLUDES = \
	/I"$(W_PY_)36\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)36\include" 
W_PY37_INCLUDES = \
	/I"$(W_PY_)37\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)37\include" 
W_PY38_INCLUDES = \
	/I"$(W_PY_)38\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)38\include" 
W_PY39_INCLUDES = \
	/I"$(W_PY_)39\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)39\include" 
W_PY310_INCLUDES = \
	/I"$(W_PY_)310\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)310\include" 

W_PY3632_INCLUDES = \
	/I"$(W_PY_)36-32\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)36-32\include" 
W_PY3732_INCLUDES = \
	/I"$(W_PY_)37-32\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)37-32\include" 
W_PY3832_INCLUDES = \
	/I"$(W_PY_)38-32\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)38-32\include" 
W_PY3932_INCLUDES = \
	/I"$(W_PY_)39-32\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)39-32\include" 
W_PY31032_INCLUDES = \
	/I"$(W_PY_)310-32\Lib\site-packages\pybind11\include" \
	/I"$(W_PY_)310-32\include" 

W_PY36_LIBS = /LIB "$(W_PY_)36\libs\python36.lib"
W_PY37_LIBS = /LIB "$(W_PY_)37\libs\python37.lib"
W_PY38_LIBS = /LIB "$(W_PY_)38\libs\python38.lib"
W_PY39_LIBS = /LIB "$(W_PY_)39\libs\python39.lib"
W_PY310_LIBS = /LIB "$(W_PY_)310\libs\python310.lib"

W_PY3632_LIBS = /LIB "$(W_PY_)36-32\libs\python36.lib"
W_PY3732_LIBS = /LIB "$(W_PY_)37-32\libs\python37.lib"
W_PY3832_LIBS = /LIB "$(W_PY_)38-32\libs\python38.lib"
W_PY3932_LIBS = /LIB "$(W_PY_)39-32\libs\python39.lib"
W_PY31032_LIBS = /LIB "$(W_PY_)310-32\libs\python310.lib"

W_INCLUDES = \
	/I"$(W_KITS_INCLUDE)\um" \
	/I"$(W_KITS_INCLUDE)\ucrt" \
	/I"$(W_KITS_INCLUDE)\shared" \
	/I"$(W_MSVC)\include" 

W_LIBS32 = \
	/LIB "$(W_MSVC)\lib\x86\libcpmt.lib" \
	/LIB "$(W_MSVC)\lib\x86\libcmt.lib" \
	/LIB "$(W_MSVC)\lib\x86\uwp\oldnames.lib" \
	/LIB "$(W_MSVC)\lib\x86\libvcruntime.lib" \
	/LIB "$(W_KITS_LIB)\ucrt\x86\libucrt.lib" \
	/LIB "$(W_KITS_LIB)\um\x86\Uuid.lib" \
	/LIB "$(W_KITS_LIB)\um\x86\User32.lib" \
	/LIB "$(W_KITS_LIB)\um\x86\kernel32.Lib"

W_LIBS64 = \
	/LIB "$(W_MSVC)\lib\x64\libcpmt.lib" \
	/LIB "$(W_MSVC)\lib\x64\libcmt.lib" \
	/LIB "$(W_MSVC)\lib\x64\uwp\oldnames.lib" \
	/LIB "$(W_MSVC)\lib\x64\libvcruntime.lib" \
	/LIB "$(W_KITS_LIB)\ucrt\x64\libucrt.lib" \
	/LIB "$(W_KITS_LIB)\um\x64\Uuid.lib" \
	/LIB "$(W_KITS_LIB)\um\x64\User32.lib" \
	/LIB "$(W_KITS_LIB)\um\x64\kernel32.Lib"

FLAGS = -O3 -Wall -shared -std=c++11 -fPIC
INCLUDES = python3 -m pybind11 --includes

wsetup-pybind:
# 64 bit
	$(W_PY_)36\python.exe -m pip install pybind11
	$(W_PY_)37\python.exe -m pip install pybind11
	$(W_PY_)38\python.exe -m pip install pybind11
	$(W_PY_)39\python.exe -m pip install pybind11
	$(W_PY_)310\python.exe -m pip install pybind11
# 32 bit
	$(W_PY_)36-32\python.exe -m pip install pybind11
	$(W_PY_)37-32\python.exe -m pip install pybind11
	$(W_PY_)38-32\python.exe -m pip install pybind11
	$(W_PY_)39-32\python.exe -m pip install pybind11
	$(W_PY_)310-32\python.exe -m pip install pybind11

wb36:
# 64 bit
	$(CL64) /LD /I$(CONGL) $(W_FLAGS) $(W_PY36_INCLUDES) $(W_INCLUDES) $(W_PY36_LIBS) $(W_LIBS64) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)36\python.exe

# 32 bit
	$(CL32) /LD /I$(CONGL) $(W_FLAGS) $(W_PY3632_INCLUDES) $(W_INCLUDES) $(W_PY3632_LIBS) $(W_LIBS32) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)36-32\python.exe

wb37:
# 64 bit
	$(CL64) /LD /I$(CONGL) $(W_FLAGS) $(W_PY37_INCLUDES) $(W_INCLUDES) $(W_PY37_LIBS) $(W_LIBS64) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)37\python.exe

# 32 bit
	$(CL32) /LD /I$(CONGL) $(W_FLAGS) $(W_PY3732_INCLUDES) $(W_INCLUDES) $(W_PY3732_LIBS) $(W_LIBS32) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)37-32\python.exe


wb38:
# 64 bit
	$(CL64) /LD /I$(CONGL) $(W_FLAGS) $(W_PY38_INCLUDES) $(W_INCLUDES) $(W_PY38_LIBS) $(W_LIBS64) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)38\python.exe

# 32 bit
	$(CL32) /LD /I$(CONGL) $(W_FLAGS) $(W_PY3832_INCLUDES) $(W_INCLUDES) $(W_PY3832_LIBS) $(W_LIBS32) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)38-32\python.exe

wb39:
# 64 bit
	$(CL64) /LD /I$(CONGL) $(W_FLAGS) $(W_PY39_INCLUDES) $(W_INCLUDES) $(W_PY39_LIBS) $(W_LIBS64) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)39\python.exe

# 32 bit
	$(CL32) /LD /I$(CONGL) $(W_FLAGS) $(W_PY3932_INCLUDES) $(W_INCLUDES) $(W_PY3932_LIBS) $(W_LIBS32) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)39-32\python.exe

wb310:
# 64 bit
	$(CL64) /LD /I$(CONGL) $(W_FLAGS) $(W_PY310_INCLUDES) $(W_INCLUDES) $(W_PY310_LIBS) $(W_LIBS64) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)310\python.exe

# 32 bit
	$(CL32) /LD /I$(CONGL) $(W_FLAGS) $(W_PY31032_INCLUDES) $(W_INCLUDES) $(W_PY31032_LIBS) $(W_LIBS32) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)310-32\python.exe

wbuild: wb310

wbuild-release: wb36 wb37 wb38 wb39 wb310

# ubuild:
# 	g++ $(FLAGS) $$($(INCLUDES)) main.cpp -o main$$($(SUFFIX))

