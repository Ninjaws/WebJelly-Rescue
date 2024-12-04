#!/bin/bash
find ./src/ -name "*.cpp" -o -name "*.h" | entr -r ./scripts/build_and_run_project.sh