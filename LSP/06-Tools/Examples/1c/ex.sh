#!
echo "Total lines = `wc -l ./ex.dat`"

echo "##########################"
SEARCH_PATTERN="[lL][acd]ne 1"
grep "$SEARCH_PATTERN" ./ex.dat
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "##########################"

