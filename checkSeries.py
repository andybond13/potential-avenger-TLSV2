#!/usr/bin/python

import os,sys
import numpy as np
reps = 20 
minfrag = []
numfrag = []
wCoh = []
solid = []

with open("output.txt") as f:
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
print ""
#print "elements",elements
print "realizations",reps
print "results of",len(minfrag),"experiments"
print "wCoh:    mean=",np.average(wCoh)," median=",np.median(wCoh)
print "numfrag: mean=",np.average(numfrag)," median=",np.median(numfrag)
print "minfrag: mean=",np.average(minfrag)," median=",np.median(minfrag)
print "solid:   mean=",np.average(solid)," median=",np.median(solid)
 

