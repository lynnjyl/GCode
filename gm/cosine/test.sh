#!bin/bash

cd  ./result

for ((i=12001;i<=13000;i++))
do
	echo $i
	old=$i"_cosine"
	new=$i"_cosine_sort"
	sort -r -n -k 2 $old > $new
	rm $old
	var=$(grep -n '\(0\.\)'[0-4] $new | awk -F':' 'NR==1{print $1}')
	echo $i $var >>../record0.5.txt
done
