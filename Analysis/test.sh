#!/bin/bash

cd ../result
filelist=$(ls)
cd ../Analysis
num=1;

for kfile in $filelist
do
	echo $num
	filename="../result/"$kfile
	#echo $filename
	./main $filename
	num=$((num+1))
done
