#/bin/bash

# this script prevents to remove / and ~.
# please rename "rm.sh" -> "rm" at first.

#if [[ "$1" != "-r" && "$1" != "-rf" ]]
if [ "$1" != "-r" -a "$1" != "-rf" ]
then
#	echo "no risk"
	/bin/rm $@
	exit $?
fi

for PARAM in $@
do
	echo $PARAM
#	if [[ "$PARAM" == "/" -o "$PARAM" == "$HOME" ]]
	if [ "$PARAM" == "/" -o "$PARAM" == "$HOME" ]
	then
		echo "I cannot do it."
		exit 1
	fi
done

#echo "execute"
/bin/rm $@
exit $?
