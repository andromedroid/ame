# coding: utf-8

"""
flash :
  $	uflash [name].py
"""

from microbit import sleep as msleep
from microbit import button_a as ba
from microbit import button_b as bb

from microbit import display as dp
from microbit import Image

import radio

MEMBERS		= 4
MY_ID		= 1				# define : 1 ~ MEMBERS
CYCLE_MS	= 100
WAIT_MS		= 1000


class GazellRelay :

	myid	= 0

	def	__init__( self, myid) :

		radio.on()
		self.myid	= myid

	def	get_id( self) :

		return	self.myid

	def	send( self, cmd) :

		sendstr	= '{}:{}'.format( self.myid + 1, str( cmd))
		print( sendstr)

		radio.send( sendstr)

	def	recv( self) :

		recvstr	= radio.receive()
		if recvstr is None :
			return	None, None

		print( recvstr)

		items	= recvstr.split( ':')
		if len( items) != 2 :
			return	None, recvstr

		print( items)

		return	items

gr	= GazellRelay( MY_ID)


def	init() :

	dp.show( Image.SAD)

def	hdr_ba() :

	if gr.get_id() == 1 :
		dp.show( Image.HAPPY)
		gr.send( 'fire')

def	hdr_bb() :

	pass

def	loop() :

	r_id, cmd	= gr.recv()
	if r_id is None :
		return

	if cmd == 'finish' :
		dp.show( Image.HEART)
		return				# END

	if int( r_id) != gr.get_id() :
		return				# it's not my biz.

	if cmd == 'fire' :
		msleep( WAIT_MS)

		if gr.get_id() != MEMBERS :
			dp.show( Image.HAPPY)
			gr.send( cmd)

		else :				# I am anchor :)
			dp.show( Image.HEART)
			gr.send( 'finish')


if __name__ == "__main__" :

	init()

	while True :
		if ba.is_pressed() :
			hdr_ba()

		elif bb.is_pressed() :
			hdr_bb()

		else :
			loop()

		msleep( CYCLE_MS)
