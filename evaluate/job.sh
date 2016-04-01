#! bin/bash

cos=$1
lcss=$2

id=1;

filename="../gm/cosine/query.txt"
for i in `cat $filename`
do
	r=$((id%2));
	if [ $r -eq 1 ]
		then
		#echo $id $i
		#./eval $i
		#./avglcss $i
		./recall 0.6 0.8 $i $cos $lcss
	fi
	# echo $i
	id=$((id+1));

	if [ $id -eq 274 ]
		then
		break
	fi

done

