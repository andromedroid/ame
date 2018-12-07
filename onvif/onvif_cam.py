#!/usr/bin/env python3
# coding: utf-8

"""
ONVIF example.

required to :
  $	pip3 install -U onvif-zeep
"""

from __future__ import absolute_import, division, print_function, unicode_literals

import sys

from onvif import ONVIFCamera


if __name__ == "__main__" :

	if len( sys.argv) < 5 :
		print( "USAGE: python3 {} [ip] [port] [user] [wsdl dir] [pass (optional)]".format( sys.argv[0]))
		sys.exit( 1)

	mycam	= ONVIFCamera(	sys.argv[1],
							int( sys.argv[2]),
							sys.argv[3],
							None if len( sys.argv) == 5 else sys.argv[5],
							wsdl_dir = sys.argv[4] )

	# Get Hostname.
	resp	= mycam.devicemgmt.GetHostname()
	print( "My camera's hostname: " + str( resp.Name))

	# Get system date and time.
	dt		= mycam.devicemgmt.GetSystemDateAndTime()
	tz		= dt.TimeZone
	year	= dt.UTCDateTime.Date.Year
	hour	= dt.UTCDateTime.Time.Hour
	minute	= dt.UTCDateTime.Time.Minute

	print( "{}, {}. {}:{}".format( tz.TZ, year, hour, minute))

	# Create media service.
	media_svc	= mycam.create_media_service()

	# Get media service capability.
#	mycam.media.GetServiceCapabilities()
	# Another way
	media_conf	= media_svc.GetServiceCapabilities()
	print( media_conf)

	# Get video sources.
	media_vsrc	= media_svc.GetVideoSources()
	print( 'vsrc num :{:2d}.'.format( len( media_vsrc)))
	print( media_vsrc)

	'''
	# Create media profile.
	params			= media_svc.create_type( 'CreateProfile')
	params.Name		= 'MEDIA'
	params.Token	= 'profile_1'
	print( params)
	media_svc.CreateProfile( params)
	'''

	'''
	# Get media profiles.
	media_prof	= media_svc.GetProfiles()
	print( 'prof num :{:2d}.'.format( len( media_prof)))
	print( media_prof)
	'''
	# Get media profile.
	params				= media_svc.create_type( 'GetProfile')
	params.ProfileToken	= 'profile_1'
	media_prof			= media_svc.GetProfile( params)
	print( media_prof)
#	'''
