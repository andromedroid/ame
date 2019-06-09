"""
based on uiflow-firmware v1.3.2
"""

from m5stack import *
from m5ui import *
from uiflow import *

BLACK	= 0x000000
WHITE	= 0xFFFFFF
#COLOR	= 0x33CC00
COLOR	= 0x00CCFF

setScreenColor( BLACK)

# bullet
bullet	= M5Circle( 54,  0, 10, BLACK, BLACK)

buttonA	= M5Button( name = "ButtonA", text = "ButtonA", visibility = True)
buttonB	= M5Button( name = "ButtonB", text = "ButtonB", visibility = True)
buttonC	= M5Button( name = "ButtonC", text = "ButtonC", visibility = True)

# amida
post1	= M5Rect( 64, 10,  1,200, WHITE, WHITE)
post2	= M5Rect(164, 10,  1,200, WHITE, WHITE)
post3	= M5Rect(264, 10,  1,200, WHITE, WHITE)

# start position
rect0	= M5Rect( 54,  0, 20, 20, COLOR, COLOR)

# horizontal line.
rect4	= M5Rect( 64, 64,100,  1, WHITE, WHITE)
rect5	= M5Rect(164,124,100,  1, WHITE, WHITE)
rect6	= M5Rect( 64,184,100,  1, WHITE, WHITE)

# batt
#rect1	= M5Rect(118, 74, 30, 80, BLACK, BLACK)
#rect2	= M5Rect(164, 74, 30, 80, BLACK, BLACK)
#rect3	= M5Rect(209, 74, 30, 80, BLACK, BLACK)


#def	btnA_pressed() :
def	btnA_released() :

#	label0.hide()
	label1.setText( str( "Hello"))

def	btnC_released() :

#	label1.hide()
	label1.setText( str( "World"))

#btnA.wasPressed( callback = btnA_pressed)
btnA.wasReleased( callback = btnA_released)
#btnB.wasPressed( callback = btnB_pressed)
btnC.wasReleased( callback = btnC_released)

def	RGB( step = 2) :

	for ii in range( 0, 256, step) :
		rgb.setBrightness( ii)
		rgb.setColorAll( COLOR)

	for ii in range( 255, -1, -step) :
		rgb.setBrightness( ii)
		rgb.setColorAll( COLOR)


rgb.setColorAll( COLOR)

def	drawVert( obj, xpos, ypos, move, step = 1) :

	for ii in range( 0, move, step) :
		obj.setPosition( xpos, ypos + ii)

def	drawHori( obj, xpos, ypos, move, step = 1) :

	for ii in range( 0, move, step) :
		obj.setPosition( xpos + ii, ypos)

def	main() :

	bullet.setBgColor( COLOR)
	drawVert( bullet,  64,   4, 60)
	drawHori( bullet,  64,  64, 100)
	drawVert( bullet, 164,  64, 60)
	drawHori( bullet, 164, 124, 100)
	drawVert( bullet, 264, 124, 60)
	bullet.setBgColor( BLACK)
#	'''

	label1	= M5TextBox( 200, 200, "Bomb !", lcd.FONT_Default, WHITE, rotate = 0)

	bullet.setPosition( 264, 214)
	bullet.setBgColor( COLOR)
	RGB( 5)
	RGB( 5)
	RGB( 5)
	RGB( 5)
	bullet.setBgColor( BLACK)

	wait_ms( 1)

'''
while True :
	main()
'''
print( M5Circle.__name__)
print( M5Circle.__class__)
#print( M5Circle.__module__)
#print( M5Circle.__dict__)
#print( M5Circle.__bases__)
#print( M5Circle.__doc__)

print( type( rgb))
print( dir( rgb))
print( type( bullet))
print( dir( bullet))
print( type( post1))
print( dir( post1))
print( type( rect0))
print( dir( rect0))
#print( type( buttonA))
#print( dir( buttonA))

btnB.wasPressed( callback = main)
#'''
