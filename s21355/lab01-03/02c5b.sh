#!/bin/bash

echo="Wpisz tekst"
read a
echo ${a:0:1}
echo ${a: -1}
case $a in
	*SOP*)
		echo -e '\\e[32mSOP\\e[0m'
	;;
esac
