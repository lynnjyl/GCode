#! bin/bash

traj=1;
cd traj030802
filelist=$(ls)
cd ..

for kfile in $filelist
do
	old="./traj030802/"$kfile
	new="./newtraj/"$traj
	echo $traj $kfile >> index0308.txt
	cp $old $new
	traj=$((traj+1))
done
