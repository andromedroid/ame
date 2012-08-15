#!/bin/bash

echo "\"$1\" is 1st arg."

echo "all args are \"$@\"."
echo "all args are \"$*\"."

echo "args num is '$#'."

./00num.sh $@
./00num.sh $*
