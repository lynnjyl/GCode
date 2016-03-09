#!bin/bash

cd ../Data/traj0308
filelist=$(ls)

cd ../../divide0308

for kfile in $filelist
do
	./divide $kfile
done
