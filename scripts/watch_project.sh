#!/bin/bash
find src/ -name "*.cpp" -o -wholename "./include/**/*.h" | entr -r ./scripts/build_and_run_project.sh
# find ./include/ -name "*.h" | entr -r ./scripts/build_and_run_project.sh