/******************************************************************************
*
* Module:SPI
*
* File Name: spi_cfg.h
*
* Description: Header file for Precompile configurations of spi module.
* 
* Author: Esmail Ahmed
*
*******************************************************************************/
#ifndef SPI_CFG_H
#define SPI_CFG_H

#include "Std_Types.h"

/* Macros for clk used 
	 0 for System clock
	 5 for PIOSC	
*/
#define SPI_CLK_CFG						 (0U)	

/* Macros for SPI Status */
#define SPI_INITIALIZED        (1U)
#define SPI_NOT_INITIALIZED    (0U)

/* Define Clock used by SPI */
#define SPISYSCLK              (16000000U)

#endif /* SPI_CFG_H */
