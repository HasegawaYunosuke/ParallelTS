#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_pthr1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_pthr2.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_pthr4.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/Long_pr2392.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/test.set
fi
