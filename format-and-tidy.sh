#!/usr/bin/env bash

SECONDS=0

COMPILATION_DATABASE=compile_commands.json

# Create the symbolic link we need.
if [ ! -f $COMPILATION_DATABASE ]; then
  ln -s build/compile_commands.json
fi

echo Formatting...
clang-format -i *.cpp

echo Tidying up...
clang-tidy *.cpp

echo "Done after $SECONDS seconds."
