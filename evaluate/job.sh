#! bin/bash

id=1;

filename="../gm/cosine/record_0.8.txt"
for i in `cat $filename`
do
	r=$((id%2));
	if [ $r -eq 1 ]
		then
		#echo $id $i
		./eval $i
		#./avglcss $i
	fi
	# echo $i
	id=$((id+1));

	if [ $id -eq 200 ]
		then
		break
	fi

done

