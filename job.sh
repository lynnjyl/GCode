#! bin/bash

for ((i=0;i<30;i++))
do
	cd ./LSH
	./m 1000 15822
	cd ..
	./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt
done