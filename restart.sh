#!/usr/bin/sh
while true
do

echo "-------------------"
#ここではftpdのプロセス監視
isAlive=`ps -aux | grep "kbhit" | grep -v grep | wc -l`
if [ $isAlive = 1 ]; then
echo "kbhit:ALIVE"
else
echo "kbhit:DEAD"

cd /home/unitree/unitree_legged_sdk_remote_control/build
./kbhit_walk0904 &

fi

sleep 0.3
done
