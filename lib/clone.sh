#!/bin/bash

dependencies="./dependencies.txt"

clone()  {
	git clone "$1"
}

while IFS= read -r line
do 
	clone "$line"
done < "$dependencies"
clone "$line"