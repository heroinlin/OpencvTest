import pickle
import os
from os import listdir, getcwd
from os.path import join
out_file = open('./images.txt', 'w')
for n in range(0,1):
	 data = ("D:/workspace/OpencvTest/OpencvTest_static/images/images/")
	 os.path.dirname(data)
	 for name in os.listdir(data):
		 out_file.write('%s%s\n'%(data,name))
		 print(name)