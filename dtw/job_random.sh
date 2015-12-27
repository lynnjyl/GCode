#!/bin/bash

for ((k=0;k<10;k++))
do


trajid=1;

id=$(($RANDOM%131246))
echo $id

file=$(sed -n "$id, 1p" ../Data/index_sub.txt | awk '{print $2}')
echo $file

queryfile="../Data/subtrajectory/"$file
#echo $queryfile


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
#echo $id

result="./RateResult/candidate_"$file
sorted=$result"sort"

sort -n -r -k 2 $result > $sorted

cat $sorted | grep -n '\(0\.\)'[0-4] | awk 'NR==1{print}'
cd ../newlsh
./r $id


echo "finish "$k
done

