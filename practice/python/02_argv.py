#!/usr/bin/env python
# coding: utf-8

"""
practice to use command arguments.
"""

from __future__ import absolute_import, division, print_function, unicode_literals

import	sys
import	os


if __name__ == "__main__" :

	argc	= len( sys.argv)
	print( argc)

	if argc < 2 :
		print( "USAGE: {:s} [hoge]".format( sys.argv[0]))
		sys.exit( 1)

	print( sys.argv[1])
