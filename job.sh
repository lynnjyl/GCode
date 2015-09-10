#! bin/bash

for ((i=100;i<182;i++))
do
    Number="${i}"
    mkdir ./result/${Number}
    ./g ${Number} ~/Downloads/Geolife\ Trajectories\ 1.3/Data/
done