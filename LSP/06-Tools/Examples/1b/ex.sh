#!
echo "Total lines = `wc -l ./ex.dat`"

echo "##########################"
SEARCH_PATTERN="[lL]ine 1"
set -x
grep "$SEARCH_PATTERN" ./ex.dat
set +x
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "##########################"

