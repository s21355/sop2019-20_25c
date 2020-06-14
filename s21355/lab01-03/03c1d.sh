#!/bin/bash

p=$(find . -maxdepth 1 -type f | wc -l)
if [ $p -gt 5 ]
then
	echo "W biezacym katalogu jest wiecej niz 5 plikow"
fi
