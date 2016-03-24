#!/bin/bash
file=$1



#trajid=1;

#queryfile="../Data/newtrajectory/"$file
queryfile="../Data/new/"$file
echo $queryfile

#cd ../Data/newtrajectory/
#filelist=$(ls)
#cd ../../lcss

for ((i=1;i<=58181;i++))
do
	#trajid=$(cat ../Data/index_sub.txt | grep $kfile | awk '{print $1}')
	#echo $i
	filename="../Data/new/"$i
	./lcss $queryfile $filename $i 120 20
	#trajid=$((trajid+1))
done

result="./result/lcss_"$file
sorted=$result"_sort"
sort -n -r -k 3 $result > $sorted
rm $result






