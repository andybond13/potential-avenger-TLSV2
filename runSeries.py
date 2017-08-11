#!/usr/bin/python

import os,sys
import numpy as np

minfrag = []
numfrag = []
wCoh = []
solid = []

nelt = sys.argv[1]
#os.system("rm output.txt")
outputfile = "output"+str(nelt)+".txt"
reps = 20
command = "./potential-avenger-launcher.py "+str(nelt)+" >> "+outputfile
for i in range(0,reps):
    print i+1,"of",reps
    os.system("rm results/*.log")
    os.system(command)

with open(outputfile) as f:
    for line in f:
        if (line[0:26]=="Final number of fragments:"):
            l = line.strip().split()
            numfrag.append(float(l[4]))
        if (line[0:24]=="Minimum fragment length:"):
            l = line.strip().split()
            minfrag.append(float(l[3]))
        if (line[0:24]=="Final dissipated energy:"):
            l = line.strip().split()
            wCoh.append(float(l[3]))
        if (line[0:22]==" fragment total length"):
            l = line.strip().split()
            solid.append(float(l[3]))

assert(len(wCoh) == len(minfrag))
assert(len(wCoh) == len(numfrag))
assert(len(wCoh) == len(solid))
#os.system("rm output.txt")
print ""
#print "elements",elements
print "realizations",reps
print "results of",len(minfrag),"experiments"
print "wCoh:    mean=",np.average(wCoh)," median=",np.median(wCoh)
print "numfrag: mean=",np.average(numfrag)," median=",np.median(numfrag)
print "minfrag: mean=",np.average(minfrag)," median=",np.median(minfrag)
print "solid:   mean=",np.average(solid)," median=",np.median(solid)

