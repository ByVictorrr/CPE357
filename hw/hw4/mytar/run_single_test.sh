#!/bin/bash
if [ -z "$1" ]
then
	echo "provide an option to the shell script [ctxvS]f"
else
		TEST="TreeOneLevel"
		make clean && make 
		echo "passed in option $1"
		./mytar $1 outputs/${TEST} inputs/${TEST}
		if [ -z "$2" ]
		then
			echo "provide a second argument for valgrind results"

		else
			echo "printing valgrind"
			valgrind ./mytar $1 outputs/${TEST} inputs/${TEST}
			echo "check outputs/test1.tar for the results"
			cat outputs/${TEST}.tar
		fi
fi

