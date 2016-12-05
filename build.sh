#!/bin/bash

./configure --host=arm-poky-linux-gnueabi --target=arm-poky-linux-gnueabi --build=x86_64-linux

make -j4
