#!/bin/bash

cleaner()  {
	cd $1
	if [ -d "build" ]; then
		rm -r build
	fi    
	cd ..
}

cleaner attender
cleaner SimpleJSON
cleaner star-tape
cleaner soci