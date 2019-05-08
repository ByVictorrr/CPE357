#!/bin/bash
for file in $( ls ~/CPE357/hw/hw3/src/hencode/inputs/* ); do
	 echo -n "Testing with ${file} -- "
	 BASE=`basename ${file} .in`
	 #program testing

	 ~pn-cs357/demos/./hencode ${file} ~/CPE357/hw/hw3/src/hencode/expected/${BASE}.expected

	 if [ $? -eq 0 ]; then
		 echo "succeeded"

	 fi


done



