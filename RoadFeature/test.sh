#!/bin/sh
:<<BLOCK
for ((k=0;k<10;k++))
do
    path="./result/00${k}"
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
#BLOCK

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
BLOCK

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

