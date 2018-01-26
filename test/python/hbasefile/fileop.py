#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
提供文件操作接口
'''
import os

def file_size(path):
    return os.path.getsize(path)

def file_content(path):
    content = ""
    with open(path) as f:
        content = f.read()
    return content

def file_name(path):
    return os.path.basename(path)

def file_path(path):
    return os.path.dirname(path)

