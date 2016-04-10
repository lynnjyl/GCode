#!/bin/bash

trajid=1;
before="";

#cd ../Data/newtrajectory
#filelist=$(ls)
#cd ../../gm
#for kfile in $filelist
#do
	#echo $trajid
#	echo $kfile
	#echo "$trajid $kfile" >> index_127.txt
#	filename="../Data/newtrajectory/"$kfile	
#	./gm2 $trajid $filename
#	trajid=$((trajid+1))
#done

for ((i=1;i<=58181;i++))
do
	echo $i
	filename="../Data/new_20/"$i
	./gm5 $i $filename
done
mv matrix.txt matrix_7.txt
mv angle.txt angle_7.txt

for ((i=1;i<=58181;i++))
do
	echo $i
	filename="../Data/new_30/"$i
	./gm5 $i $filename
done
mv matrix.txt matrix_10.txt
mv angle.txt angle_10.txt

for ((i=1;i<=58181;i++))
do
	echo $i
	filename="../Data/new_40/"$i
	./gm5 $i $filename
done
mv matrix.txt matrix_13.txt
mv angle.txt angle_13.txt

for ((i=1;i<=58181;i++))
do
	echo $i
	filename="../Data/new_50/"$i
	./gm5 $i $filename
done
mv matrix.txt matrix_16.txt
mv angle.txt angle_16.txt
