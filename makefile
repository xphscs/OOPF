all: all
	g++ source.cpp -o "simulador.exe" -I"include" -L"lib" -lfreeglut -lopengl32 -lglu32