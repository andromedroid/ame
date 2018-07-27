#!/bin/bash

DATASET='17flowers'
MODEL='nasnet_mobile'
MODULE="https://tfhub.dev/google/imagenet/${MODEL}/feature_vector/1"
DATE=`date +%s`
LOG="log_${DATASET}_${MODEL}_${DATE}.txt"

STEPS=1000
LR=1000
BS=32

time python3 retrain.py \
--image_dir dataset/${DATASET} \
--how_many_training_steps $STEPS \
--learning_rate $LR \
--train_batch_size $BS \
--validation_batch_size $BS \
--tfhub_module $MODULE \
--saved_model_dir _save/${MODEL}_${DATE} \
2>&1 | tee $LOG
