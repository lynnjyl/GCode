#!/bin/bash

trajid=1;
<<<<<<< HEAD
queryfile="../result/15320100127234004.plt"
=======
queryfile="00020081023025304.plt"
>>>>>>> c60ec2d1794433039f68350acbc812a72adef774

cd ../result/
filelist=$(ls)
cd ../dtw

for kfile in $filelist
do
<<<<<<< HEAD
=======
	echo $trajid
>>>>>>> c60ec2d1794433039f68350acbc812a72adef774
	filename="../result/"$kfile
	./dtw $queryfile $filename $trajid
	trajid=$((trajid+1))
done
<<<<<<< HEAD

:<<BLOCK
for kfile in $filelist
do
	trajid=1
	queryfile="../result/"$kfile
	for jfile in $filelist
	do
		filename="../result/"$jfile
		./dtw $queryfile $filename $trajid
		trajid=$((trajid+1))
	done
	
done
BLOCK
=======
>>>>>>> c60ec2d1794433039f68350acbc812a72adef774
