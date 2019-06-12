"""
based on uiflow-firmware v1.3.2
"""

import random

from m5stack import *
from m5ui import *
from uiflow import *


BLACK	= 0x000000
RED		= 0xFF0000
GREEN	= 0x00FF00
BLUE	= 0x0000FF
WHITE	= 0xFFFFFF
#COLOR	= 0x33CC00
COLOR	= 0x00CCFF


class Amida :

	objsize		= 10
	lines		= [0] * 10
	lines_rect	= [None] * 10
	bullet		= None

	def	__init__( self) :

		for ii in range( len( self.lines)) :
#			self.lines[ii]		= ii % 2 + 1												# for debug.
			self.lines[ii]		= random.randint( 0, 2)
			if self.lines[ii] > 0 :
				genten	= (64 + (self.lines[ii] - 1) * 100)
				print( "genten {:2d}: {}".format( ii, genten))
#				self.lines_rect[ii]	= M5Rect( genten, 56 + ii * 15, 100, 1, WHITE, WHITE)	# for debug.
				self.lines_rect[ii]	= M5Rect( genten, 56 + ii * 15, 100, 1, BLACK, BLACK)

	def	drawVert( self, obj, xpos, ypos, move, step = 1) :

		for ii in range( 0, move, step) :
			obj.setPosition( xpos, ypos + ii)

		return	ypos + move

	def	drawHori( self, obj, xpos, ypos, move, step = 1) :

		for ii in range( 0, move, step) :
			obj.setPosition( xpos + ii, ypos)

		return	xpos + move

	def	__gogo_bullet( self, post, ypos, line) :

		xpos	= 64 + post * 100

		if line == 1 :
			if post == 0 :
				xpos	= self.drawHori( self.bullet, xpos, ypos, 100)
				post	+= 1

			elif post == 1 :
				xpos	= self.drawHori( self.bullet, xpos, ypos, -100, -1)
				post	-= 1

			else :	# post == 2
				pass

		elif line == 2 :
			if post == 0 :
				pass

			elif post == 1 :
				xpos	= self.drawHori( self.bullet, xpos, ypos, 100)
				post	+= 1

			else :	# post == 2
				xpos	= self.drawHori( self.bullet, xpos, ypos, -100, -1)
				post	-= 1

		else :	# line == 0
			pass

		ypos	= self.drawVert( self.bullet, xpos, ypos, 15)

		return	post, ypos

	def	ready( self) :

		for ii in range( len( self.lines)) :
			if self.lines_rect[ii] is not None :
				self.lines_rect[ii].setBorderColor( WHITE)

	def	start( self, post, shield) :
		'''
		fix start position
		int( post)	: 0 ~ 2
		'''

		genten	= (64 + post * 100) - self.objsize
		rect0	= M5Rect( genten,  0, self.objsize * 2, self.objsize * 2, COLOR, COLOR)

		# bullet
		xpos	= 64 + post * 100
		ypos	= 30
		self.bullet	= M5Circle( xpos, ypos, self.objsize, BLACK, BLACK)

		self.bullet.setBgColor( COLOR)

		ypos	= self.drawVert( self.bullet, xpos, ypos, 26)	# to y: 56.
		for line in self.lines :
			post, ypos	= self.__gogo_bullet( post, ypos, line)
#			wait_ms( 100)

		self.bullet.setBgColor( BLACK)

		if post == shield :
			return	True

		return	False


def	RGB( color, step = 2) :

	for ii in range( 0, 256, step) :
		rgb.setBrightness( ii)
		rgb.setColorAll( color)

	for ii in range( 255, -1, -step) :
		rgb.setBrightness( ii)
		rgb.setColorAll( color)


#rgb.setColorAll( COLOR)


def	judge( guard) :

	if guard :
#		label1	= M5TextBox( 200, 200, "Guard !", lcd.FONT_Default, WHITE, rotate = 0)
		label1.setText( str( "Guard !"))

		RGB( COLOR, 1)

	else :
#		label1	= M5TextBox( 200, 200, "BOMB !", lcd.FONT_Default, WHITE, rotate = 0)
		label1.setText( str( "BOMB !"))

		RGB( RED, 5)
		RGB( RED, 5)
		RGB( RED, 5)
		RGB( RED, 5)


label1	= M5TextBox( 200, 200, "", lcd.FONT_Default, WHITE, rotate = 0)

is_end	= False

def	main() :

	setScreenColor( BLACK)

	buttonA	= M5Button( name = "ButtonA", text = "ButtonA", visibility = True)
	buttonB	= M5Button( name = "ButtonB", text = "ButtonB", visibility = True)
	buttonC	= M5Button( name = "ButtonC", text = "ButtonC", visibility = True)

	# post
	post1	= M5Rect( 64, 10, 1, 200, WHITE, WHITE)
	post2	= M5Rect(164, 10, 1, 200, WHITE, WHITE)
	post3	= M5Rect(264, 10, 1, 200, WHITE, WHITE)

	global	is_end
	is_end	= False


post	= 0													# for debug.

def	btn_common( post, shield) :

	label1.hide()

	amida	= Amida()

	label1.setText( str( "Hello"))
	wait_ms( 900)

	label1.hide()
	wait_ms( 100)

	guard	= amida.ready()

	label1.setText( str( "World"))
	wait_ms( 900)

	label1.hide()
	wait_ms( 100)

	guard	= amida.start( post, shield)
	judge( guard)

	amida	= None

	global	is_end
	is_end	= True

def	btnA_pressed() :
#def	btnA_released() :

	if is_end :
		main()
	else :
		btn_common( post, 0)

#	label1.setText( str( "0"))

def	btnB_pressed() :

	if is_end :
		main()
	else :
		btn_common( post, 1)

#	label1.setText( str( "1"))

def	btnC_pressed() :

	if is_end :
		main()
	else :
		btn_common( post, 2)

#	label1.setText( str( "2"))

btnA.wasPressed( callback = btnA_pressed)
#btnA.wasReleased( callback = btnA_released)
btnB.wasPressed( callback = btnB_pressed)
btnC.wasPressed( callback = btnC_pressed)

'''
while True :
	main()
'''
main()
#'''

'''
print( M5Circle.__name__)
print( M5Circle.__class__)
#print( M5Circle.__module__)
#print( M5Circle.__dict__)
#print( M5Circle.__bases__)
#print( M5Circle.__doc__)


print( type( rgb))
print( dir( rgb))
#print( type( bullet))
#print( dir( bullet))
print( type( post1))
print( dir( post1))
#print( type( rect0))
#print( dir( rect0))
print( type( btnA))
print( dir( btnA))
'''
