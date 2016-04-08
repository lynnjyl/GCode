#!bin/bash


for((i=4;i<=17;i++))
do
	mkdir result
	dir="../../../GData/mix_"$i".txt"
	./main3 $dir query.txt 45
	sh test.sh
	new="result_"$i
	mv result $new
done
