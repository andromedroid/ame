#!/usr/bin/env python
# coding: utf-8

"""
flash :
  $	uflash [name].py
"""

from microbit import *


def	init() :

	display.scroll( "Hello, World !")

#	display.show( Image.HAPPY)
	display.show( Image.HEART)


if __name__ == "__main__" :

	init()

#	while True :
#		loop()
