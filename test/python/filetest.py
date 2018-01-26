#!/usr/bin/env python
#-*- coding:utf-8 -*-
import sys
import os

def list_dir(path):
    filelist = []
    if os.path.isdir(path):
        pathlist = os.listdir(path)
        for item in pathlist:
            fullpath = os.path.join(path,item)
            #print fullpath
            if os.path.isdir(fullpath):
                #list_dir(item)
                pass
            elif os.path.isfile(fullpath):
                if os.path.getsize(fullpath)/1024/1024 < 10:
                    filelist.append(fullpath)
    return filelist

def main():
    file_list = list_dir("/root/")
    for item in file_list:
        print item

if __name__ == "__main__":
    main()
