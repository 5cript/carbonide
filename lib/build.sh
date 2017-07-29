#!/bin/bash

cmake_build()  {
	cd $1
    mkdir -p build
	cd build
    if [ -z "$2" ]; then
        cmake ..
    else
        cmake $2 ..
	fi
	make -j4
	cd ../..
}

cmake_build attender $1
cmake_build SimpleJSON $1
cmake_build star-tape $1
cmake_build soci $1