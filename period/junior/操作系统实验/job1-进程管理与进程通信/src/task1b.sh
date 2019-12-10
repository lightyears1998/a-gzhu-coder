#!/bin/bash

gcc -o task1b -O0 task1b.c

OUTPUT=""
for (( i=1; i<=100; i++)); do
	OUTPUT+="`./task1b`\n";
done;

echo "$OUTPUT";
echo "abc:" `echo -e "$OUTPUT" | grep "abc" | wc -l`;
echo "bca:" `echo -e "$OUTPUT" | grep "bca" | wc -l`;
echo "cab:" `echo -e "$OUTPUT" | grep "cab" | wc -l`;
echo "acb:" `echo -e "$OUTPUT" | grep "acb" | wc -l`;
echo "cba:" `echo -e "$OUTPUT" | grep "cba" | wc -l`;
echo "bac:" `echo -e "$OUTPUT" | grep "bac" | wc -l`;
