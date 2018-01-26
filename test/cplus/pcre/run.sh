#!/bin/bash
USR_DIR=/root/usr
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${USR_DIR}/lib
rm -f pcrecpp
make 
#gdb ./pcrecpp
./pcrecpp
