#!/bin/bash

valgrind --leak-check=full -v --log-file=../test/valgrind.log --error-exitcode=1 ./TreasureHunter $1 $2 &>> ../test/output.log
if $? then
    echo "Memory error."
fi
valgrind --leak-check=full -v --log-file=../test/valgrind.log --error-exitcode=1 ./TreasureHunterLog $1 $2 &>> ../test/output.log
if $? then
    echo "Memory error."
fi
valgrind --leak-check=full -v --log-file=../test/valgrind.log --error-exitcode=1 ./TreasureHunterAI $1 $2 &>> ../test/output.log
if $? then
    echo "Memory error."
fi

if diff ../test/output.log $3 then 
    echo "Unexpected stdout."
fi

if diff adventure.log $4 then 
    echo "Unexpected log."
fi
