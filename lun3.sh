#!/bin/bash

scrun -group=nop2_3,network=sctp -nodes=2x1 ./b.out input/GA_rat575.set
sleep 30
scrun -group=nop2_3,network=sctp -nodes=2x1 ./b.out input/GA_rat575.set
