#!/bin/bash

if [ -f $1 ]
then
	echo "\"$1\" is exist."
else
	echo "\"$1\" is not exist."
fi
