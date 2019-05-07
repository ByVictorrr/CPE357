#!/bin/bash


for getInput in $( ls ~/CPE357/hw/hw3/src/hencode/expected/* ); do
	echo -n "Testing with ${getInput} -- "
	getBase=`basename ${getInput} .expected`
	#get make hardlink


	if [ -e ~/CPE357/hw/hw3/src/hdecode/inputs/${getBase} ];
	then	
		echo "hi"
		rm ~/CPE357/hw/hw3/src/hdecode/inputs/${getBase}
	fi

	ln ${getInput} ~/CPE357/hw/hw3/src/hdecode/inputs/${getBase}

done

for file in $( ls ~/CPE357/hw/hw3/src/hdecode/inputs/* ); do
	 echo -n "Testing with ${file} -- "
	 BASE=`basename ${file} .in`
	 #program testing

	 ~pn-cs357/demos/./hdecode ${file} ~/CPE357/hw/hw3/src/hdecode/expected/${BASE}.expected

	 if [ $? -eq 0 ]; then
		 echo "succeeded"

	 fi


done



