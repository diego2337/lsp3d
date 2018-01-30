CC=g++
CFLAGS=-Wall -pedantic -g
LIBS=-lglut -lGLU -lGL
SRC=./src/
all:
	$(CC) $(CFLAGS) -o lsp3d $(SRC)main.cpp $(SRC)utils.cpp $(SRC)FileHandler.cpp $(SRC)DataFrame.cpp $(SRC)LSP3D.cpp $(SRC)GLHandler.cpp $(LIBS)
