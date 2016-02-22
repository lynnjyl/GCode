#! bin/bash

cosinedir=$1
lcssdir=$2
trajid=$3

cosine=$1$3"_cosine_sort"
lcss=$2"lcss_"$3"_sort"
echo $cosine
echo $lcss

#l9=$(sed -n '/0.9/=' $cosine | awk 'NR==1{print}')
l8=$(sed -n '/0\.8/=' $cosine | awk 'NR==1{print}')
l7=$(sed -n '/0\.7/=' $cosine | awk 'NR==1{print}')
l6=$(sed -n '/0\.6/=' $cosine | awk 'NR==1{print}')
l5=$(sed -n '/0\.5/=' $cosine | awk 'NR==1{print}')
l4=$(sed -n '/0\.4/=' $cosine | awk 'NR==1{print}')
l3=$(sed -n '/0\.3/=' $cosine | awk 'NR==1{print}')
l2=$(sed -n '/0\.2/=' $cosine | awk 'NR==1{print}')
l1=$(sed -n '/0\.1/=' $cosine | awk 'NR==1{print}')
l0=$(sed -n '/0\.0/=' $cosine | awk 'NR==1{print}')

l8=$(($l8-1))
echo "****** > 0.9 $l8 *****"
./jaccard $cosine $lcss $l8

l7=$(($l7-1))
echo "****** > 0.8 $l7 *****"
./jaccard $cosine $lcss $l7

l6=$(($l6-1))
echo "****** > 0.7 $l6 *****"
./jaccard $cosine $lcss $l6

l5=$(($l5-1))
echo "****** > 0.6 $l5 *****"
./jaccard $cosine $lcss $l5

l4=$(($l4-1))
echo "****** > 0.5 $l4 *****"
./jaccard $cosine $lcss $l4

l3=$(($l3-1))
echo "****** > 0.4 $l3 *****"
./jaccard $cosine $lcss $l3

l2=$(($l2-1))
echo "****** > 0.3 $l2 *****"
./jaccard $cosine $lcss $l2

l1=$(($l1-1))
echo "****** > 0.2 $l1 *****"
./jaccard $cosine $lcss $l1

l0=$(($l0-1))
echo "****** > 0.1 $l0 *****"
./jaccard $cosine $lcss $l0
