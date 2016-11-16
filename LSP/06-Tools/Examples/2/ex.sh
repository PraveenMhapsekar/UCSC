set -x

echo "This is for testing Test" | sed 's/is/at/' 
echo "This is for testing Test" | sed 's/is/at/2' 
echo "This is for testing Test" | sed 's/is/at/g' 

echo "/temp/tmpfile" | sed 's/temp/tmp/'

