#!/bin/sh

trajid=9301;
before="";
:<<BLOCK
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
     #   echo $path
     #   echo $kfile
	    
	name=${kfile:0:14}
	if [ "$name" != "$before" ];then
		echo $name
		before=$name
		echo "$trajid $name" >> index.txt
		file1=$path"/"$name".plt_edge.txt"
		file2=$path"/"$name".plt_traj.txt"
		echo $file1
		./main $trajid $file1 $file2 30
		trajid=$((trajid+1))
	else
		echo "the same"
	fi
#    ./main ./roadnetwork/grid_edge_0.05.txt $path"/"$kfile
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
     #   echo $path
     #   echo $kfile
	    
	name=${kfile:0:14}
	if [ "$name" != "$before" ];then
		echo $name
		before=$name
		echo "$trajid $name" >> index.txt
		file1=$path"/"$name".plt_edge.txt"
		file2=$path"/"$name".plt_traj.txt"
		echo $file1
		./main $trajid $file1 $file2 30
		trajid=$((trajid+1))
	else
		echo "the same"
	fi
#    ./main ./roadnetwork/grid_edge_0.05.txt $path"/"$kfile
    done
done
BLOCK
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
     #   echo $path
     #   echo $kfile
	    
	name=${kfile:0:14}
	if [ "$name" != "$before" ];then
		echo $name
		before=$name
		echo "$trajid $name" >> index.txt
		file1=$path"/"$name".plt_edge.txt"
		file2=$path"/"$name".plt_traj.txt"
		echo $file1
		./main $trajid $file1 $file2 30
		trajid=$((trajid+1))
	else
		echo "the same"
	fi
#    ./main ./roadnetwork/grid_edge_0.05.txt $path"/"$kfile
    done
done
:<<BLOCK
for ((k=100;k<101;k++))
do
    path="./result/${k}"
    cd $path
    filelist=$(ls)
    cd ../..
    for kfile in $filelist
    do
        echo $path
        echo $kfile
        ./main ./roadnetwork/grid_edge_0.05.txt $path"/"$kfile
    done

done


for ((k=101;k<182;k++))
do
    path="./result/${k}"
    cd $path
    filelist=$(ls)
    cd ../..
    for kfile in $filelist
    do
        echo $path
        echo $kfile
        ./main ./roadnetwork/grid_edge_0.05.txt $path"/"$kfile
    done


done
BLOCK


#path=$1
#cd $path

#	tmp=`basename $kfile`
#	if [ $tmp == "test.sh" ];then
#		cd ${tmp}
#		for aFile in *
#		do
#            filename="~/Codes/GCode/result/${tmp}/${aFile}"
#            cd ..
#            ./main ./roadnetwork/grid_edge_0.05.txt $filename
#		done
#	fi
#	cd ..
done

