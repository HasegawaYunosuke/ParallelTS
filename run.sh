#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/pr2392_long_log.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/GA_rat575.set

sleep 30
scrun -group=nop4_1,network=sctp -nodes=4x1 ./b.out input/GA_rat575.set &
sleep 5
scrun -group=nop4_2,network=sctp -nodes=4x1 ./b.out input/GA_rat575.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/dsj1000_long_log.set
fi
