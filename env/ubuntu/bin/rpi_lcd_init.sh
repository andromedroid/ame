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

i2c_set $I2C_DATA_ADR 0x38 0x39 0x14 0x70 0x56 0x6c

if [ $? != 0 ]
then
	i2c_set $I2C_DATA_ADR 0x38 0x39 0x14 0x70 0x56 0x6c
fi

i2c_set $I2C_DATA_ADR 0x38 0x0d 0x01
