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
	echo "$trajid $kfile" >> index_sub_gm_111.txt
	filename="../Data/subtrajectory/"$kfile	
	./gm2 $trajid $filename
	trajid=$((trajid+1))
done

