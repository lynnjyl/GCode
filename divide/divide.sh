#! bin/bash

trajid=1

cd ../Data/trajectory
filelist=$(ls)

cd ../../divide
for kfile in $filelist
do
	echo $trajid $kfile >> index.txt
	#echo $kfile
	#n=$(wc -l $kfile | awk  '{print $1}')
	#d=$((n/120))
	#echo $n
	#echo $d
	#prefix=$trajid"_"
	#echo $prefix
	#split -l 120 $kfile -d $prefix
	trajid=$((trajid+1))
done
