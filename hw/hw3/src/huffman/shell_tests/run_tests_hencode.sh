#!/bin/bash
for file in $( ls ~/CPE357/hw/hw3/src/huffman/hencode_tests/inputs/* ); do
	 echo -n "Testing with ${file} -- "
	 BASE=`basename ${file} .in`
	 #program testing

	 ../hencode ${file} ../hencode_tests/outputs/${BASE}.out

	 if [ $? -eq 0 ]; then
		 echo "succeeded"

	 fi


done



