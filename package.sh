#!/usr/bin/env bash

rm -rf deploy
mkdir deploy
cp analyzer.cpp CMakeLists.txt format-and-tidy.sh LICENSE.txt README.md deploy/
cd deploy
zip bernardo-sulzbach.zip *
cd ..
cp deploy/bernardo-sulzbach.zip .
rm -rf deploy
