#!/bin/bash
# emcc src/main.cpp -o dist/game.js -Wno-missing-braces -I/app/libs/raylib/build/raylib/include -L/app/libs/raylib/src /app/libs/raylib/src/libraylib.a -s USE_GLFW=3 -DPLATFORM_WEB


# emcc $(find src/ -name "*.cpp") -o dist/game.js -Wno-missing-braces -I./include -I/app/libs/raylib/build/raylib/include -L/app/libs/raylib/src /app/libs/raylib/src/libraylib.a -s ALLOW_MEMORY_GROWTH=1 -s INITIAL_MEMORY=268435456 -s MAXIMUM_MEMORY=4294967296 -s --preload-file assets@/assets -s USE_GLFW=3 -DPLATFORM_WEB
emcc $(find src/ -name "*.cpp") -o dist/game.js -Wno-missing-braces -I./include -I/app/libs/raylib/build/raylib/include -L/app/libs/raylib/src /app/libs/raylib/src/libraylib.a -s ALLOW_MEMORY_GROWTH=1 -s INITIAL_MEMORY=536870912 -s MAXIMUM_MEMORY=4294967296 -s --preload-file assets@/assets -s USE_GLFW=3 -s ASSERTIONS=2 -DPLATFORM_WEB
# -I./include
# -L$LD_LIBRARY_PATH 
# -I.
# -L.
# -s --preload-file assets@/assets
# /app/libs/raylib/src/libraylib.a
#  -Os -Wall
# --shell-file /app/raylib/src/shell.html
cd dist
python3 -m http.server 8080;