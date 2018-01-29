SRC = ./src/
all:
	g++ -Wall -pedantic -g -o lsp3d $(SRC)main.cpp $(SRC)FileHandler.cpp
