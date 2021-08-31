/******************************************************************************
*
* Module:SPI
*
* File Name: spi.h
*
* Description: Source file for spi module.
*
* Author: Esmail Ahmed
*
*******************************************************************************/
#include "spi.h"

/* ISR for Receiving a Byte*/     
void SPI_Receive_Handler(void)
{
}

/*******************************************************************************
*************************FUNCTIONS DEFINITIONS**********************************
*******************************************************************************/

/********************************************************************************
*[Function Name]: SPI_init.
*[Description]  : This function is responsible for initializing the SPI.
*[in]		: SPI_ConfigType *a_config_Ptr:pointer contains address of structure.
*[out]		: None.
*[in/out]	: None.
*[Returns]	: None.
*********************************************************************************/
void SPI_init(const SPI_ConfigType *a_config_Ptr){
  
  volatile uint8 delay = 0;
  
	/* Enable SPI clock*/
  SET_BIT(SYSCTL_SPI_RCGCSPI_REG,SPI0_CLOCK_BIT);
  delay = (uint8) SYSCTL_SPI_RCGCSPI_REG;
	
  /* Enable Port clock*/
  SET_BIT(SYSCTL_GPIO_REGCGC2_REG,PORTA_CLOCK_BIT);
  delay = (uint8) SYSCTL_GPIO_REGCGC2_REG;
  
	/*Select SPI as alternative function for A2,A3,A4 and A5*/
  GPIO_PORTA_AFSEL_REG |= SPI0_PINS_MASK;
	GPIO_PORTA_PCTL_REG  |= SPI0_PCTL_VALUE;
	
	/* Set Pins A2,A3,A4 and A5 directions */
	if(a_config_Ptr->s_master_slave == MASTER_ENABLE)
	{
		/* Set Pins A2,A3,A4 and A5 directions for SPI MASTER */
		GPIO_PORTA_DIR_REG &= (uint32)~SPI0_PINS_MASK;
		GPIO_PORTA_DIR_REG |= SPI0_PINS_MASTER_DIR_MASK;
	}
	else if (a_config_Ptr->s_master_slave == SLAVE_ENABLE)
	{
		/* Set Pins A2,A3,A4 and A5 directions for SPI SLAVE */
		GPIO_PORTA_DIR_REG &= (uint32)~SPI0_PINS_MASK;
		GPIO_PORTA_DIR_REG |= SPI0_PINS_SLAVE_DIR_MASK;
	}
  
  /*Set A2,A3,A4 and A5 as Digital Pins*/
  GPIO_PORTA_DEN_REG |= SPI0_PINS_MASK;

  /* Disable SPI0 */
	CLEAR_BIT(SPI0_CTL_REG_1,SPI0_ENABLE_BIT);

  /* Select master or slave */
	if(a_config_Ptr->s_master_slave == MASTER_ENABLE)
	{
		CLEAR_BIT(SPI0_CTL_REG_1,SPI0_MASTER_SLAVE_BIT);
	}
	else if (a_config_Ptr->s_master_slave == SLAVE_ENABLE)
	{
		SET_BIT(SPI0_CTL_REG_1,SPI0_MASTER_SLAVE_BIT);	
	}
	
	/* Configure which clock is used by SPI0 */
	SPI0_CLK_CFG_REG=SPI_CLK_CFG;
  
	/* Set prescaler value */
	SPI0_CLKPS_REG= a_config_Ptr->s_clk_ps_div;
	
	/* Set priority 2 for  SPI_Receive_Handler*/
  NVIC_PRI1_REG &= 0x0FFFFFFF;
  NVIC_PRI1_REG |= SPI0_HANDLER_PRIORITY;
  
  /* Set interrupt number in vector table */
  SET_BIT(NVIC_EN0_REG,NVIC_SPI0_INTERRUPT);
  
}
/********************************************************************************
*[Function Name]: SPI_sendByte.
*[Description]  : This function is responsible for sending one byte.
*[in]		: uint8 a_data:contain data that will be sent.
*[out]		: None.
*[in/out]	: None.
*[Returns]	: None.
*********************************************************************************/
void SPI_sendByte(const uint8 a_data){
  
  /* Write data I want to send */
  
  /* Polling until data is sent*/
  
  /* Clear Tx flag */
}

/********************************************************************************
*[Function Name]: SPI_receiveByte.
*[Description]  : This function is responsible for receiving one byte.
*[in]		: uint8 a_data:contain data that will be sent.
*[out]		: None.
*[in/out]	: None.
*[Returns]	: The received data.
*********************************************************************************/
uint8 SPI_receiveByte(void){

  /* return data */
	return 0;
}
     