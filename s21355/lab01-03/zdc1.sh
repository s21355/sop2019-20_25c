#!/bin/bash

if [[ $1 =~ [A-Z]+[a-z] ]]
then
	echo "Tekst jest poprawnie napisanym polskim imieniem"
else
	echo "Tekst nie jest poprawnie napisanym polskim imieniem"
fi
