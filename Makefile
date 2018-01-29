SRC = ./src/
all:
	g++ -Wall -pedantic -o lsp3d $(SRC)main.cpp $(SRC)FileHandler.cpp
