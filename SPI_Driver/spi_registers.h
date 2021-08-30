/******************************************************************************
*
* Module:SPI
*
* File Name: spi.h
*
* Description: Header file for TM4C123GH6PM Microcontroller - SPI Driver Registers
*
* Author: Esmail Ahmed
*
*******************************************************************************/
 
#ifndef SPI_REGS_H
#define SPI_REGS_H

#include "Std_Types.h"

/* Needed to initialize the port containing SPI0 Clock and SPI0 Clock */
#define SYSCTL_GPIO_REGCGC2_REG   (*((volatile uint32 *)0x400FE108))
#define SYSCTL_SPI_RCGCSPI_REG    (*((volatile uint32 *)0x400FE61C))

/* Needed GPIO Registers for SPI0 pins Initialization */
#define GPIO_PORTA_AFSEL_REG      (*((volatile uint32 *)0x40004420))
#define GPIO_PORTA_PCTL_REG       (*((volatile uint32 *)0x4000452C))
#define GPIO_PORTA_DIR_REG        (*((volatile uint32 *)0x40004400))
#define GPIO_PORTA_DEN_REG        (*((volatile uint32 *)0x4000451C))
#define GPIO_PORTA_PUR_REG				(*((volatile uint32 *)0x40004510))
/* SPI Registers for SPI0 configuration */
#define SPI0_CTL_REG_0				    (*((volatile uint32 *)0x40008000))
#define SPI0_CTL_REG_1				    (*((volatile uint32 *)0x40008004))
#define SPI0_DATA_REG			        (*((volatile uint32 *)0x40008008))
#define SPI0_STATUS_REG				    (*((volatile uint32 *)0x4000800C))
#define SPI0_CLKPS_REG				    (*((volatile uint32 *)0x40008010))
#define SPI0_INT_MASK_REG				  (*((volatile uint32 *)0x40008014))
#define SPI0_INT_STATUS_REG				(*((volatile uint32 *)0x40008018))
#define SPI0_INT_CLEAR_REG				(*((volatile uint32 *)0x40008020))
#define SPI0_CLK_CFG_REG  				(*((volatile uint32 *)0x40008FC8))

/* NVIC Registers for SPI0 Interrupt handling */
#define NVIC_PRI1_REG             (*((volatile uint32 *)0xE000E404))
#define NVIC_EN0_REG              (*((volatile uint32 *)0xE000E100))
	
#endif /* SPI_REGS_H */
