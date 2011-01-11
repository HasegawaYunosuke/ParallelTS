#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_pthr1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_pthr4.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/dsj1000_long_log.set
fi
