#! bin/bash

id=1;

filename="./query.txt"
for i in `cat $filename`
do
#	r=$((id%2));
#	if [ $r -eq 1 ]
#		then
		file="./result/"$i"_cosine_sort"
		echo $id $i
		if [ ! -f "$file" ]
		then
			echo "not existed"
			./main2 ../../../GData/mix_309.txt $i 45
			result="./result/"$i"_cosine"
			sorted=$result"_sort"
			sort -n -r -k 2 $result > $sorted
			rm $result
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