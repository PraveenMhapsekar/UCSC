#!
echo "##########################"
echo "Total lines = `wc -l ./ex.dat`"

echo "##########################"
SEARCH_PATTERN="[lL].*ne 1"
grep "$SEARCH_PATTERN" ./ex.dat
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "Match all lines that have l or L - followed by any char - any #times"
echo "followed by a \"ne 1\"".
echo "##########################"
