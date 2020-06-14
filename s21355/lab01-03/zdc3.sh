#!/bin/bash

if [[ $1 =~ ["@"] && $1 =~ ["."] ]]
then
	echo "To jest poprawny adres mailowy"
else
	echo "To nie jest prawidlowy adres mailowy"
fi
