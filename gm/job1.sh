#!/bin/bash

trajid=1;
before="";

#cd ../Data/newtrajectory
#filelist=$(ls)
#cd ../../gm
#for kfile in $filelist
#do
	#echo $trajid
#	echo $kfile
	#echo "$trajid $kfile" >> index_127.txt
#	filename="../Data/newtrajectory/"$kfile	
#	./gm2 $trajid $filename
#	trajid=$((trajid+1))
#done

for ((i=1;i<=131246;i++))
do
	echo $i
	filename="../Data/newtrajectory/"$i
	./gm $i $filename
done

