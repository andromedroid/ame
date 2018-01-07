#!/usr/bin/env python
# coding: utf-8

"""
flash :
  $	uflash [name].py
"""

from microbit import display as dp
from microbit import Image
from microbit import button_a as ba
from microbit import button_b as bb


def	init() :

	pass

def	hdr_ba() :

	dp.show( Image.HAPPY)

def	hdr_bb() :

	dp.clear()

def	loop() :

	dp.show( Image.SAD)


if __name__ == "__main__" :

	init()

	while True :
		if ba.is_pressed() :
			hdr_ba()
		elif bb.is_pressed() :
			hdr_bb()
		else :
			loop()
