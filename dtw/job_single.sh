#!/bin/bash

trajid=1;
queryfile="../Data/subtrajectory/10009_02"


cd ../Data/subtrajectory/
filelist=$(ls)
cd ../../dtw

for kfile in $filelist
do
	echo $trajid
	filename="../Data/subtrajectory/"$kfile
	./main $queryfile $filename $trajid 10
	trajid=$((trajid+1))
done

