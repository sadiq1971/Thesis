#!/bin/bash

rd=/home/sadiq/Thesis/
f2=/home/sadiq/Thesis/NAWRIN_thesis_codes/f2.txt
scendir=/home/sadiq/Thesis/NAWRIN_thesis_codes/final_input
inforalgo=/home/sadiq/Thesis/NAWRIN_thesis_codes/test_input
scenGen=/home/sadiq/Thesis/run/scenGen
algo=/home/sadiq/Thesis/NAWRIN_thesis_codes
#remove content of f2..., scenario..
# rm -f $f2
# rm -f $scendir/*
# rm -f $inforalgo/*


echo -n "Number of Node: "
read num_nodes

echo -n "Size of the Topography: "
read max_xy

echo -n "Number of scenario: "
read sn
trange=100





# cd ns-allinone-2.34/ns-2.34/indep-utils/cmu-scen-gen/setdest
# echo "Creating Random Scenario Files.."
scenario_file_name="scen-$num_nodes-$trange-$max_xy-$max_xy-"
# for(( i=1;i<=$sn;i++))
# do
#     echo $scenario_file_name$i".out" | tee >> $f2
#     setdest -v 1 -n $num_nodes -p 300 -M 1 -t 250 -x $max_xy -y $max_xy >> $scendir/$scenario_file_name$i.out

# done
# echo "Generating input from scenario.."
# cd $scenGen
# g++ ./convertTohop.cpp
# for(( i=1;i<=$sn;i++))
# do
#     # pass three arg. input file path, output file path and #of nodes
#     ./a.out $scendir/$scenario_file_name$i.out $inforalgo/$scenario_file_name$i.out $num_nodes

# done


CACDS=/home/sadiq/Thesis/NAWRIN_thesis_codes/outCACDS
DCADS=/home/sadiq/Thesis/NAWRIN_thesis_codes/outDCADS
DP=/home/sadiq/Thesis/NAWRIN_thesis_codes/outDP
MCDS=/home/sadiq/Thesis/NAWRIN_thesis_codes/outMCDS

# rm -f $CACDS/*
# rm -f $DCADS/*
# rm -f $DP/*
# rm -f $MCDS/*


# # all files are  ready
# # run the algorithms now
# echo "Running the algorithms.."

# cd $algo
# g++ ./MCDS.cpp
# ./a.out

# g++ ./Centralized\ CACDS.cpp
# ./a.out

# g++ ./DP.cpp
# ./a.out

# g++ ./DCACDS.cpp
# ./a.out

# output files are generated...
# now run the ns simulator.... 
# files for ns2...
scenario=/home/sadiq/Thesis/run/scenario
output=/home/sadiq/Thesis/run/output.txt
run=/home/sadiq/Thesis/run
analyser=/home/sadiq/Thesis/run/Trace_Analysis
result=/home/sadiq/Thesis/result
trace=/home/sadiq/Thesis/run/wireless-flooding.tr
current_output=/home/sadiq/Thesis/run/current_output
rm -f $result/*



# echo "Running ns2 for MCDS.."
# # MCDS
# for(( i=1;i<=$sn;i++))
# do
#     cd $run
#     rm -f $scenario
#     rm -f $output
#     rm -f $current_output
#     cp $scendir/$scenario_file_name$i.out $scenario
#     # cp $MCDS/$scenario_file_name$i.out $output
#     echo $MCDS | tee >> $current_output
#     echo $MCDS/$scenario_file_name$i".out" | tee >> $current_output
#     rm -f MCDS.tr
    
#     ns flooding.tcl
#     cp $trace MCDS.tr
#     cd $analyser
#     ./Trace_Analysis >> $result/mcds

# done
# echo "Running ns2 for CACDS.."
# # CACDS
# for(( i=1;i<=$sn;i++))
# do
#     cd $run
#     rm -f $scenario
#     rm -f $output
#     rm -f current_output
#     cp $scendir/$scenario_file_name$i.out $scenario
#     # cp $CACDS/$scenario_file_name$i.out $output
#     echo $CACDS | tee >> $current_output
#     echo $CACDS/$scenario_file_name$i".out" | tee >> $current_output
#     rm -f CACDS.tr
    
#     ns flooding.tcl
#     cp $trace CACDS.tr
#     cd $analyser
#     ./Trace_Analysis >> $result/cacds

# done

echo "Running ns2 for DCADS.."
# DCADS
for(( i=1;i<=$sn;i++))
do
    cd $run
    rm -f $scenario
    rm -f $output
    rm -f $current_output
    cp $scendir/$scenario_file_name$i.out $scenario
    # cp $DCADS/$scenario_file_name$i.out0 $output
    echo "DCADS" | tee >> $current_output
    echo $inforalgo/$scenario_file_name$i".out" | tee >> $current_output
    rm -f DCACDS.tr
   
    ns flooding.tcl
    cp $trace DCADS.tr
    cd $analyser
    ./Trace_Analysis >> $result/dcads

done

echo "Running ns2 for DP.."
# DP
for(( i=1;i<=$sn;i++))
do
    cd $run
    rm -f $scenario
    rm -f $output
    rm -f $current_output
    cp $scendir/$scenario_file_name$i.out $scenario
    # cp $DP/$scenario_file_name$i.out0 $output
    echo "DP" | tee >> $current_output
    echo $inforalgo/$scenario_file_name$i".out" | tee >> $current_output
    rm -f DP.tr
    
    ns flooding.tcl
    cp $trace DP.tr
    cd $analyser
    ./Trace_Analysis >> $result/dp
done


ra=/home/sadiq/Thesis/result/resultAnalysis
cacds=/home/sadiq/Thesis/result/cacds
dcads=/home/sadiq/Thesis/result/dcads
dp=/home/sadiq/Thesis/result/dp
mcds=/home/sadiq/Thesis/result/mcds
fn=/home/sadiq/Thesis/result/final_result
rm -f $fn

cd $ra
g++ ./analysis.cpp
./a.out $mcds $cacds $dp $dcads $fn $sn
