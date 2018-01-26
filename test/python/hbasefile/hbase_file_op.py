#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
提供HBase存取文件
'''
from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from thrift.transport import TTransport
from hbase import Hbase
import fileop as fp
import os

class HBaseFileOp(object):
    '''
    HBase存取文件类，提供saveFile和readFile方法
    '''
    def __init__(self, table='file_table', host="127.0.0.1", port=9090):
        self.table = table
        self.host  = host
        self.port  = port 
        self.columnFamilies = ['fileinfo']

        self.transport = TTransport.TBufferedTransport(TSocket.TSocket(host, port))
        self.protocol  = TBinaryProtocol.TBinaryProtocolAccelerated(self.transport)

        self.client = Hbase.Client(self.protocol)
        self.transport.open()

    def reCreateTable(self):
        table = self.table
        tables = self.client.getTableNames()
        # 如果table存在，先删除
        if table in tables:
            self.client.disableTable(table)
            self.client.deleteTable(table)
        self.__create_table(table)

    def __create_table(self, table):
        '''
        内部函数，创建表
        '''
        columnFamilies = []
        for columnname in self.columnFamilies:
            column = Hbase.ColumnDescriptor(name=columnname)
            columnFamilies.append(column)
        self.client.createTable(table, columnFamilies)

    def saveFile(self, path):
        '''
        根据完整的文件路径存储文件到hbase中
        '''
        s_file_size = str(fp.file_size(path))
        s_file_content = fp.file_content(path)
        s_file_name = fp.file_name(path)
        s_file_path = fp.file_path(path)

        rowKey = s_file_name 
        mutations = []
        mutations.append(Hbase.Mutation(column="fileinfo" + ":" +"file_path", value=s_file_path))
        mutations.append(Hbase.Mutation(column="fileinfo" + ":" +"file_content", value=s_file_content))
        mutations.append(Hbase.Mutation(column="fileinfo" + ":" +"file_size", value=s_file_size))
        mutations.append(Hbase.Mutation(column="fileinfo" + ":" +"file_name", value=s_file_name))
        self.client.mutateRow(self.table, rowKey, mutations, {})

    def readFile(self, filename):
        '''
        根据文件名读取文件内容
        '''
        rowKey = filename
        rows = self.client.getRow(self.table, rowKey, {})
        content = ""
        i = 0
        for r in rows:
            i += 1
            content = r.columns.get("fileinfo"+":"+"file_content").value
        if i > 1:
            print "content count is not 1"
        if i == 0:
            # 没有此文件
            return None
        return content

    def deleteFile(self, filename):
        '''
        根据文件名删除记录
        '''
        rowKey = filename
        self.client.deleteAll(self.table, rowKey, "fileinfo",{})

def list_dir(path, filter_size = 1024*1024*10):
    '''
    返回指定目录下的文件列表，过滤掉大于filter_size的文件
    '''
    filelist = []
    if os.path.isdir(path):
        pathlist = os.listdir(path)
        for item in pathlist:
            fullpath = os.path.join(path,item)
            if os.path.isdir(fullpath):
                #list_dir(item)
                pass
            elif os.path.isfile(fullpath):
                if os.path.getsize(fullpath) <= filter_size:
                    filelist.append(fullpath)
    return filelist

def createTable(db):
    db.reCreateTable()
    print '建表完成，表名为file_table'

def uploadFile(db):
    file_path=raw_input('上传文件路径:')
    if os.path.isfile(file_path):
        print '上传文件' + file_path
        db.saveFile(file_path)
    elif os.path.isdir(file_path):
        file_list = list_dir(file_path)
        for item in file_list:
            print '上传文件' + item
            db.saveFile(item)
    print '上传完成'

def downloadFile(db):
    saveDir = '/home/download/'
    file_name=raw_input('下载文件名:')
    content = db.readFile(file_name)
    if content is None:
        print '未找到此文件'
    else:
        savepath = saveDir + file_name
        with open(savepath, 'w+') as f:
            f.write(content)
            print '文件保存到' + savepath

def catFile(db):
    file_name=raw_input('下载文件名:')
    content = db.readFile(file_name)
    if content is None:
        print '未找到此文件'
    else:
        print content

def deleteFile(db):
    file_name=raw_input('下载文件名:')
    db.deleteFile(file_name)
    print '文件已删除'

if __name__ == '__main__':
    db = HBaseFileOp()
    f_map = {}
    f_map['1'] = createTable
    f_map['2'] = uploadFile
    f_map['3'] = downloadFile
    f_map['4'] = deleteFile
    f_map['5'] = catFile
    
    menu = '''======================= MainMenu ========================
1. 建表  2. 上传文件  3.下载文件 4. 删除文件 5. 查看文件 0. 退出
========================================================='''
    while True:
        print menu
        choice = raw_input('请选择:')
        if choice not in ['1','2','3','4','5','0']:
            continue
        elif choice == '0':
            break
        else:
            f = f_map[choice]
            f(db)
