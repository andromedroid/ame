#!/bin/bash

echo "is it sunny ? [y|n]"
read sunny

case $sunny in
	y)
		echo "it is sunny."
		;;
	n)
		echo "is it rainy ?"
		read rainy

		case $rainy in
			y)
				echo "it is rainy."
				;;
			n)
				echo "it is cloudy."
				;;
			*)
				echo "your input is wrong."
				;;
		esac
		;;
	*)
		echo "your input is wrong."
		;;
esac
