/*
 * freertos_function.h
 *
 *  Created on: May 11, 2022
 *      Author: Hyun-Ho Cha
 */


#ifndef INT_WIZNETREALFUNC_H_
#define INT_WIZNETREALFUNC_H_

#include "wizchip_conf.h"

/**
 *@brief call back function for WIZCHIP select
 *@todo Describe @ref wizchip_cs_select and @ref wizchip_cs_deselect function or register your functions.
 */
static void cs_sel(void);


/**
 *@brief call back function for WIZCHIP deselect
 *@todo Describe @ref wizchip_cs_select and @ref wizchip_cs_deselect function or register your functions.
 */
static void cs_desel(void);


/**
 *@brief call back function for bus interface read.
 *@param addr   : memory address to read
 */
static iodata_t bus_rb(uint32_t addr);


/**
 *@brief call back function for bus interface write.
 *@param addr   : memory address to write
 *@param wb	: data to write to the address
 */
static void bus_wb(uint32_t addr, iodata_t wb);



#endif /* INT_WIZNETREALFUNC_H_ */
