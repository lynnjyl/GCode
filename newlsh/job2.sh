#! bin/bash

# id=1;

# filename="./query.txt"
# for i in `cat $filename`
# do
# 	# ./recall 0.6 $i
# 	# echo $i
# 	r=$((id%2));
# 	if [ $r -eq 1 ]
# 		then
# 		#echo $id $i
# 		#./eval $i
# 		#./avglcss $i
# 		./recall 0.6 $i
# 	fi
# 	# echo $i
# 	id=$((id+1));

# 	if [ $id -eq 200 ]
# 		then
# 		break
# 	fi

# done

for ((i=1;i<=10;i++))
do
	./r 1 1000 5 6
	./recall 0.6
	cd result
	rm *
	cd ..
done

