#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=pc11_12,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc13_14,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_12,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc13_14,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_12,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc13_14,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_12,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc13_14,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_12,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc13_14,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_12,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc13_14,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_12,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc13_14,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc15_16,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc17_18,network=sctp -nodes=2x1 ./b.out input/GA_dsj1000.set
sleep 30

scrun -group=pc11_14,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_18,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_14,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_18,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_14,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_18,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_14,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_18,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set
sleep 30
scrun -group=pc11_14,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set &
sleep 10
scrun -group=pc15_18,network=sctp -nodes=4x1 ./b.out input/GA_dsj1000.set
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/test.set
fi
