#!/usr/bin/env python3
# coding: utf-8

"""
control PTZ example.

required to :
  $	pip3 install -U onvif-zeep
"""

from __future__ import absolute_import, division, print_function, unicode_literals

import sys
from time import sleep
from onvif import ONVIFCamera


if __name__ == "__main__" :

	if len( sys.argv) < 8 :
		print( "USAGE: python3 {} [ip] [port] [user] [wsdl dir] [x] [y] [sec] [pass (optional)]".format( sys.argv[0]))
		sys.exit( 1)

	mycam	= ONVIFCamera(	sys.argv[1],
							int( sys.argv[2]),
							sys.argv[3],
							None if len( sys.argv) == 8 else sys.argv[8],
							wsdl_dir = sys.argv[4] )

	vel_x	= float( sys.argv[5])
	vel_y	= float( sys.argv[6])
	seconds	= float( sys.argv[7])

	# Create ptz service.
	ptz_svc	= mycam.create_ptz_service()

	# Get ptz configuration.
#	mycam.ptz.GetConfigurations()
	# Another way
	ptz_conf	= ptz_svc.GetConfigurations()
	print( 'conf num :{:2d}.'.format( len( ptz_conf)))
	print( ptz_conf[0])

	# Get ptz status.
	params			   	= ptz_svc.create_type( 'GetStatus')
	params.ProfileToken	= 'profile_1'
	ptz_stat			= ptz_svc.GetStatus( params)
	print( ptz_stat)

	# Pan / Tilt.
	params			   	= ptz_svc.create_type( 'ContinuousMove')
	params.ProfileToken	= 'profile_1'
	params.Velocity		= ptz_stat.Position			# TODO: copy.
	params.Timeout		= 0

	params.Velocity.PanTilt.x	= vel_x
	params.Velocity.PanTilt.y	= vel_y

	print( params)
	ptz_svc.ContinuousMove( params)

	sleep( seconds)

	# Stop.
	params			   	= ptz_svc.create_type( 'Stop')
	params.ProfileToken	= 'profile_1'
	params.PanTilt		= True
	params.Zoom			= True
	print( params)
	ptz_svc.Stop( params)
