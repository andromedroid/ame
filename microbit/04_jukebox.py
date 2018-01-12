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
from microbit import uart
import music


def	init() :

	uart.init( baudrate = 115200)

	tpl	= (
		music.BA_DING,
		music.JUMP_UP,
		music.JUMP_DOWN,
		music.POWER_UP,
		music.POWER_DOWN,
		music.BADDY,
		music.RINGTONE,
		music.WAWAWAWAA,
		music.PUNCHLINE,
		music.DADADADUM,
		music.CHASE,
		music.ENTERTAINER,
		music.PRELUDE,
		music.BIRTHDAY,
		music.WEDDING,
		music.FUNERAL,
		music.FUNK,
		music.BLUES,
		music.PYTHON,
		music.ODE,
		music.NYAN
	)

	return	tpl

def	hdr_ba( jukebox) :

	dp.show( Image.HAPPY)
#	music.play( music.NYAN)
	music.play( jukebox)

def	hdr_bb( cnt, limit) :

	if limit == cnt :
		cnt	= 0
	else :
		cnt	= cnt + 1

	uart.write( str( cnt))
	dp.scroll( str( cnt), delay = 80)

	return	cnt

def	loop() :

	dp.show( Image.SAD)


if __name__ == "__main__" :

	tpl	= init()
	cnt	= 0
	lim	= len( tpl) - 1

	while True :
		if ba.is_pressed() :
			hdr_ba( tpl[cnt])

		elif bb.is_pressed() :
			cnt	= hdr_bb( cnt, lim)

		else :
			loop()
