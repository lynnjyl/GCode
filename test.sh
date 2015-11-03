#!/bin/sh
:<<BLOCK
for ((k=0;k<10;k++))
do
    path="GeolifeTrajectories1.3/Data/00${k}/Trajectory"
    cd $path
    filelist=$(ls)
    cd ../../../../
    for kfile in $filelist
    do
        ./g $path"/"$kfile
    done
done


for ((k=10;k<100;k++))
do
    path="GeolifeTrajectories1.3/Data/0${k}/Trajectory"
    cd $path
    filelist=$(ls)
    cd ../../../../
    for kfile in $filelist
    do
        ./g $path"/"$kfile
    done
done
BLOCK
for ((k=100;k<101;k++))
do
    path="GeolifeTrajectories1.3/Data/${k}/Trajectory"
    cd $path
    filelist=$(ls)
    cd ../../../../
    for kfile in $filelist
    do
        ./g $path"/"$kfile
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

