SRC = ./src/
all:
	g++ -Wall -pedantic -g -o lsp3d $(SRC)main.cpp $(SRC)utils.cpp $(SRC)FileHandler.cpp $(SRC)DataFrame.cpp $(SRC)LSP3D.cpp $(SRC)GLHandler.cpp
