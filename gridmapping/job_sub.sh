#!/bin/bash

trajid=1;
before="";

cd ../divide/subtrajectory
filelist=$(ls)
cd ../../gridmapping
for kfile in $filelist
do
	echo $trajid
	echo $kfile
	echo "$trajid $kfile" >> index_sub.txt
	filename="../divide/subtrajectory/"$kfile	
	./g $trajid $filename
	trajid=$((trajid+1))
done

