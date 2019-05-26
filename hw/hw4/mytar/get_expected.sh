#!/bin/bash
for file in $( ls inputs/header/* ); do
	BASE=`basename ${file}`
	echo -n "Testing with ${file} -- "
	~pn-cs357/demos/mytar cf expected/header/${file} inputs/header/${file}
done
