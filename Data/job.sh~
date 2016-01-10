#! bin/bash

cd ./trajectory
filelist=$(ls)
cd ../subtraj

trajid=1;

for kfile in $filelist
do
	file="../trajectory/"$kfile
	lines=$(wc -l $file|awk '{print $1}')
	k=$((lines/120))
	
	if [ $k -lt 10 ] 
	then
		last=$trajid"_0"$k
	else
		last=$trajid"_"$k
	fi
	tail -n 120 $file > $last
	trajid=$((trajid+1))
done












cd ../trajectory
lines=$(wc -l 00020081023025304.plt | awk '{print $1}')
echo $lines
k=$((lines/120+1))
echo $k
# if [ $k -lt 10 ] 
# then
# 	filename=$trajid"_0"$k
# else
# 	filename=$trajid"_"$k
# fi
# echo $filename

# tail -n 120 00020081023025304.plt  > ../$filename
# for kfile in $filelist
# do

# done
