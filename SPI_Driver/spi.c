/******************************************************************************
*
* Module:SPI
*
* File Name: spi.h
*
* Description: Source file for spi module.
*              This module use receiver with interrupt and transmitting with polling.
*              Options given : 
*                -Changeable baud rate.
*                -Changeable Data size.
*								 -Make device Master or Slave.	
*              The rest is fixed.
* Author: Esmail Ahmed
*
*******************************************************************************/
#include "spi.h"

/*******************************************************************************
 *****************************GLOBAL VARIABLES**********************************
 *******************************************************************************/

/* Global variable used for call back technique */

static void(*g_SPI_interrupt_Func_Ptr)(void);

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
	
  /*Set A2,A3,A4 and A5 as Digital Pins*/
  GPIO_PORTA_DEN_REG |= SPI0_PINS_MASK;

  /* Disable SPI0 */
	CLEAR_BIT(SPI0_CTL_REG_1,SPI0_ENABLE_BIT);

  /* Select Master or Slave */
	SPI_Master_Slave_Enable(a_config_Ptr->s_master_slave );
	
	/* Configure which clock is used by SPI0 */
	SPI0_CLK_CFG_REG = SPI_CLK_CFG;
  
	/* Set prescaler value */
	SPI0_CLKPS_REG= a_config_Ptr->s_clk_ps_div;
	
	/*Serial clock rate (SCR)
	 *The protocol mode:TI SSF.
	 *The data size (DSS)
	*/
	SPI0_CTL_REG_0 = (((uint32) a_config_Ptr->s_sc_rate << SPI0_SCR_BIT)
								   |(uint32) (1<<SPI0_SCR_BIT)
									 |(uint32) a_config_Ptr->s_data_size);
	
	/* Set priority 2 for  SPI_Receive_Handler*/
  NVIC_PRI1_REG &= 0x0FFFFFFF;
  NVIC_PRI1_REG |= SPI0_HANDLER_PRIORITY;
  
  /* Set interrupt number in vector table */
  SET_BIT(NVIC_EN0_REG,NVIC_SPI0_INTERRUPT);
  
	/* Enble receive interrupt */
	SET_BIT(SPI0_INT_MASK_REG,SPI0_RX_INT_ENABLE);
	
	/* Enaable SPI0 */
	SET_BIT(SPI0_CTL_REG_1,SPI0_ENABLE_BIT);
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
  /* Polling To check if  data is being sent */
  while(BIT_IS_SET(SPI0_STATUS_REG,SPI0_BUSY_CHECK));
  /* Write data I want to send */
  SPI0_DATA_REG = a_data;
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
	return (uint8)SPI0_DATA_REG;
}
/********************************************************************************
*[Function Name]: SPI_Master_Slave_Enable.
*[Description]  : This function is responsible for Making Master or Slave.
*[in]		: uint8 a_master_or_slave:contain data that will choose master or slave.
*[out]		: None.
*[in/out]	: None.
*[Returns]	: None.
*********************************************************************************/
void SPI_Master_Slave_Enable(uint8 a_master_or_slave){
	
	/* Select Master or Slave */
	if(a_master_or_slave == MASTER_ENABLE)
	{
		/* Set Pins A2,A3,A4 and A5 directions for SPI MASTER */
		GPIO_PORTA_DIR_REG &= (uint32)~SPI0_PINS_MASK;
		GPIO_PORTA_DIR_REG |= SPI0_PINS_MASTER_DIR_MASK;
		CLEAR_BIT(SPI0_CTL_REG_1,SPI0_MASTER_SLAVE_BIT);
	}
	else if (a_master_or_slave == SLAVE_ENABLE)
	{
		/* Set Pins A2,A3,A4 and A5 directions for SPI SLAVE */
		GPIO_PORTA_DIR_REG &= (uint32)~SPI0_PINS_MASK;
		GPIO_PORTA_DIR_REG |= SPI0_PINS_SLAVE_DIR_MASK;
		SET_BIT(SPI0_CTL_REG_1,SPI0_MASTER_SLAVE_BIT);
	}
	
}
/**********************************************************************************************
 *[Function Name]:	SPI_callBackAdress
 *[Description] :This function is responsible for saving the address that will be called after interrupts happen
 *[in] :void(*a_Func_Ptr)(void): Pointer to function used to store function's address ISR will call
 *[out] :None.
 *[in/out] :None.
 *[Returns] :.
 ***********************************************************************************************/
void SPI_callBackAdress(void(*a_Func_Ptr)(void)){
		g_SPI_interrupt_Func_Ptr=a_Func_Ptr;
}

/*******************************************************************************
***************************INTERRUPT HANDLER************************************
*******************************************************************************/

/* ISR for Receiving a Byte*/     
void SPI_Receive_Handler(void)
{
	SET_BIT(SPI0_INT_CLEAR_REG,SPI0_INT_CLEAR);
	/* Call the function in the Scheduler using Call Back concept */
	(*g_SPI_interrupt_Func_Ptr)();
}
