/*
*************************************************************************************
**文件说明：spi器件操作
**文件名称：spi_devices.h 
**创建日期：2013.12.16  
**创 建 人：ww
**-----------------------------------------------------------------------------------
**修改日期：2013.xx.xx
**修改说明：
*************************************************************************************
*/
#ifndef SPI_DEVICES_H
#define SPI_DEVICES_H

#include "user_type.h"
#include "stm32f10x.h"




/*
--------------------------------------------------------------------------------
说明：SPI Memory Op-code Commands
--------------------------------------------------------------------------------
*/
#define MEM_WREN          (0x06) /* Set Write Enable Latch 0000 0110b*/
#define MEM_WRDI          (0x04) /* Write Disable 0000 0100b */
#define MEM_RDSR          (0x05) /* Read Status Register 0000 0101b */
#define MEM_WRSR          (0x01) /* Write Status Register 0000 0001b */
#define MEM_READ          (0x03) /* Read Memory Data 0000 0011b */ 
#define MEM_FSTRD         (0x0b) /* Fast Read Memory Data 0000 1011b */
#define MEM_WRITE         (0x02) /* Write Memory Data 0000 0010b */
#define MEM_SLEEP         (0xb9) /* Enter Sleep Mode 1011 1001b */
#define MEM_RDID          (0x9f) /* Read Device ID 1001 1111b */
#define MEM_SNR           (0xc3) /* Read S/N 1100 0011b */



/*
********************************************************************************
**函数名称：void SPI_FLASH_SendAddr(Uint32 Addr, Uint8 CMD)
**函数功能：向SPI Flash 操作码及发送地址  8bit模式
**入口参数：Uint32 Addr 发送的地址
            Uint16 CMD  操作码
**返回参数：无
********************************************************************************
*/
extern void SPI_FLASH_SendAddr(Uint32 Addr, Uint8 CMD);


/*
********************************************************************************
**函数名称：void SPI_FLASH_Read(Uint32 Addr, Uint8 * Buf, Uint32 Cont)
**函数功能：向SPI存储器读取Cont个数据 8bit模式
**入口参数：Uint32 Addr 读取的地址
            Uint16 * Buf 将读取的数据缓冲区
            Uint32 Cont  读取数据个数
**返回参数：无
********************************************************************************
*/
extern void SPI_FLASH_Read(Uint32 Addr, Uint8 * Buf, Uint32 Cont);



#endif
