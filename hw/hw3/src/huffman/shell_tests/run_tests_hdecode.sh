#!/bin/bash
for file in $( ls ~/CPE357/hw/hw3/src/huffman/hdecode_tests/inputs/* ); do
	 echo -n "Testing with ${file} -- "
	 BASE=`basename ${file} .in`
	 #program testing

	 ../hdecode ${file} ../hdecode_tests/outputs/${BASE}.out

	 if [ $? -eq 0 ]; then
		 echo "succeeded"

	 fi


done



