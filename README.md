# lsp3d
This is a simple LSP projection in 3D using C++ and OpenGL.

# Getting Started

## For UNIX users

Run `dependencies.sh` to install the required packages. Alternatively, if you wish to do it manually, the following packages are required:

* [freeglut3-dev](https://pkgs.org/download/freeglut3-dev)

## For Windows users

Support for Windows is currently unavailable, see [this issue](https://github.com/diego2337/lsp3d/issues/1).

# Usage

## Loading a LSP projection

To run LSP3D, `make` and `<program name> <input file>`. A simple input file would be:

    DY
    3
    3
    x;y;z
    015089_20150306_114500.jpeg;-41.0035226244584;-11.3038845993496;0;1
    015089_20150306_120000.jpeg;6.55586318090474;-21.8315724176906;0;1
    015089_20150306_121500.jpeg;-39.8238878788003;-8.20420979184138;0;1
    
## Commands

Keyboard arrows and `W`, `S`, `A` and `D` rotate the visualization.
