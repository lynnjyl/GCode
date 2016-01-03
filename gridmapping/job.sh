#!/bin/bash

trajid=1;
before="";

cd ./trajectory
filelist=$(ls)
cd ..
for kfile in $filelist
do
	echo $trajid
	echo $kfile
	echo "$trajid $kfile" >> index.txt
	filename="./trajectory/"$kfile	
	./grid $filename $trajid
	trajid=$((trajid+1))
done

