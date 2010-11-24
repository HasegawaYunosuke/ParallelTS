#!/bin/bash

scrun -group=machinefile,network=sctp -nodes=8x1 ./a.out input/test.set
