#!/bin/bash

trajid=1;
queryfile="../result/15320100127234004.plt"


cd ../result/
filelist=$(ls)
cd ../dtw

for kfile in $filelist
do
	echo $trajid
	filename="../result/"$kfile
	./main $queryfile $filename $trajid 10
	trajid=$((trajid+1))
done

