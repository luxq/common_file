#!/bin/bash 

#for ((loop = 0; loop < 1;loop))
#do
    for ((i = 0; i < 2000; i++))
    do
        mysql -u test -p"Changan000%" -h 172.26.3.23 < /mnt/code/luxqdb.p_car_capture.sql 2> /dev/null
    done
    echo 'insert 1w data.'
#done

