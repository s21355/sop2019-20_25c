#!/bin/bash

file="$(basename $0)"
if [[ "${file##*.}" = "sh" ]]
then
	echo "'${file}' ma rozszerzenie .sh"
else
	mv $0 ${0}.sh
fi
