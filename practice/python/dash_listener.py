#!/usr/bin/env python
# coding: utf-8

"""
need to :
  $	sudo apt install python-scapy
"""

from __future__ import absolute_import, division, print_function, unicode_literals

import sys
from scapy.all import *


def	dash_action() :

	print( "pushed dash.")
#	sys.exit( 0)


def	arp_handler( pkt) :

	dash_ip 	= '192.168.0.255'
	dash_mac	= '3a:ca:dd:7e:55:da'

	try :
#		print( pkt[ARP].op)
		if pkt[ARP].op != 1 :
			return

	except IndexError as e :
		print( "{}, msg: {}".format(
				type( e), e.message ) )
#		print( "args: {}".format( e.args) )
		return

#	print( pkt[ARP].psrc)
	if pkt[ARP].psrc != dash_ip :
		return

#	print( pkt[ARP].hwsrc)
	if pkt[ARP].hwsrc != dash_mac :
		return

	dash_action()


if __name__ == "__main__" :

	sniff(	prn		= arp_handler,
			filter	= "arp",
			store	= 0 )
#			count	= 3 )
