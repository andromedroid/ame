#/bin/bash

# ref: http://mag.switch-science.com/2013/07/30/use-i2c-lcd-brakeout-board-on-raspberry-pi/
# This script requires sudo.

I2C_BUS=1
I2C_DEV_ADR=0x3e
I2C_END_OF_CMD=i

i2c_set() {
#	echo $I2C_BUS $I2C_DEV_ADR $@ ${I2C_END_OF_CMD}
	sudo i2cset -y $I2C_BUS $I2C_DEV_ADR $@ ${I2C_END_OF_CMD}
}

I2C_DATA_ADR=0x00
I2C_CHAR_ADR=0x40

i2c_set_cmd() {
	i2c_set $I2C_DATA_ADR $@
}

i2c_set_char() {
	i2c_set $I2C_CHAR_ADR $@
}

clear_screen() {
	i2c_set_cmd 0x01
}

move_line_up() {
	i2c_set_cmd 0x8$1
}

move_line_down() {
	i2c_set_cmd 0xC$1
}

conv_keycode() {
	# char -> code
	CODE=`printf "%d" \'$1`

	# conversion
#	if [ $CODE -ge 0x30 -a $CODE -le 0x39 ]
#	then
#		CODE=$(($CODE + 0))							# same value
#	elif [ $CODE -gt 0x40 -a $CODE -le 0x5A ]
#	then
#		CODE=$(($CODE + 0))							# same value		
#	elif [ $CODE -gt 0x60 -a $CODE -le 0x7A ]
#	then
#		CODE=$(($CODE + 0))							# same value
#	else
#		echo $CODE
#	fi

	# code -> char
	HEX=`printf "%X" $CODE`
	echo "0x${HEX} "
	CHAR=`printf "\x${HEX}"`
#	echo $CHAR
}

conv_string() {
	if [ $# -lt 1 -o $# -gt 1 ]
	then
		echo "Error @ conv_string() : arguments."
		return	1
	fi

	STR=$1
	LEN=`expr length ${STR}`
	II=$LEN

	while [ $II -gt 0 ]
	do
		II=$(($II - 1))
		CHAR=`echo $STR | cut -c $(($LEN - $II))`
#		echo $CHAR
		CONV_STR=$CONV_STR`conv_keycode $CHAR`
	done

	echo ${CONV_STR}
}

if [ $# -gt 2 ]
then
	echo "[USAGE] ${0} [string1] [string2]"
	exit
fi

clear_screen
#move_line_up 0
i2c_set_char `conv_string $1`

if [ $# -gt 1 ]
then
	move_line_down 0
	i2c_set_char `conv_string $2`
fi
