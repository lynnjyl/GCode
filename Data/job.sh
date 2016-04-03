#! bin/bash

for ((i=1;i<58181;i++))
do
	echo $i
	./addnoise 50 $i
done