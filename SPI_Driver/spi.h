/******************************************************************************
*
* Module:SPI
*
* File Name: spi.h
*
* Description: Header file for TM4C123GH6PM Microcontroller - SPI Driver
*
* Author: Esmail Ahmed
*
*******************************************************************************/
#ifndef SPI_H
#define SPI_H

#include "spi_cfg.h"
#include "Std_Types.h"
#include "Common_Macros.h"
#include "spi_registers.h"

/*******************************************************************************
*****************************PREPRPCESSOR MACROS********************************
*******************************************************************************/
#define PORTA_CLOCK_BIT         			(0U)
#define SPI0_CLOCK_BIT          			(0U)
#define SPI0_PINS_MASK								(0x0000003C)
#define SPI0_PCTL_VALUE								(0x00222200)
#define SPI0_PINS_MASTER_DIR_MASK		  (0x0000002C)
#define SPI0_PINS_SLAVE_DIR_MASK		  (0x00000020)
#define SPI0_HANDLER_PRIORITY				  (0x40000000)
#define NVIC_SPI0_INTERRUPT						(7U)
#define SPI0_ENABLE_BIT								(1U)				
#define SPI0_MASTER_SLAVE_BIT					(2U)
#define SPI0_SCR_BIT									(8U)
#define SPI0_FRAME_BIT								(4U)
#define SPI0_BUSY_CHECK								(4U)
#define SPI0_RX_INT_ENABLE						(1U)
#define SPI0_INT_CLEAR								(1U)	
/*******************************************************************************
****************************TYPES DECLARATION***********************************
*******************************************************************************/
/* Configuration structure for the UART */
/* Enum for Master-Slave selection */
typedef enum
{
	MASTER_ENABLE,SLAVE_ENABLE
}SPI_Master_Slave_Selection;
typedef enum
{
	DATA_SIZE_4_BITS=3 ,DATA_SIZE_5_BITS  ,DATA_SIZE_6_BITS ,
	DATA_SIZE_7_BITS   ,DATA_SIZE_8_BITS  ,DATA_SIZE_9_BITS ,
	DATA_SIZE_10_BITS  ,DATA_SIZE_11_BITS ,DATA_SIZE_12_BITS ,
	DATA_SIZE_13_BITS  ,DATA_SIZE_14_BITS ,DATA_SIZE_15_BITS
}SPI_Data_size;
typedef struct
{
	uint8 s_sc_rate;
	uint8	s_clk_ps_div;
	uint8 s_data_size;
	SPI_Master_Slave_Selection s_master_slave;		/* Initialize SPI as master or slave */
	
}SPI_ConfigType;
/*******************************************************************************
*****************************FUNCTIONS PROTOTYPE********************************
*******************************************************************************/
/* This function is responsible for initializing the SPI */
void SPI_init(const SPI_ConfigType *a_config_Ptr);

/* This function is responsible for sending one byte */
void SPI_sendByte(const uint8 a_data);

/* This function is responsible for receiving one byte */
uint8 SPI_receiveByte(void);

/* This function is responsible for Making Master or Slave */
void SPI_Master_Slave_Enable(uint8 a_master_or_slave);

/*This function is responsible for saving the address that will be called after interrupts happen*/
void SPI_callBackAdress(void(*a_Func_Ptr)(void));

extern const SPI_ConfigType SPI_Configuration;
#endif	/* SPI_H */
