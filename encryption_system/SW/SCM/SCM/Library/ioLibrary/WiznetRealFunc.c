/*
 * WiznetRealFunc.c
 *
 *  Created on: May 11, 2022
 *      Author: Hyun-Ho Cha
 */
#include "stm32h7xx_hal.h"

static void cs_sel(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
}

static void cs_dessel(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
}

static iodata_t bus_rb(uint32_t addr)
{
	return (iodata_t) *addr;
}


static void bus_wb(uint32_t addr, iodata_t wb)
{
	*addr = wb;
}
