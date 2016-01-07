#!/bin/bash

trajid=1;
before="";

cd ../Data/subtrajectory
filelist=$(ls)
cd ../../gm
for kfile in $filelist
do
	echo $trajid
	echo $kfile
	echo "$trajid $kfile" >> index_sub_gm.txt
	filename="../Data/subtrajectory/"$kfile	
	./gm $trajid $filename
	trajid=$((trajid+1))
done

