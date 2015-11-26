#! bin/bash

for ((i=0;i<50;i++))
do
	cd ./LSH
	./m600 1000 15822
	cd ..
	./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 600.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m800 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt  >> 800.txt
done


for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m1000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 1000.txt
done
