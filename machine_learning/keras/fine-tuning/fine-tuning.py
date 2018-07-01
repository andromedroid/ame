#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
ref :
	https://keras.io/applications/#usage-examples-for-image-classification-models
	https://qiita.com/tshimba/items/60f7bcc8ae26b5004a3a
	http://www.robots.ox.ac.uk/~vgg/data/flowers/17/
"""

from __future__ import absolute_import, division, print_function, unicode_literals

import sys
import os
import numpy as np

#import plaidml.keras
#plaidml.keras.install_backend()

from keras.preprocessing.image import ImageDataGenerator
from keras.models import Sequential, Model
#from keras.layers import Input, Activation, Dropout, Flatten, Dense
#from keras.layers import Input, AveragePooling2D, Flatten, Dense
from keras.layers import Input, GlobalAveragePooling2D, Dense
#from keras.layers import Input, GlobalAveragePooling2D, Reshape, Dropout, Conv2D, Activation
#from keras.applications.vgg16 import VGG16
#from keras.applications.inception_v3 import InceptionV3
#from keras.applications.resnet50 import ResNet50, preprocess_input
from keras.applications.mobilenetv2 import MobileNetV2, preprocess_input
#from keras.applications.nasnet import NASNetMobile, preprocess_input
from keras import optimizers


classes	= [	'Tulip', 'Snowdrop', 'LilyValley', 'Bluebell', 'Crocus',
			'Iris', 'Tigerlily', 'Daffodil', 'Fritillary', 'Sunflower',
			'Daisy', 'ColtsFoot', 'Dandelion', 'Cowslip', 'Buttercup',
			'Windflower', 'Pansy' ]

batch_size	= 24
nb_classes	= len( classes)

#img_rows, img_cols	= 224, 224
#img_rows, img_cols	= 200, 200
#img_rows, img_cols	= 192, 192
img_rows, img_cols	= 160, 160
#img_rows, img_cols	= 128, 128
channels	= 3

train_data_dir	= 'dataset/train_images'
valid_data_dir	= 'dataset/valid_images'

nb_train_samples = 1190
nb_valid_samples = 170
nb_epoch		 = 100

result_dir = 'dataset/results'


def save_history( history, result_file) :

	loss	 = history.history['loss']
	acc		 = history.history['acc']
	val_loss = history.history['val_loss']
	val_acc	 = history.history['val_acc']
	nb_epoch = len( acc)

	with open( result_file, "w") as fp :
		fp.write("epoch\tloss\tacc\tval_loss\tval_acc\n")
		for ii in range( nb_epoch) :
			fp.write("%d\t%f\t%f\t%f\t%f\n" % (ii, loss[ii], acc[ii], val_loss[ii], val_acc[ii]))


if __name__ == '__main__' :

	# create the base pre-trained model
	input_tensor	= Input( shape = (img_rows, img_cols, 3))
#	basenet			= VGG16(		include_top	= False,
#	basenet			= InceptionV3(	include_top	= False,
#	basenet			= ResNet50(		include_top	= False,
	basenet			= MobileNetV2(	include_top	= False,
#	basenet			= NASNetMobile(	include_top	= False,
									input_shape	= (img_rows, img_cols, 3),
									weights		= 'imagenet' )

#	basenet.summary()
#	sys.exit( 0)

	# add a global spatial average pooling layer
	x	= basenet.output
#	x	= Flatten( name = 'flatten')(x)
	x	= GlobalAveragePooling2D( name = 'avg_pool')(x)
	# let's add a fully-connected layer
	# VGG16
#	x	= Dense( 4096, activation = 'relu', name = 'fc1')(x)
#	x	= Dense( 4096, activation = 'relu', name = 'fc2')(x)
#	x	= Dense( 1024, activation = 'relu')(x)
	# MobileNet
#	x	= Reshape( shape, name = 'reshape_1')(x)
#	x	= Dropout( dropout, name = 'dropout')(x)
#	x	= Conv2D( nb_classes, (1, 1), padding = 'same', name = 'conv_preds')(x)
#	x	= Activation( 'softmax', name = 'act_softmax')(x)
	# ResNet50
#	x	= AveragePooling2D( (7, 7), name = 'avg_pool')(x)
#	x	= Flatten()(x)
#	x	= Dense( classes, activation = 'softmax', name = 'fc1000')(x)
	# and a logistic layer
	predictions	= Dense( nb_classes, activation = 'softmax', name = 'predictions')(x)
#	predictions	= Reshape( (nb_classes,), name = 'reshape_2')(x)

	# load pretrained weights
#	top_model.load_weights( os.path.join( result_dir, 'bottleneck_fc_model.h5'))

	# this is the model we will train
	model	= Model(	inputs	= basenet.input,
						outputs	= predictions )

#	model.summary()
#	sys.exit( 0)

	# first: train only the top layers (which were randomly initialized)
#	ii	= 0
#	for layer in model.layers :
#	for layer in model.layers[:294] :	# [313]	InceptionV3		: average_pooling2d_9
#	for layer in model.layers[:163] :	# [176]	ResNet50		: activation_46
#	for layer in model.layers[:104] :	# [152]	MobileNetV2		: block_11_add
#	for layer in model.layers[:113] :	# [152]	MobileNetV2		: block_12_add
#	for layer in model.layers[:119] :	# [152]	MobileNetV2		: block_13_depthwise_relu
	for layer in model.layers[:121] :	# [152]	MobileNetV2		: block_13_project_BN
#	for layer in model.layers[:130] :	# [152]	MobileNetV2		: block_14_add
#	for layer in model.layers[:339] :	# [751]	NASNetMobile	: concatenate_3
#	for layer in model.layers[:571] :	# [751]	NASNetMobile	: concatenate_4
#	for layer in model.layers[:697] :	# [751]	NASNetMobile	: separable_conv_2_bn_normal_left_11
#	for layer in model.layers[:742] :	# [751]	NASNetMobile	: separable_conv_2_bn_normal_left_12
		layer.trainable	= False
#		ii	= ii + 1
#		print( ii, type( layer))

#	sys.exit( 0)

	# we need to recompile the model for these modifications to take effect.
	# we use SGD with a low learning rate.
	model.compile(	loss		= 'categorical_crossentropy',
					optimizer	= optimizers.SGD(	#lr			= 1e-4,		# default
													#lr			= 1e-2,		# for ResNet50
													lr			= 0.045,	# for MobileNet
													#lr			= 0.1,		# for NASNetMobile
													momentum	= 0.9 ),
					metrics		= ['accuracy'])

	train_datagen	= ImageDataGenerator(
#		rescale			= 1.0 / 255,
		preprocessing_function	= preprocess_input,
		shear_range		= 0.2,
		zoom_range		= 0.2,
		horizontal_flip	= True )

	valid_datagen	= ImageDataGenerator(
#		rescale			= 1.0 / 255 )
		preprocessing_function	= preprocess_input )

	train_generator	= train_datagen.flow_from_directory(
		train_data_dir,
		target_size	= (img_rows, img_cols),
		color_mode	= 'rgb',
		classes		= classes,
		class_mode	= 'categorical',
		batch_size	= batch_size,
		shuffle		= True )

	valid_generator	= valid_datagen.flow_from_directory(
		valid_data_dir,
		target_size	= (img_rows, img_cols),
		color_mode	= 'rgb',
		classes		= classes,
		class_mode	= 'categorical',
		batch_size	= batch_size,
		shuffle		= True )

	# Fine-tuning
	history = model.fit_generator(
		train_generator,
#		samples_per_epoch	= nb_train_samples,		# Keras 1.x format.
		steps_per_epoch		= nb_train_samples // batch_size,
#		nb_epoch			= nb_epoch,				# Keras 1.x format.
		epochs				= nb_epoch,
		validation_data		= valid_generator,
#		nb_val_samples		= nb_valid_samples )	# Keras 1.x format.
		validation_steps	= nb_valid_samples // batch_size )

	if not os.path.exists( result_dir) :
		os.mkdir( result_dir)

	model.save_weights( os.path.join( result_dir, 'finetuning.h5'))

	save_history( history, os.path.join( result_dir, 'history_finetuning.txt'))
