#!/bin/bash

for i in `seq 14 21`;
do
	echo $i
	cd ../test$i
#	rm *.c
#	rm *.h
#	ln -s ../../potential-avenger.c .	
#	ln -s ../../potential-avenger.h .	
#	ln -s ../../damageModel.c .	
#	ln -s ../../damageModel.h .	
#	ln -s ../../objects.c .	
#	ln -s ../../objects.h .
	touch potential-avenger-launcher.c	
done    
