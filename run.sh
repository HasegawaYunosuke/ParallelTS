#!/bin/bash

if [ $1 == 1 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/pm2_1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/pm2_1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/pm2_2.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/od2.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/only_pm_no_GAsw.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/only_pm_GAsw.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/only_od_no_GAsw_1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/only_od_no_GAsw_2.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/pm2_1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/pm2_1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/pm2_2.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/od2.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/only_pm_no_GAsw.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/only_pm_GAsw.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/only_od_no_GAsw_1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/only_od_no_GAsw_2.set
sleep 30

scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/only_pm_no_GAsw.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/only_pm_GAsw.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./threadp1.out input/only_od_no_GAsw_1.set
sleep 30
scrun -group=machinefile,network=sctp -nodes=8x1 ./pc1p.out input/only_od_no_GAsw_2.set
sleep 30
fi
if [ $1 == 2 ]
then
scrun -group=machinefile,network=sctp -nodes=8x1 ./b.out input/only_pm.set
fi
