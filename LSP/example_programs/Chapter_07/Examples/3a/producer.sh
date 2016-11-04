#!/bin/bash -a

i=1
I=10

while [ "${i}" -le "${I}" ]
do
    DATE="`date +%m%d%y.%H%M%S`";
    echo "Hello from $$ ( @$DATE )";
    (( i= i+1 ))
    sleep 2
done
