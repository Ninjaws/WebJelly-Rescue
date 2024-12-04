#!/bin/bash
clear
g++ src/main.cpp -o dist/jelly_rescue -L$LD_LIBRARY_PATH -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./dist/jelly_rescue
