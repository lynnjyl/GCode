#! bin/bash



# ./main ../../../GData/mix_233.txt 12639 45
# ./main ../../../GData/mix_233.txt 22019 45
# ./main ../../../GData/mix_233.txt 22026 45
# ./main ../../../GData/mix_233.txt 22176 45
# ./main ../../../GData/mix_233.txt 22246 45
# ./main ../../../GData/mix_233.txt 22258 45
# ./main ../../../GData/mix_233.txt 24090 45

# cd ./result
# filelist=$(ls)
# for kfile in $filelist
# do
# 	file=$kfile"_sort"
# 	sort -r -n -k 2 $kfile > $file
# done


for ((k=0;k<100;k++))
do
id=$((($RANDOM%58181)+1))
echo $id

./main ../../../GData/mix_308.txt $id 45
cd ./result
old=$id"_cosine"
new=$id"_cosine_sort"
sort -r -n -k 2 $old > $new
rm $old

# echo "*********"$id"**********"
# cat $new | grep -n '\(0\.\)'[0-4] | awk 'NR==1{print}'
# cat $new | grep -n '\(0\.\)'[0-5] | awk 'NR==1{print}'
# cat $new | grep -n '\(0\.\)'[0-6] | awk 'NR==1{print}'
# cat $new | grep -n '\(0\.\)'[0-7] | awk 'NR==1{print}'
# cat $new | grep -n '\(0\.\)'[0-8] | awk 'NR==1{print}'
# cat $new | grep -n '\(0\.\)'[0-9] | awk 'NR==1{print}'
cd ..

done
