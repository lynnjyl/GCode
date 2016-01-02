#! bin/bash


for ((i=0;i<10;i++))
do
cd ./newlsh
./r 1 1000 10
cd ../dtw
./eval >> log
cd ..
done