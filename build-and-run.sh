#!/bin/bash
# A script to build (compile the project out-of-source using cmake),
# create an executable using make, and run the project.
# Dan Seremet - 29/Jan/2020

builddir=cmake-build-debug
project_name=LAB03

mkdir -p $builddir && cd $builddir || exit
cmake ../ || exit
make || exit
./$project_name || exit
