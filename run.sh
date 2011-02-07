#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/test.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_rat575.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_dsj1000.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/TSONLY_pr2392.set
fi
