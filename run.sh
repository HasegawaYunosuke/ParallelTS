#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=pc4_1,network=sctp -nodes=4x1 ./b.out input/GA_rat575.set &
sleep 10
scrun -group=pc4_2,network=sctp -nodes=4x1 ./b.out input/GA_rat575.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/dsj1000_long_log.set
fi
