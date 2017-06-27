#!/bin/sh

iter(){
	for file in $*
	do 
		if [ -d $file ]
			echo "$file is directory"
			iter $file/*
		elif [ -f $file ]
			echo "$file is file"
		fi
	done
}
iter $*