#!/bin/bash

trajid=1;
queryfile="../result/00020081023025304.plt"


cd ../result/
querylist=$(ls 000*)
filelist=$(ls)
cd ../dtw

:<<BLOCK
for kfile in $filelist
do
	echo $trajid
	filename="../result/"$kfile
	./main $queryfile $filename $trajid 10
	trajid=$((trajid+1))
done
<<<<<<< HEAD
BLOCK


for kfile in $querylist
do
	trajid=1
	queryfile="../result/"$kfile
	for jfile in $filelist
	do
		filename="../result/"$jfile
		./main $queryfile $filename $trajid 10
		trajid=$((trajid+1))
	done
	
done

