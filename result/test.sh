#!/bin/sh
for kfile in * 
do
	tmp=`basename $kfile`
	if [ $tmp != "test.sh" ];then
		cd ${tmp}
		for aFile in *
		do
			tmpFile=`basename $aFile`
    			lines=$(wc -l ${tmpFile} | awk '{print $1}')
			if [ $lines -gt 92644 ];then  
    				echo $lines  
			fi  
		done
	fi
	cd ..
done
