#!/bin/bash
#run from src directory
#args: csv, lst, txt, log

rm adventure.log
rm ../test/output.log

echo "Running test $5"

valgrind --leak-check=full -v --log-file=../test/valgrind1_$5.log --error-exitcode=1 ./TreasureHunter $1 $2 &>> ../test/output.log
if [ $? == 1 ]; then
    echo "Memory error."
fi
valgrind --leak-check=full -v --log-file=../test/valgrind2_$5.log --error-exitcode=1 ./TreasureHunterLog $1 $2 &>> ../test/output.log
if [ $? == 1 ]; then
    echo "Memory error."
fi
valgrind --leak-check=full -v --log-file=../test/valgrind3_$5.log --error-exitcode=1 ./TreasureHunterAI $1 $2 &>> ../test/output.log
if [ $? == 1 ]; then
    echo "Memory error."
fi

cmp --silent ../test/output.log $3 || echo "Unexpected stdout."

cmp --silent adventure.log $4 || echo "Unexpected log."
