#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_0005per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_0005per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_0005per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_005per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_005per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_005per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_05per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_05per.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_1h_05per.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/eil51_300sec.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/lin318_300sec.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/rat575_300sec.set
fi
