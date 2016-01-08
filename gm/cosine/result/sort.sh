#! bin/bash

filelist=$(ls)

for kfile  in $filelist
do 
	filename=$kfile"_sort"
	sort -r -n -k 2 $kfile  > $filename

done