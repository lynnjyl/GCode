#!bin/sh

for ((k=100;k<101;k++))
do
	path="../result/${k}"
	cd $path
	filelist=$(ls)
	cd ../../DeleteError
	for kfile in $filelist
	do
		./main $path"/"$kfile
	done
done
