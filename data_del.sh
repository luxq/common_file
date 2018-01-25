#!/bin/bash 

for ((loop = 0; loop < 1;loop))
do
    for ((i = 0; i < 1; i++))
    do
        mysql -u test -p"12345678" -h 172.19.21.6 < /mnt/code/del_luxqdb.p_car_capture.sql 2> /dev/null
    done
    echo 'del 1w data.'
    sleep 16
done

