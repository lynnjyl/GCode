#! bin/bash

# mode=$1

# ./jaccard "./result/12639_"$mode"_sort" ../../lcss/result/candidate_1184_07sort 68
# ./jaccard "./result/22019_"$mode"_sort" ../../lcss/result/candidate_13016_70sort 196
# ./jaccard "./result/22026_"$mode"_sort" ../../lcss/result/candidate_13019_00sort 49
# ./jaccard "./result/22176_"$mode"_sort" ../../lcss/result/candidate_13047_02sort 225
# ./jaccard "./result/22246_"$mode"_sort" ../../lcss/result/candidate_13060_02sort 204
# ./jaccard "./result/22258_"$mode"_sort" ../../lcss/result/candidate_13066_00sort 162
# ./jaccard "./result/24090_"$mode"_sort" ../../lcss/result/candidate_13324_02sort 42

cd ./result
filelist=$(ls)

for ((i=1;i<=13000;i++))
do
	echo $i
	#old=$i"_cosine"
	new=$i"_cosine_sort"
	#sort -r -n -k 2 $old > $new
	#rm $old
	var=$(grep -n '\(0\.\)'[0-5] $new | awk -F':' 'NR==1{print $1}')
	echo $i $var >>../record_0.6.txt
	var=$(grep -n '\(0\.\)'[0-6] $new | awk -F':' 'NR==1{print $1}')
	echo $i $var >>../record_0.7.txt
	var=$(grep -n '\(0\.\)'[0-7] $new | awk -F':' 'NR==1{print $1}')
	echo $i $var >>../record_0.8.txt
	var=$(grep -n '\(0\.\)'[0-8] $new | awk -F':' 'NR==1{print $1}')
	echo $i $var >>../record_0.9.txt
done
