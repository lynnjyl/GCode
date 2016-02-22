#! bin/bash

traj=1;
cd subtrajectory
filelist=$(ls)
cd ..

for kfile in $filelist
do
	old="./subtrajectory/"$kfile
	new="./newtrajectory/"$traj
	echo $traj $kfile >> index.txt
	cp $old $new
	traj=$((traj+1))
done