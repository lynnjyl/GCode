#! bin/bash

mkdir result
filename="./t.txt"
for i in `cat $filename`
do
		file="./result/lcss_"$i"_sort"
		echo $i
		if [ ! -f "$file" ]
		then
			echo "not existed"
			sh job_single.sh $i 10
		else
			echo "existed"
		fi
done

mv result result_10


mkdir result
filename="./t.txt"
for i in `cat $filename`
do
		file="./result/lcss_"$i"_sort"
		echo $i
		if [ ! -f "$file" ]
		then
			echo "not existed"
			sh job_single.sh $i 20
		else
			echo "existed"
		fi
done

mv result result_20


mkdir result
filename="./t.txt"
for i in `cat $filename`
do
		file="./result/lcss_"$i"_sort"
		echo $i
		if [ ! -f "$file" ]
		then
			echo "not existed"
			sh job_single.sh $i 30
		else
			echo "existed"
		fi
done

mv result result_30


mkdir result
filename="./t.txt"
for i in `cat $filename`
do
		file="./result/lcss_"$i"_sort"
		echo $i
		if [ ! -f "$file" ]
		then
			echo "not existed"
			sh job_single.sh $i 40
		else
			echo "existed"
		fi
done

mv result result_40


mkdir result
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


