#!
set -a
echo "##########################"
echo "Total lines = `wc -l ./ex.dat`"

echo "##########################"
SEARCH_PATTERN="^t.* 1"
grep "$SEARCH_PATTERN" ./ex.dat
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "Matches all lines that begin with \"t\" and have a \" 1\"."
echo "##########################"
SEARCH_PATTERN=".* 1.$"
grep "$SEARCH_PATTERN" ./ex.dat
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "Matches all lines that end with \"1.\"."
echo "##########################"
SEARCH_PATTERN="^$"
grep "$SEARCH_PATTERN" ./ex.dat
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "Matches all null lines."
echo "##########################"
SEARCH_PATTERN="^ $"
grep "$SEARCH_PATTERN" ./ex.dat
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "Matches all lines that have one blank-space."
echo "##########################"
SEARCH_PATTERN="^ *$"
grep "$SEARCH_PATTERN" ./ex.dat
echo "Lines with \"$SEARCH_PATTERN\" pattern = `grep -c \"$SEARCH_PATTERN\" ./ex.dat`"
echo "Matches all lines that are null or have blank-spaces."
echo "##########################"
