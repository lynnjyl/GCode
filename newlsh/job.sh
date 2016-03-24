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


# for ((k=1;k<=1;k=k+1))
# do
# 	./r 1 1000 15 6
# 	./recall 0.6
# 	cd result
# 	rm *
# 	cd ..
# done
for ((i=20 ;i<=20;i=i+5))
do
	for ((j=1000;j<=5000;j=j+1000))
	do
		for ((k=1;k<=10;k=k+1))
		do
			./r 1 $j $i 6
			./recall 0.6
			cd result
			rm *
			cd ..
		done
		echo $i $j
	done
	
done


