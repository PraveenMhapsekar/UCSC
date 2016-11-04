#!
echo "##########################"
echo "Total lines = `wc -l ./ex.dat`"
set -x
grep "Line 1" ./ex.dat
set +x
echo "Lines with \"Line 1\" pattern = `grep -c \"Line 1\" ./ex.dat`"
echo "##########################"

