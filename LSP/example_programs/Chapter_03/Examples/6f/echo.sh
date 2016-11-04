#!/bin/bash -a


i="1"
I="1000000"

while [ "$i" -le "$I" ]
do
   echo " Here $i"
   sleep 1;
   ((i=i+1))
done
