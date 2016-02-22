#! bin/bash

for ((i=40001;i<=50000;i++))
do
	echo $i
	./main $i
	file='./result/'$i'_cosine'
	result=$file'_sort'
	sort -n -r -k 2 $file > $result
	count=$(sed -n '/0\.5/=' $result | awk 'NR==1{print}')
	echo $i $count >> ../count.txt
	rm $file
	rm './result/'$i'_product'
	rm $result
done
