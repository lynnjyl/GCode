#! bin/bash

for ((i=0;i<50;i++))
do
	cd ./LSH
	./m1200 1000 15822
	cd ..
	./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 1200.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m1400 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt  >> 1400.txt
done


for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m1600 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 1600.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m1800 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 1800.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m2000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 2000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m3000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 3000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m4000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 4000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m5000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 5000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m6000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 6000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m7000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 7000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m8000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 8000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m9000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 9000.txt
done

for ((i=0;i<50;i++))
do
        cd ./LSH
        ./m10000 1000 15822
        cd ..
        ./dtw/eval 300 ./dtw/RateResult/candidate_15320100127234004_sort.plt ./LSH/RbsLsh/cant_15822.txt >> 10000.txt
done
