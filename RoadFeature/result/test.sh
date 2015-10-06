#!/bin/sh
for kfile in * 
do
	tmp=`basename $kfile`
	if [ $tmp != "test.sh" ];then
		cd ${tmp}
		for aFile in *
		do

            filename="~/Codes/GCode/result/${tmp}/${aFile}"
#echo $filename
#tmpFile=`basename $aFile`
            ~/Codes/GCode/RoadFeature/main ~/Codes/GCode/RoadFeature/roadnetwork/grid_edge_0.05.txt $filename
		done
	fi
	cd ..
done
