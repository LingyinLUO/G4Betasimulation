#!/bin/bash

for((i=0;i<6;i++))
do
 n=$((i*2))
 macfile=run1.mac
 filename=Al-$n.root
 length=$(echo "scale=2;$i*0.2" | bc)
 
 str1=Althick
 str2="/B1detector/Althick $length mm"

 sed -i "/$str1/c$str2" $macfile
 
 ./exampleB1 $macfile && mv test1.root $filename

done
