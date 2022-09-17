#!/bin/bash

CFLAGS='-std=c++98 -pedantic'
CC=clang++
FOLDER=$COMPILE_FOLDER

#makefile_rule=...

$CC $CFLAGS *.cpp 2> compile.log

if [[ $? != 0 ]]; then
	echo 'ERROR'
	echo 
else
	echo 'Compilation OK'
fi
