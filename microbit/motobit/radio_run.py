#!/usr/bin/env python
# coding: utf-8

"""
refered :
  SparkFun moto:bit の I2C 操作と MicroPython からの利用
	https://qiita.com/inachi/items/6ed7c42dc1faa35ba89c
"""

from microbit import button_a as ba
from microbit import button_b as bb
from microbit import display as dp
from microbit import Image
from microbit import sleep
from microbit import i2c

import radio


class Motor :

	# command
	LEFT		 = 0x21
	RIGHT		 = 0x20
	LEFT_INVERT	 = 0x13
	RIGHT_INVERT = 0x12
	ENABLE		 = 0x70

	# direction
	FORWARD = 0x80
	REVERSE = 0x00

	# i2c
	_I2C_ADDR = 0x59
	_I2C_SDA  = 20
	_I2C_SCL  = 19
	_i2c_buf  = bytearray(2)

	def __init__( self, motor):
		self.motor = motor

	def set_speed( self, speed, direction=FORWARD):
		pwr = speed * 127 // 100
		Motor._i2c_buf[0] = self.motor
		Motor._i2c_buf[1] = (pwr | direction) \
							if direction == Motor.FORWARD else (127 - pwr)
		i2c.write(Motor._I2C_ADDR, Motor._i2c_buf)

	def invert( self, invert):
		if self.motor == Motor.LEFT:
			Motor._i2c_buf[0] = Motor.LEFT_INVERT
		else:
			Motor._i2c_buf[0] = Motor.RIGHT_INVERT
		Motor._i2c_buf[1] = int(invert)
		i2c.write(Motor._I2C_ADDR, Motor._i2c_buf)

	@staticmethod
	def enable():
		Motor._i2c_buf[0] = Motor.ENABLE
		Motor._i2c_buf[1] = 1
		i2c.write(Motor._I2C_ADDR, Motor._i2c_buf)

	@staticmethod
	def disable():
		Motor._i2c_buf[0] = Motor.ENABLE
		Motor._i2c_buf[1] = 0
		i2c.write(Motor._I2C_ADDR, Motor._i2c_buf)


motor_left	= Motor(Motor.LEFT)
motor_right = Motor(Motor.RIGHT)


def	hdr_ba( spd) :

	dp.show( Image.HAPPY)

	if ena is False :
		Motor.enable()

	motor_left.set_speed( spd)
	motor_right.set_speed( spd)
	sleep( 500)

#	Motor.disable()

	return	True

def	hdr_bb( spd) :

	dp.show( Image.SAD)

	if ena is False :
		Motor.enable()

	motor_left.set_speed( spd, Motor.REVERSE)
	motor_right.set_speed( spd, Motor.REVERSE)
	sleep( 500)

#	Motor.disable()

	return	True

def	init() :

	radio.on()

	dp.show( Image.HEART)

def	loop( ena) :

	if ena is True :
		Motor.disable()

	return	False


if __name__ == "__main__" :

	init()

	spd	= 50
	ena	= False

	while True :
		try :
			incoming = radio.receive()
		except :
			continue

#		if ba.is_pressed() :
		if incoming == 'run':
			ena	= hdr_ba( spd)

#		elif bb.is_pressed() :	
		elif incoming == 'back':
			ena	= hdr_bb( spd)

		else :
			ena	= loop( ena)
