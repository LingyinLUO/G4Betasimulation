#!/bin/bash

for((i=0;i<8;i++))
do
 macfile=run1.mac
 filename=Reletivity-$i.root
 
 window=$((i+1))

 str1="\/B1generator\/SetPosition"
 str2="/B1generator/SetPosition $window"

 sed -i "/$str1/c$str2" $macfile
 
 str3="\/B1detector\/SetPosition"
 str4="/B1detector/SetPosition $window"
 sed -i "/$str3/c$str4" $macfile

 ./exampleB1 $macfile && mv test1.root $filename

done
