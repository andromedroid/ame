#!/usr/bin/env python
# coding: utf-8

"""
refered :
  import radio
	http://microbit-micropython.readthedocs.io/ja/latest/radio.html
"""

from microbit import button_a as ba
from microbit import button_b as bb
from microbit import sleep

import radio


def	hdr_ba() :

	radio.send( 'run')
	sleep( 200)

def	hdr_bb() :

	radio.send( 'back')
	sleep( 200)

def	init() :

	radio.on()

def	loop() :

	pass


if __name__ == "__main__" :

	init()

	while True :
		if ba.is_pressed() :
			hdr_ba()

		elif bb.is_pressed() :	
			hdr_bb()

		else :
			loop()
