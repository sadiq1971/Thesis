#!/bin/bash

rd=/home/sadiq/Thesis/
f2=/home/sadiq/Thesis/NAWRIN_thesis_codes/f2.txt
scendir=/home/sadiq/Thesis/NAWRIN_thesis_codes/final_input 
inforalgo=/home/sadiq/Thesis/NAWRIN_thesis_codes/test_input 
#remove content of f2..., scenario..
rm -f $f2
rm -f $scendir/*
rm -f $inforalgo/*


echo -n "Number of Node: "
read num_nodes

echo -n "Size of the Topography: "
read max_xy

echo -n "Number of scenario: "
read sn
trange=250

#echo " $num_nodes $max_xy $sn"
pwd



cd ns-allinone-2.34/ns-2.34/indep-utils/cmu-scen-gen/setdest
echo "Creating Random Scenario Files"
scenario_file_name="scen-$num_nodes-$trange-$max_xy-$max_xy-"
for(( i=1;i<=$sn;i++))
do
    echo $scenario_file_name$i".out" | tee >> $f2
    setdest -v 1 -n $num_nodes -p 300 -M 1 -t 250 -x $max_xy -y $max_xy >> $scendir/$scenario_file_name$i.out

done
