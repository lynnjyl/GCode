#!/bin/bash
d1=$1
d2=$2

cd ../GridMapping/trajectory
filelist=$(ls)
cd ../../Analysis
num=1;

for kfile in $filelist
do
	echo $num
	filename="../GridMapping/trajectory/"$kfile
	echo $kfile
	#echo $filename
	./main $filename $d1 $d2
	num=$((num+1))
done
