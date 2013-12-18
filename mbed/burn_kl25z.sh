#!/bin/bash

if [ $# -lt 1 ]
then
	echo "[USAGE] $0 [PROJECT NAME]"
	exit 1
fi

PRJ_NAME=$1
MBED_TARGET="KL25Z"
PREFIX="bin"

BIN_NAME="${PRJ_NAME}_${MBED_TARGET}.${PREFIX}"
BIN_DIR="${PWD}/bin"
DL_DIR="${HOME}/Downloads"

TARGET_DIR="/media/MBED"

if [ -f ${DL_DIR}/${BIN_NAME} ]
then
	mv ${DL_DIR}/${BIN_NAME} ${BIN_DIR}/
fi
cp -a ${BIN_DIR}/${BIN_NAME} ${TARGET_DIR}/
