#! bin/bash

id=1;

filename="../query.txt"
for i in `cat $filename`
do
#	r=$((id%2));
#	if [ $r -eq 1 ]
#		then
#		echo $id $i
		file="./result/lcss_"$i"_sort"
		echo $file
		if [ ! -f "$file" ]
		then
			echo "not existed"
			sh job_single.sh $i
		else
			echo "existed"
		fi
#	fi
	# echo $i
#	id=$((id+1));

#	if [ $id -eq 200 ]
#		then
#		break
#	fi

done

