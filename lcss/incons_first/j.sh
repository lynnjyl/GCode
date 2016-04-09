#! bin/bash

id=1;

filename="./t.txt"
for i in `cat $filename`
do
		file="./result/lcss_"$i"_sort"
		echo $i
		if [ ! -f "$file" ]
		then
			echo "not existed"
			sh job_single.sh $i 50
		else
			echo "existed"
		fi
done

mv result result_50


