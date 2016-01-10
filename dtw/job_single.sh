#!/bin/bash

trajid=1;
file="10208_03"
queryfile="../Data/subtrajectory/"$file


cd ../Data/subtrajectory/
filelist=$(ls)
cd ../../dtw

for kfile in $filelist
do
	#echo $trajid
	filename="../Data/subtrajectory/"$kfile
	./main $queryfile $filename $trajid 10
	trajid=$((trajid+1))
done

result="./RateResult/candidate_"$file
sorted=$result"sort"
sort -n -r -k 2 $result > $sorted
cat $sorted | grep -n '\(0\.\)'[0-4] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-5] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-6] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-7] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-8] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-9] | awk 'NR==1{print}'




