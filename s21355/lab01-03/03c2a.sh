#!/bin/bash

for((i = 10; i>1; i--));
	do if ((${i}%2==0))
	then
		echo $i
fi
done
