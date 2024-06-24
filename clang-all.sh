#!/bin/bash

# Find all .cpp, .h, and .hpp files and format them using clang-format
find ./src -name '*.cpp' -or -name '*.h' -or -name '*.hpp' | xargs clang-format --verbose -style=file -i