#!/bin/bash

if [ "$#" -gt 2 ]; then
    echo "Illegal number of parameters"
    exit
fi
if [ "$#" -lt 1 ]; then
    echo "Illegal number of parameters"
    exit
fi

begin=$1
end=$1

if [ "$#" -eq 2 ]; then
    end=$2
fi

for i in `seq $begin $end`;
do
    #echo $i
	(cd test$i && cp raw_disp.out raw_disp.gold)
done
