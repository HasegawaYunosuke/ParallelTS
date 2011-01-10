#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/test.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/dsj1000_long_log.set
fi
