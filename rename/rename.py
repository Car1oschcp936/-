#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2015-10-11 23:37:03
# @Author  : Car1os.chcp936 (Car1os.chcp936@gmail.com)
# @Link    : https://github.com/DIEGOSnow
# @Version : $Id$

import os
import os.path
import time
start = time.time()
rootdir = "G:\\passwd" # 指明被遍历的文件夹
f = open("G:\\text","w")
count = 0
f.write("原来的文件名：\n")
for parent,dirnames,filenames in os.walk(rootdir): 
#三个参数：分别返回1.父目录 2.所有文件夹名字（不含路径） 3.所有文件名字
	for filename in filenames:
		f.write(os.path.join(parent,filename)+"\n")
		if (cmp(parent,os.getcwd()) != 0):
			os.chdir(parent)    #修改文件名必须要到这个文件夹
			count = 0
		string = "%d" % count
		os.rename(filename, string+".jpg")
		count = count + 1
f.write("修改后的文件名：\n")
count = 0
for parent,dirnames,filenames in os.walk(rootdir): 
	for filename in filenames:
		f.write(os.path.join(parent,filename)+"\n")
		count = count+1
c = time.time() - start
f.write("程序运行耗时:%0.2f\n"%(c))
f.write("一共遍历了%d个文件"%(count))
f.close()