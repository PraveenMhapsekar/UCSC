#!/bin/bash -ax

rm -f /tmp/myfifo
mkfifo /tmp/myfifo

ls -l /tmp/myfifo

sleep 5

echo "cat /etc/services > /tmp/myfifo"
cat /etc/services > /tmp/myfifo
