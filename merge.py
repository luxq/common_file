#!/bin/python
#-*- coding:utf-8 -*-
import sys
import os


def main():
    if len(sys.argv) != 3:
        print "参数错误"
        return False
    file1=sys.argv[1]
    file2=sys.argv[2]
    file3="merge_"+file1+"_"+file2+".txt"
    f1 = open(file1,"r")
    f2 = open(file2,"r")
    f3 = open(file3,"w")
    
    line = f1.readline()
    while line:
        line2 = f2.readline()
        f3.write(line)
        f3.write(line2)
        line = f1.readline()

    f1.close()
    f2.close()
    f3.close()
    return True


if __name__ == "__main__":
    if main():
        print "执行成功"
    else:
        print "运行失败."

