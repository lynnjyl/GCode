#! bin/bash

for ((i=1;i<58182;i++))
do
	echo $i
	./addnoise 10 $i
done
echo "10 done"
for ((i=1;i<58182;i++))
do
	echo $i
	./addnoise 20 $i
done
echo "20 done"
for ((i=1;i<58182;i++))
do
	echo $i
	./addnoise 30 $i
done
echo "30 done"
for ((i=1;i<58182;i++))
do
	echo $i
	./addnoise 40 $i
done
echo "40 done"
for ((i=1;i<58182;i++))
do
	echo $i
	./addnoise 50 $i
done
echo "50 done"
