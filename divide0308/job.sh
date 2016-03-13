#!bin/bash

cd ../Data/trajectory
filelist=$(ls)

cd ../../divide0308

for kfile in $filelist
do
	./a.out $kfile
done
