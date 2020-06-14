#!/bin/bash

a=Ala
b=kot
echo $a ma ${b}a, $b ma ${a} | sed s/a$/e/g

