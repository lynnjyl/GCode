#!/bin/sh
path=$1
cd $path
filelist=$(ls)
cd ../..
for kfile in $filelist
do
    echo $path
    echo $kfile
    ./main ./roadnetwork/grid_edge_0.05.txt $path"/"$kfile


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

