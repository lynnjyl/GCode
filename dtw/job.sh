#!/bin/bash

trajid=1;
queryfile="00020081023025304.plt"

cd ../result/
filelist=$(ls)
cd ../dtw

for kfile in $filelist
do
	echo $trajid
	filename="../result/"$kfile
	./dtw $queryfile $filename $trajid
	trajid=$((trajid+1))
done
