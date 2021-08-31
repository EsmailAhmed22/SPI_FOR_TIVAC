/******************************************************************************
*
* Module:SPI
*
* File Name: spi_pbcfg.c
*
* Description: Source file for Post build configurations of spi module. 
*
* Author: Esmail Ahmed
*
*******************************************************************************/
#include "spi.h"

/* PB structure used with SPI_Init API */
const SPI_ConfigType SPI_Configuration= {9,
																				 2, 
																				MASTER_ENABLE,
																				MASTER_ENABLE};
