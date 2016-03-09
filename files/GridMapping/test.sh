#!/bin/bash


cd ../result
filelist=$(ls)
cd ../GridMapping
num=1;

for kfile in $filelist
do
	echo $num
	filename="../result/"$kfile
	echo $kfile
	#echo $filename
	./main $filename 100 30 30
	num=$((num+1))
done
