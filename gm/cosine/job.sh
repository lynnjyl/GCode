#! bin/bash



./main ../../../GData/mix_230.txt 12639 45
./main ../../../GData/mix_230.txt 22019 45
./main ../../../GData/mix_230.txt 22026 45
./main ../../../GData/mix_230.txt 22176 45
./main ../../../GData/mix_230.txt 22246 45
./main ../../../GData/mix_230.txt 22258 45
./main ../../../GData/mix_230.txt 24090 45

cd ./result
filelist=$(ls)
for kfile in $filelist
do
	file=$kfile"_sort"
	sort -r -n -k 2 $kfile > $file
done
