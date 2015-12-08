#!/bin/bash

trajid=1;
before="";

cd ../trajectory
filelist=$(ls)
cd ../gridmapping
for kfile in $filelist
do
	echo $trajid
	echo $kfile
	echo "$trajid $kfile" >> index.txt
	filename="../trajectory/"$kfile	
	./g $trajid $filename
	trajid=$((trajid+1))
done

