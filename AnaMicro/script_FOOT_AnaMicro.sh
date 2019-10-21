#!/bin/bash

i=177

while (( $i <= 210 ))
do
    echo $[i]
    ./Micro_Ana -in /Volumes/Maxtor/FOOT_PROD/Regression_TMVA/Deuteri/Deu_$[i].root
    mv EMU_out.root /Volumes/Maxtor/FOOT_PROD/AnaMicro/Deu_$[i].root

(( i++ ))
done

j=133

while (( $j <= 135 ))
do
    echo $[j]

    ./Micro_Ana -in /Volumes/Maxtor/FOOT_PROD/Regression_TMVA/Protoni/Proton_$[j]_v2.root
    mv EMU_out.root /Volumes/Maxtor/FOOT_PROD/AnaMicro/Proton_$[j]_v2.root

(( j++ ))
done
