#!/bin/bash
for file in $( ls inputs/* ); do
	 echo -n "Testing with ${file} -- "
	 BASE=`basename ${file} .in`
	 #program testing

	 ~pn-cs357/demos/./hencode ${file} expected/${BASE}.expected

	 if [ $? -eq 0 ]; then
		 echo "succeeded"

	 fi

	 #test binary

	 diff `xxd outputs/${BASE}.out` `xxd expected/${BASE}.expected` 

done



