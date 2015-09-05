#!/usr/bin/env python
# coding: utf-8

import	sys
import	os

class MyClass :

	__myStr	= None

#	def	__init__(self, string) :
#
#		self.__myStr	= string

	def	imset(self, string) :

		self.__myStr	= string

	@classmethod
	def	cmset(cls, string) :

		cls.__myStr	= string

	def	imshow(self) :

		print self.__myStr

	@classmethod
	def	cmshow(cls) :

		print cls.__myStr


if __name__ == "__main__" :

	mc	= MyClass()
#	mc	= MyClass("instance init")
#	MyClass("class init")

#	mc.imshow()
#	MyClass.cmshow()
#	print

#	mc.imset("imset")		# it apply only instance.
	MyClass.cmset("cmset")	# it apply instance/class both.
							# (only never assign any values to variable of instance.

	mc.imshow()
	MyClass.cmshow()
	print

	mc.imset(None)
	MyClass.cmset(None)

	mc.imshow()				# None
	MyClass.cmshow()		# None
	print

#	mc.imset("imset")		# it apply only instance.
	MyClass.cmset("cmset")	# it apply only class.

	mc.imshow()
	MyClass.cmshow()
	print
