#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/test.set
fi
if [ $1 == 2 ]
then
scrun -group=nop2,network=sctp -nodes=2x1 ./b.out input/GA_rat575.set
fi
