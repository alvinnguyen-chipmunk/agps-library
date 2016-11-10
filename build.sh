#!/bin/bash

if [ ! -e ./image/usr/lib ];
then
	mkdir ./image/usr/lib
fi

if [ ! -e ./image/usr/bin ];
then
	mkdir ./image/usr/bin
fi

if [ ! -e ./image/usr/include ];
then
	mkdir ./image/usr/include
fi


export LD_LIBRARY_PATH=${PWD}/image/usr/lib

make lib
make all
cp styl-agps.h ./image/usr/include

ln -fs ./image/usr/bin/demo-agps
ln -fs ./image/usr/bin/demo-agps-cpp
