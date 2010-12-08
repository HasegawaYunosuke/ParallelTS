#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/only_od.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/only_od.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/only_od.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/only_od.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/only_od.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/nompi.set
fi
