#!/bin/sh

trajid=1;
before="";

for ((k=0;k<10;k++))
do
    path="../modified/00${k}"
    cd $path
    numoffiles=$(ls|wc -l)
    filelist=$(ls)
    echo $numoffiles

    cd ../../CreateTensor
    for kfile in $filelist
    do	    
	name=${kfile:0:14}
	if [ "$name" != "$before" ];then
		echo $name
		before=$name
		echo "$trajid $name" >> index.txt
		file1=$path"/"$name".plt_edge.txt"
		file2=$path"/"$name".plt_traj.txt"
		echo $file1
		./main $trajid $file1 $file2 60
		trajid=$((trajid+1))
	else
		echo "the same"
	fi
    done
done

for ((k=10;k<100;k++))
do
    path="../modified/0${k}"
    cd $path
    numoffiles=$(ls|wc -l)
    filelist=$(ls)
    echo $numoffiles

    cd ../../CreateTensor
    for kfile in $filelist
    do
	name=${kfile:0:14}
	if [ "$name" != "$before" ];then
		echo $name
		before=$name
		echo "$trajid $name" >> index.txt
		file1=$path"/"$name".plt_edge.txt"
		file2=$path"/"$name".plt_traj.txt"
		echo $file1
		./main $trajid $file1 $file2 60
		trajid=$((trajid+1))
	else
		echo "the same"
	fi
    done
done

for ((k=100;k<182;k++))
do
    path="../modified/${k}"
    cd $path
    numoffiles=$(ls|wc -l)
    filelist=$(ls)
    echo $numoffiles

    cd ../../CreateTensor
    for kfile in $filelist
    do	    
	name=${kfile:0:14}
	if [ "$name" != "$before" ];then
		echo $name
		before=$name
		echo "$trajid $name" >> index.txt
		file1=$path"/"$name".plt_edge.txt"
		file2=$path"/"$name".plt_traj.txt"
		echo $file1
		./main $trajid $file1 $file2 60
		trajid=$((trajid+1))
	else
		echo "the same"
	fi
    done
done


