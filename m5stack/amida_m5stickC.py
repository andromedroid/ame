"""
based on uiflow-firmware v1.4.5
"""

from m5stack import *
from m5ui import *
from uiflow import *

#from m5mqtt import M5mqtt
import random


BLACK	= 0x000000
RED		= 0xFF0000
GREEN	= 0x00FF00
BLUE	= 0x0000FF
WHITE	= 0xFFFFFF
#COLOR	= 0x33CC00
COLOR	= 0x00CCFF


class Amida :

	objsize		= 8
	lines		= [0] * 7
	lines_rect	= [None] * 7
	bullet		= None

	def	__init__( self) :

		self.lines_rect	= [None] * 7

		for ii in range( len( self.lines)) :
#			self.lines[ii]		= ii % 2 + 1												# for debug.
			self.lines[ii]		= random.randint( 0, 2)
			if self.lines[ii] > 0 :
				genten	= (20 + (self.lines[ii] - 1) * 20)
				print( "genten {:2d}: {}".format( ii, genten))
#				self.lines_rect[ii]	= M5Rect( genten, 36 + ii * 15, 20, 1, WHITE, WHITE)	# for debug.
				self.lines_rect[ii]	= M5Rect( genten, 36 + ii * 15, 20, 1, BLACK, BLACK)

	def	drawVert( self, obj, xpos, ypos, move, step = 1) :

		for ii in range( 0, move, step) :
			obj.setPosition( xpos, ypos + ii)
			wait_ms( 5)

		return	ypos + move

	def	drawHori( self, obj, xpos, ypos, move, step = 1) :

		for ii in range( 0, move, step) :
			obj.setPosition( xpos + ii, ypos)
			wait_ms( 5)

		return	xpos + move

	def	__gogo_bullet( self, post, ypos, line) :

		xpos	= 20 + post * 20

		if line == 1 :
			if post == 0 :
				xpos	= self.drawHori( self.bullet, xpos, ypos, 20)
				post	+= 1

			elif post == 1 :
				xpos	= self.drawHori( self.bullet, xpos, ypos, -20, -1)
				post	-= 1

			else :	# post == 2
				pass

		elif line == 2 :
			if post == 0 :
				pass

			elif post == 1 :
				xpos	= self.drawHori( self.bullet, xpos, ypos, 20)
				post	+= 1

			else :	# post == 2
				xpos	= self.drawHori( self.bullet, xpos, ypos, -20, -1)
				post	-= 1

		else :	# line == 0
			pass

		ypos	= self.drawVert( self.bullet, xpos, ypos, 15)

		return	post, ypos

	def	ready( self) :

		for line in self.lines_rect :
			if line is not None :
				line.setBorderColor( WHITE)

	def	start( self, post) :
		'''
		fix start position
		int( post)	: 0 ~ 2
		'''

		genten	= (20 + post * 20) - self.objsize
		rect0	= M5Rect( genten,  8, self.objsize * 2, self.objsize * 2, COLOR, COLOR)

		# bullet
		xpos	= 20 + post * 20
		ypos	= 30
		self.bullet	= M5Circle( xpos, ypos, self.objsize, BLACK, BLACK)

		self.bullet.setBgColor( COLOR)

		ypos	= self.drawVert( self.bullet, xpos, ypos, self.objsize // 2)	# vert. center adjust.
		for line in self.lines :
			post, ypos	= self.__gogo_bullet( post, ypos, line)
#			wait_ms( 100)

		self.bullet.setBgColor( BLACK)

		return	post


def	guard( succeed) :

	if succeed :
		M5Led.on()
		wait_ms( 500)
		M5Led.off()
		return

	for ii in range( 10) :
		M5Led.on()
		wait_ms( 50)
		M5Led.off()
		wait_ms( 50)


#rgb.setColorAll( COLOR)


shield	= -1

def	judge( post) :

	global	shield

	if post == shield :
#		label1	= M5TextBox( 10, 144, "Guard !", lcd.FONT_Default, WHITE, rotate = 0)
		label1.setText( str( "Guard !"))
		guard( True)

	else :
#		speaker.sing( 110, 0.5)
#		label1	= M5TextBox( 10, 144, "BOMB !", lcd.FONT_Default, WHITE, rotate = 0)
		label1.setText( str( "BOMB !"))
		guard( False)


label1	= M5TextBox( 10, 144, "", lcd.FONT_Default, WHITE, rotate = 0)

is_end	= False

def	main() :

	global	shield
	global	is_end

	setScreenColor( BLACK)

	buttonA	= M5Button( name = "ButtonA", text = "ButtonA", visibility = True)
	buttonB	= M5Button( name = "ButtonB", text = "ButtonB", visibility = True)
	buttonC	= M5Button( name = "ButtonC", text = "ButtonC", visibility = True)

	# post
	post1	= M5Rect( 20, 20, 1, 120, WHITE, WHITE)
	post2	= M5Rect( 40, 20, 1, 120, WHITE, WHITE)
	post3	= M5Rect( 60, 20, 1, 120, WHITE, WHITE)

	shield	= -1
	is_end	= False


post	= 0													# for debug.

def	btn_common( post) :

	label1.hide()

	amida	= Amida()

	label1.setText( str( "Hello"))
#	label1.setText( str( amida.lines))
	wait_ms( 900)

	label1.hide()
	wait_ms( 100)

	amida.ready()

	label1.setText( str( "World"))
	wait_ms( 900)

	label1.hide()
	wait_ms( 100)

	global	shield
	shield	= 1
	label1.setText( str( '     B'))
	post	= amida.start( post)

	judge( post)

	amida	= None

	global	is_end
	is_end	= True


#m5mqtt	= M5mqtt( '', '192.168.0.255', 1883, '', '', 300)

def fun_missile_( topic_data) :

	post	= int( topic_data)
	print( 'missile', post)

	if is_end :
		main()

	btn_common( post)

#m5mqtt.subscribe( 'missile', fun_missile_)

def	btnA_pressed() :
#def	btnA_released() :

	global	shield

	if is_end :
		main()
	else :
		shield	= 0
		label1.setText( str( ' A'))

def	btnB_pressed() :

	global	shield

	if is_end :
		main()
	else :
		shield	= 2
		label1.setText( str( '         C'))

btnA.wasPressed( callback = btnA_pressed)
#btnA.wasReleased( callback = btnA_released)
btnB.wasPressed( callback = btnB_pressed)

main()

'''
m5mqtt.start()
'''
while True :
	fun_missile_( random.randint( 0, 2))
	wait_ms( 3000)
#'''
