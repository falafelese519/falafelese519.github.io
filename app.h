#ifndef APP_H
#define APP_H


#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include <boards/adafruit_qtpy_rp2040.h>
#include "pico/stdlib.h"
#include "pio_i2c.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "hardware/adc.h"
#include "ssd1306.h"

//#include "Adafruit_Trellis.h"
//#include  "mpu6050_i2c.h"

char scan_kepad();

void init_keypad();


#endif