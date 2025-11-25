# ComponentSDL

- [About](#about)
- [Compilation](#compilation)
- [Donate](#donate)

## About

Tools to make easy and simple GUI for SDL2 in C++.

## Compilation

### Using makefile

   ```bash
   git clone https://github.com/Riyufuchi/ComponentSDL.git
   cd ComponentSDL
   make
   ```

### Using CMake

   ```bash
   git clone https://github.com/Riyufuchi/ComponentSDL.git
   cd ComponentSDL
   
   # On Linux and MacOS
   cmake -B build -S .
   
   # On Windows
   cmake -B build -S . \
    -DSDL2_DIR="C:/path/to/SDL2/cmake" \
    -DSDL2_image_DIR="C:/path/to/SDL2_image/cmake" \
    -DSDL2_ttf_DIR="C:/path/to/SDL2_ttf/cmake"
    
   # Then build the lib
   cmake --build build
   ```
   
## Donate

Few dollars will be enough. If you are planning to use this library in a commercial application, then it would be fair if you would send more, possibly a small share of 5-10% of monthly profits.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
