#!/bin/bash

if [[ $1 =~ [0-9]-[0-9] ]];
then
	echo "To jest prawidlowy kod pocztowy"
else
	echo "Ten kod nie jest prawidlowym kodem pocztowym"
fi
