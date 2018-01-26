#!/bin/bash 

echo "step 1: 按照下面的描述先修改下配置文件"
#修改配置文件，/opt/Changan_backup/DataRuleEngine/conf/file_input/input_file_format.xml
#配置项 input_path 的 path_value 设置为 /data/file_send/, 表示程序从/data/file_send/ 目录扫描文件进行处理.
#配置项 keep_original_file 的status 设置为1，keep_path 设置为 /data/file_send_bak/, 表示将处理后的文件存放到/data/file_send_bak/目录下。
#保存后退出, 执行以下步骤.


echo "step 2: 将抓包程序停掉，准备启动重传文件的程序"
/etc/init.d/nprd stop
/etc/init.d/nred stop
/etc/init.d/redisd stop

mv /opt/Changan /opt/Changan_bak 
mv /opt/Changan_backup /opt/Changan


echo "step 3: 启动程序开始处理数据"
/etc/init.d/redisd start
/etc/init.d/nred start
# 定时七个小时，等待数据传送完.
sleep 25200

echo "step 4 : 恢复抓包程序"
/etc/init.d/nred stop 
/etc/init.d/redisd stop 

mv /opt/Changan /opt/Changan_backup
mv /opt/Changan_bak /opt/Changan 
/etc/init.d/redisd restart 
/etc/init.d/nred restart 
/etc/init.d/nprd restart







