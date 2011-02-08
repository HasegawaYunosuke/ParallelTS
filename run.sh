#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
sleep 10
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/NO_hum_dsj1000.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/test.set
fi
