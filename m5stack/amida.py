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
circl1	= M5Circle( 64, 64, 10, BLACK, BLACK)
circl2	= M5Circle(164,124, 10, BLACK, BLACK)
circl3	= M5Circle(264,184, 10, BLACK, BLACK)
circl4	= M5Circle(264,214, 10, BLACK, BLACK)

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

def	main() :

	circl1.setBgColor( COLOR)
	RGB()
	circl1.setBgColor( BLACK)

	circl2.setBgColor( COLOR)
	RGB()
	circl2.setBgColor( BLACK)

	circl3.setBgColor( COLOR)
	RGB()
	circl3.setBgColor( BLACK)

	label1	= M5TextBox( 200, 200, "Bomb !", lcd.FONT_Default, WHITE, rotate = 0)

	circl4.setBgColor( COLOR)
	RGB( 5)
	RGB( 5)
	RGB( 5)
	RGB( 5)
	circl4.setBgColor( BLACK)

	wait_ms( 0.001)

'''
while True :
	main()
'''
btnB.wasPressed( callback = main)
#'''
