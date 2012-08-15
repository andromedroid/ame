#!/bin/bash

#num =0
#num= 0
num=0

for argv
do
#	num=$num + 1
	num=`expr $num + 1`
	echo "No.$num arg is \"$argv\""
done

echo
num=0

for item
do
#	num=$num + 1
	num=`expr $num + 1`
	echo "No.$num arg is \"$item\""
done
