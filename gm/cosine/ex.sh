#! bin/bash
index=$1
traj=$2
num=$3

file="./result_"$index"/"$traj"_product_sort"
lcss="../../lcss/result_120_30/lcss_"$traj"_sort"
#./j2 $file $lcss $num $num

for ((i=100;i<=900;i=i+50))
do
	./j2 $file $lcss $i $i
done
