# Application for Visual Composition of 3D Transformations

Application for visual composition of 3D transformations written in C++ using libraries such as [assimp](https://github.com/assimp/assimp), [glfw](https://github.com/glfw/glfw), [glad](https://github.com/Dav1dde/glad), [imgui](https://github.com/ocornut/imgui), [stb](https://github.com/nothings/stb) and [glm](https://github.com/g-truc/glm).

This project was created for bachelor's thesis at Technical University of Liberec, Faculty of Mechatronics, Informatics and Interdisciplinary Studies.

## Build

Clone with `--recursive` flag and run cmake:

```sh
git clone --recursive https://github.com/Micovec/avc3t.git

cd avc3t
cmake CMakeLists.txt
cmake --build .
```

### Visual Studio

Visual Studio has a support for cmake projects. Just open Visual Studio, from menu: File > Open > CMake... and select CMakeLists.txt.

## Run

In order to run the built application you need to have it along side res folder from which the app loads models into scene like so:

```txt
avc3t/
├─ res/
├─ ...
└─ avc3t (the executable)
```
