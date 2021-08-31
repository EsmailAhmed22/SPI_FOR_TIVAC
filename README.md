# SPI_FOR_TIVAC
## SUMMARY
* This module use receiver with interrupt and transmitting with polling.
* CALLBACK Address technique is used.
* Dynamic Driver for Serial Peripheral Interface (SPI).
## OPTIONS GIVEN
* Changeable Baud rate.
* Changeable Data size.
* Make device Master or Slave.
## FUNCTIONS IMPLEMENTED

* __void SPI_init(const SPI_ConfigType *a_config_Ptr);__
    * This function is responsible for initializing the SPI via configuration structure.

* **void SPI_sendByte(const uint8 a_data);**
  * This function is responsible for sending one byte.

* **uint8 SPI_receiveByte(void);**
  * This function is responsible for receiving one byte.

* **void SPI_Master_Slave_Enable(uint8 a_master_or_slave);**
  * This function is responsible for Making Master or Slave.

* __void SPI_callBackAdress(void(*a_Func_Ptr)(void));__
   * This function is responsible for saving the address that will be called after interrupts happen
