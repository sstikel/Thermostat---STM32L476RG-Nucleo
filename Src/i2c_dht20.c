/*
 * i2c_dht20.c for STM32L476RG
 *
 *  Created on: 7/9/26
 *  Author: Sam Gay
 */

#include "i2c_main.h"
#include "delay.h"
#include "i2c_dht20.h"

#define SLAVE_ADDRESS_DHT20 0x38

void dht20_write(){}

void dht20_read()
{
	// pg. 10 dht20 datasheet

	// step 1.1: wait 100ms after power on

	// step 1.2: request "status word" by sending 0x71 before reading

	// step 1.3: if "status word" AND 0x18 == 0x18
	// 				initialize 0x1B, 0x1C, 0x1E registers
	// 			 else
	// step 2.1		wait 10ms

	// step 2.2		send 0xAC (trigger measurement)
	//			 		command parameter has two bytes (0x33, 0x00)

	// step 3.1		wait 80ms

	// 	//TODO: use while to check status word
	// step 3.2		if "status word" bit[7] == 0
	// step 3.3			 read 6 bytes continuously
	//						#1: state
	//						#2: Humidity data
	//						#3: Humidity data
	//						#4: Humidity data (first 4 bits), Temp data (last 4 bits)
	//						#5: Temp data
	//						#6: Temp data
	// 				else
	//				 	 wait ?? (80ms ?)

	// step 4.1		do something with the CRC byte (comes after the previous 6 bytes)

	// step 5 	calculate temp and humidity values
	//				Temp(in C) = (Signal(temp) / 2^20) * 200 - 50
	//				RH(%)      = (Signal(RH)   / 2^20) * 100%
}

void dht20_send_cmd(){}

void dht20_send_data(){}

void dht20_init(){}
