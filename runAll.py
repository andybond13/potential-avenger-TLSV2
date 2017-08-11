#!/usr/bin/python

import os,sys
import numpy as np

#elems = [10,15,23,30,45,70,100,150,225,300,450,700,1000,1500,2250,3000,4500,7000,10000,15000,22500,30000,45000]
elems = [4500,7000,10000,15000,22500,30000,45000]
#elems = [500,600,700,840]
#elems = [0.15,0.125,0.1,0.075,0.05]

command = "rm output.txt"
os.system(command)

for elem in elems:
#	command = "./runSeries.py "+str(elem)
	command = "./potential-avenger-launcher.py "+str(elem)+" >>output.txt"
	os.system(command)
