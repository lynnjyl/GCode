#!/bin/bash

for ((k=0;k<25;k++))
do


trajid=1;

id=$(($RANDOM%131246))
echo $id

file=$(sed -n "$id, 1p" ../Data/index_sub_gm.txt | awk '{print $2}')
echo $id $file >> ../dtw/Query.txt
echo $file


queryfile="../Data/subtrajectory/"$file
#echo $queryfile


cd ../Data/subtrajectory/
filelist=$(ls)
cd ../../dtw

for kfile in $filelist
do
#	echo $trajid
	filename="../Data/subtrajectory/"$kfile
	./main $queryfile $filename $trajid 10
	trajid=$((trajid+1))
done
#echo $id

result="./RateResult/candidate_"$file
sorted=$result"sort"

sort -n -r -k 2 $result > $sorted

echo "*********"$file"**********"
cat $sorted | grep -n '\(0\.\)'[0-4] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-5] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-6] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-7] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-8] | awk 'NR==1{print}'
cat $sorted | grep -n '\(0\.\)'[0-9] | awk 'NR==1{print}'
# cd ../newlsh
# ./r $id


echo "finish "$k
done

