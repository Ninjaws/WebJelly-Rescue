#!/bin/bash
emcc -o dist/game.js src/main.cpp -Os -Wall /app/raylib/src/libraylib.a -I. -I/app/raylib/build/raylib/include -L. -L$LD_LIBRARY_PATH -s USE_GLFW=3 -s --preload-file assets@/assets  -DPLATFORM_WEB
# --shell-file /app/raylib/src/shell.html
cd dist
python3 -m http.server 8080;