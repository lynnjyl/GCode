#! bin/bash

trajid="22043"

./main $trajid

cd ./result

cosine=$trajid"_cosine"
cosinesort=$cosine"_sort"
product=$trajid"_product"
productsort=$product"_sort"

sort -n -r -k 2 $cosine > $cosinesort
sort -n -r -k 2 $product > $productsort