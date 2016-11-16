#!/bin/bash -a
# set -x

TMPDIR=/tmp/ch6_1b

mkdir -p $TMPDIR

I=300000

i=0

while [ "$i" -le "$I" ]
do
		echo "$i" > $TMPDIR/$i.txt2
	 (( i=i+1 ))
    echo -n "."
done

ls -l $TMPDIR/* 2>&1

echo "waiting for input"
read x

find $TMPDIR -name "3*txt2" -print | xargs tar cvf test.tar

ls -ld $TMPDIR test.tar

exit

rm -f $TMPDIR/*.txt2 *.tar
rm -fr $TMPDIR
rmdir $TMPDIR

exit 0

# Testing 1 2 3
