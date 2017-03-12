#!/bin/bash

TARGET="stylagps.tar.xz"
BUILD=${PWD}

if [[ ! ${ARCH} = "arm" || -z ${ARCH} ]]; then
	printf "\e[31mERROR: please initialize poky SDK first\e[0m\n"
#	exit -1
fi

./autogen.sh
./configure --host=arm-poky-linux-gnueabi --prefix=${PWD}/image
make -j4
make install -j4
cd image
mkdir -p etc/stylagps
cp ../stylagps.conf etc/stylagps
tar cJf ${TARGET} ./*
mv ${TARGET} ..
cd ${BUILD}
