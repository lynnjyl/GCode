#!bin/bash

id=1

cd ../result
filelist=$(ls)
cd ../Filter


for kfile in $filelist
do
	input="../result/"$kfile
	output="./8-9/"${id}".txt"

	echo $input
	echo $output
	./f $input 8 9 $output
	id=$((id+1))
done