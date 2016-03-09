#!/bin/bash
num=0
for ((i=0;i<10;i++))
do
	path="./00${i}"
	cd $path
	k=$(ls|wc -l)
	num=$((num+k))
	cd ..
done
for ((i=10;i<100;i++))
do
	path="./0${i}"
	cd $path
	k=$(ls|wc -l)
	num=$((num+k))
	cd ..
done
for ((i=100;i<182;i++))
do
	path="./${i}"
	cd $path
	k=$(ls|wc -l)
	num=$((num+k))
	cd ..
done
echo $num
