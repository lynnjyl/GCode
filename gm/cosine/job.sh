#! bin/bash



./main 12639
./main 22019
./main 22026
./main 22176
./main 22246
./main 22258
./main 24090

cd ./result
filelist=$(ls)
for kfile in $filelist
do
	file=$kfile"_sort"
	sort -r -n -k 2 $kfile > $file
done