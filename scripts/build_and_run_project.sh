#!/bin/bash
clear
# g++ src/main.cpp -o dist/jelly_rescue -L$LD_LIBRARY_PATH -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# g++ -std=c++20 $(find src/ -name "*.cpp") -o dist/jelly_rescue -I./include -L$LD_LIBRARY_PATH -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
g++ -std=c++20 -g -O0 $(find src/ -name "*.cpp") -o dist/jelly_rescue -I./include -L$LD_LIBRARY_PATH -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# g++ src/main.cpp -o dist/jelly_rescue -L$LD_LIBRARY_PATH -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
gdb dist/jelly_rescue
