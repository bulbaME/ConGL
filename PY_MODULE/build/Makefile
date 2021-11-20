CL = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\cl.exe"
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

W_PY36_LIBS = /LIB "$(W_PY_)36\libs\python36.lib"
W_PY37_LIBS = /LIB "$(W_PY_)37\libs\python37.lib"
W_PY38_LIBS = /LIB "$(W_PY_)38\libs\python38.lib"
W_PY39_LIBS = /LIB "$(W_PY_)39\libs\python39.lib"
W_PY310_LIBS = /LIB "$(W_PY_)310\libs\python310.lib"

W_INCLUDES = \
	/I"$(W_KITS_INCLUDE)\um" \
	/I"$(W_KITS_INCLUDE)\ucrt" \
	/I"$(W_KITS_INCLUDE)\shared" \
	/I"$(W_MSVC)\include" \
	/

W_LIBS = \
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
	$(W_PY_)36\python.exe -m pip install pybind11
	$(W_PY_)37\python.exe -m pip install pybind11
	$(W_PY_)38\python.exe -m pip install pybind11
	$(W_PY_)39\python.exe -m pip install pybind11
	$(W_PY_)310\python.exe -m pip install pybind11

wb36:
	$(CL) /LD /I"D:\git\ConGL" $(W_FLAGS) $(W_PY36_INCLUDES) $(W_INCLUDES) $(W_PY36_LIBS) $(W_LIBS) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)36\python.exe

wb37:
	$(CL) /LD /I"D:\git\ConGL" $(W_FLAGS) $(W_PY37_INCLUDES) $(W_INCLUDES) $(W_PY37_LIBS) $(W_LIBS) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)37\python.exe

wb38:
	$(CL) /LD /I"D:\git\ConGL" $(W_FLAGS) $(W_PY38_INCLUDES) $(W_INCLUDES) $(W_PY38_LIBS) $(W_LIBS) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)38\python.exe

wb39:
	$(CL) /LD /I"D:\git\ConGL" $(W_FLAGS) $(W_PY39_INCLUDES) $(W_INCLUDES) $(W_PY39_LIBS) $(W_LIBS) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)39\python.exe

wb310:
	$(CL) /LD /I"D:\git\ConGL" $(W_FLAGS) $(W_PY310_INCLUDES) $(W_INCLUDES) $(W_PY310_LIBS) $(W_LIBS) build.cpp
	rm *.lib *.exp *.obj
	end_build.bat $(W_PY_)310\python.exe

wbuild: wb310

wbuild-release: wb36 wb37 wb38 wb39 wb310

# ubuild:
# 	g++ $(FLAGS) $$($(INCLUDES)) main.cpp -o main$$($(SUFFIX))

