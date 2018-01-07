#!/usr/bin/env python
# coding: utf-8

"""
flash :
  $	uflash [name].py
"""

from microbit import uart


def	init() :

	uart.init( baudrate = 115200)

	uart.write( "Hello World !\r\n")

def	loop() :

#	words	= uart.readline()
	word	= uart.read()

	if word is None :
		return

#	uart.write( str( len( word)))
#	uart.write( str( type( word)))
#	uart.write( str( int.from_bytes( word, 'big')))
	uart.write( word)

	if int.from_bytes( word, 'big') == 0x0D :
		uart.write( '\n')


if __name__ == "__main__" :

	init()

	while True :
		loop()

#		from microbit import sleep
#		uart.write( "Hello World !\r\n")
#		sleep( 1000)
