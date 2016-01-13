#!/bin/bash
file ="11087_04"



trajid=1;

queryfile="../Data/subtrajectory/"$file
echo $queryfile

cd ../Data/subtrajectory/
filelist=$(ls)
cd ../../lcss

for kfile in $filelist
do
	#echo $trajid
	filename="../Data/subtrajectory/"$kfile
	./lcss $queryfile $filename $trajid 10 10
	trajid=$((trajid+1))
done

result="./candidate_"$file
sorted=$result"sort"
sort -n -r -k 3 $result > $sorted






