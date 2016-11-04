#!/bin/bash -a

i=1
I=10

while [ "${i}" -le "${I}" ]
do
   sleep 3
   read input_line
   echo "just got $input_line"
   (( i=i+1 ))
done
