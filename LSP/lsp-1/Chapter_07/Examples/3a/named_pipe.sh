#!/bin/bash -a

mkfifo /tmp/mkfifo
ls -l /tmp/mkfifo
./producer.sh > /tmp/mkfifo &
./consumer.sh < /tmp/mkfifo &
