#!/bin/bash
file[0]="29538"
# file[1]="14292_41"
# file[2]="1184_07"
# file[3]="10654_00"
# file[4]="14294_06"
# file[5]="13258_08"
# file[6]="13324_02"
# file[7]="13060_02"
# file[8]="11099_9352"
# file[9]="11083_05"
# file[10]="13047_02"
# file[11]="14294_53"
# file[12]="13378_00"
# file[13]="14297_9025
# file[14]="13066_00"
# file[15]="13016_70"
# file[16]="12087_33"
# file[17]="14297_53"
# file[18]="12771_01"
# file[19]="13019_00"
for i in 0 
do

trajid=1;

queryfile="../Data/new/"${file[i]}
echo $queryfile

cd ../Data/newtraj/
filelist=$(ls)
cd ../../lcss

for kfile in $filelist
do
	echo $trajid
	filename="../Data/newtraj/"$kfile
	echo $filename
	./lcss $queryfile $filename $kfile 10 30
	# trajid=$((trajid+1))
done

result="./result/lcss_"${file[i]}
sorted=$result"_sort"
sort -n -r -k 4 $result > $sorted
rm $result
# echo "*********"${file[i]}"**********"
# cat $sorted | grep -n '\(0\.\)'[0-4] | awk 'NR==1{print}'
# cat $sorted | grep -n '\(0\.\)'[0-5] | awk 'NR==1{print}'
# cat $sorted | grep -n '\(0\.\)'[0-6] | awk 'NR==1{print}'
# cat $sorted | grep -n '\(0\.\)'[0-7] | awk 'NR==1{print}'
# cat $sorted | grep -n '\(0\.\)'[0-8] | awk 'NR==1{print}'
# cat $sorted | grep -n '\(0\.\)'[0-9] | awk 'NR==1{print}'

done



