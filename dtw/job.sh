#!/bin/bash

trajid=1;
queryfile="../result/15320100127234004.plt"

cd ../result/
filelist=$(ls)
cd ../dtw

for kfile in $filelist
do
	filename="../result/"$kfile
	./dtw $queryfile $filename $trajid
	trajid=$((trajid+1))
done

:<<BLOCK
for kfile in $filelist
do
	trajid=1
	queryfile="../result/"$kfile
	for jfile in $filelist
	do
		filename="../result/"$jfile
		./dtw $queryfile $filename $trajid
		trajid=$((trajid+1))
	done
	
done
BLOCK
