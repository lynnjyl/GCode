#! bin/bash

#sh job_single.sh 11087_04
#sh job_single.sh 14292_41
#sh job_single.sh 1184_07
#sh job_single.sh 10654_00
#sh job_single.sh 14294_06
#sh job_single.sh 13258_08
#sh job_single.sh 13324_02
#sh job_single.sh 13060_02
#sh job_single.sh 11099_9352
#sh job_single.sh 11083_05
#sh job_single.sh 13047_02
#sh job_single.sh 14294_53
#sh job_single.sh 13378_00
#sh job_single.sh 14297_9025
#sh job_single.sh 13066_00
#sh job_single.sh 13016_70
#sh job_single.sh 12087_33
#sh job_single.sh 14297_53
#sh job_single.sh 12771_01
#sh job_single.sh 13019_00
# sh job_single.sh 2145
# sh job_single.sh 30459
# sh job_single.sh 29538
# sh job_single.sh 2797
# sh job_single.sh 8010
# sh job_single.sh 13311
# sh job_single.sh 12063
# sh job_single.sh 30878
# sh job_single.sh 3423
# sh job_single.sh 30717
# sh job_single.sh 23269
# sh job_single.sh 18557
# sh job_single.sh 5664

id=1;

filename="../gm/cosine/record_0.8.txt"
for i in `cat $filename`
do
	r=$((id%2));
	if [ $r -eq 1 ]
		then
		echo $id $i
		file="./result/lcss_"$i"_sort"
		echo $file
		if [ ! -f "$file" ]
		then
			echo "not existed"
			sh job_single.sh $i
		else
			echo "existed"
		fi
	fi
	# echo $i
	id=$((id+1));

	if [ $id -eq 200 ]
		then
		break
	fi

done

