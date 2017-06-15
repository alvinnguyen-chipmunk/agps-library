#!/bin/bash

TARGET="stylagps.tar.xz"
BUILD=${PWD}

if [[ ! ${ARCH} = "arm" || -z ${ARCH} ]]; then
	printf "\e[31mERROR: please initialize poky SDK first\e[0m\n"
	exit -1
fi

if [ -e ${TARGET} ]; then
	rm ${TARGET}
	rm -rf image
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

function build_static()
{
	$CC -Wall -c stylAgpsUtils.c stylagps.c $(pkg-config --libs --cflags glib-2.0 libnm json-c libcurl) -I. -L.
	$AR rcs libstylagps.a stylagps.o stylAgpsUtils.o

	$CC -o stylagps_demo_static examples/main.c -L/data/linux-workspace/styl/project/busterminal/stylagps/ -lstylagps $(pkg-config --cflags --libs json-c libnm glib-2.0 libcurl)
}

build_static
