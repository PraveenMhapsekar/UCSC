#!/bin/bash -a

rm -f myfile

echo "dd if=/dev/zero of=myfile bs=1024k seek=128 count=1"
dd if=/dev/zero of=myfile bs=1024k seek=128 count=1

ls -l myfile

ls -lah myfile

du -lah myfile

# rm -f myfile
