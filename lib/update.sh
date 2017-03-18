#!/bin/bash

dependencies="./dependencies.txt"

update()  {
	dir="${1##*/}"
	dir="${dir%.*}"
	cd "$dir"
	echo -e "pull \e[32m$dir\e[0m"
	git pull
	cd ..
}

while IFS= read -r line
do 
	update "$line"
done < "$dependencies"
update "$line"