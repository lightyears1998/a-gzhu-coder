#!/bin/bash

echo "Without lock:"
gcc task3.c -o task3
./task3

echo "With lock:"
gcc task3.c -o task3 -DTEST_LOCK
./task3
