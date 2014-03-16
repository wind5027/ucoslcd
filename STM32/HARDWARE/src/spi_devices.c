/*
*************************************************************************************
**文件说明：spi器件操作
**文件名称：spi_devices.c 
**创建日期：2013.12.16  
**创 建 人：ww
**-----------------------------------------------------------------------------------
**修改日期：2013.xx.xx
**修改说明：
*************************************************************************************
*/
#include "spi_cfg.h"
#include "spi_devices.h"
#include "gpio_cfg.h"


/*
********************************************************************************
**函数名称：Uint8 SPI_Disk_SendByte(Uint8 Byte)
**函数功能：SPI字节读取及写入
**入口参数：无
**返回参数：无
********************************************************************************
*/
Uint8 SPI_DISK_SendByte(Uint8 Byte)
{
    return SPI1_ReadWriteByte(Byte);
}

Uint8 SPI_DISK_ReciveByte(void)
{
    return SPI1_ReadWriteByte(0x00);
}
void SPI_DISK_WriteEnable(void)
{
    FMEnable();                   // Clr CS
    SPI_DISK_SendByte(MEM_WREN);  // Set Write Enable Latch CMD
    FMDisable();                  // Set CS
}

/*
********************************************************************************
**函数名称：void SPI_DISK_Write(Uint16 Addr, Uint8 * Buf, Uint8 Cont)
**函数功能：向SPI存储器写入Cont个数据
**入口参数：Uint16 Addr 写入的地址
            Uint8 * Buf 将写入的数据缓冲区
            Uint8 Cont  写入数据个数
**返回参数：无
********************************************************************************
*/
void SPI_DISK_Write(Uint16 Addr, Uint8 * Buf, Uint8 Cont)
{
    SPI_DISK_WriteEnable();                     // Enable the write accsss
    FMEnable();                                 // Clr CS
    SPI_DISK_SendByte(MEM_WRITE);               // Write Memory Data CMD
    SPI_DISK_SendByte((Uint8)(Addr >> 8));      // Send Address MSB
    SPI_DISK_SendByte((Uint8)Addr);             // Send Address LSB
    do{
        SPI_DISK_SendByte( * Buf);              // Send Data
        Buf ++;
        Cont --;
    }while(Cont);
    FMDisable();                                // Set CS
}

/*
********************************************************************************
**函数名称：void SPI_DISK_Read(Uint16 Addr, Uint8 * Buf, Uint8 Cont)
**函数功能：向SPI存储器读取Cont个数据
**入口参数：Uint16 Addr 读取的地址
            Uint8 * Buf 将读取的数据缓冲区
            Uint8 Cont  读取数据个数
**返回参数：无
********************************************************************************
*/
void SPI_DISK_Read(Uint16 Addr, Uint8 * Buf, Uint8 Cont)
{
    FMEnable();                                 // Clr CS
    SPI_DISK_SendByte(MEM_READ);                // Read Memory Data CMD
    SPI_DISK_SendByte((Uint8)(Addr >> 8));      // Recive Address MSB
    SPI_DISK_SendByte((Uint8)Addr);             // Recive Address LSB
    do{
        *Buf = SPI_DISK_ReciveByte();           // Recive Data
        Buf ++;
        Cont --;
    }while(Cont);
    FMDisable();                                // Set CS
}

/*
********************************************************************************
**函数名称：void SPI_DISK_SetStatus(Uint8 Status)
**函数功能：设置 SPI 存储器状态码
**入口参数：Uint8 Status 状态字
**返回参数：无
********************************************************************************
*/
void SPI_DISK_SetStatus(Uint8 Status)
{
    SPI_DISK_WriteEnable();                     // Enable the write accsss
    FMEnable();                                 // Clr CS
    SPI_DISK_SendByte(MEM_WRSR);                // Write Status Register CMD
    SPI_DISK_SendByte(Status);                  // Send Status Register
    FMDisable();                                // Set CS
}
/*
********************************************************************************
**函数名称：Uint8 SPI_DISK_GetStatus(void)
**函数功能：获取 SPI 存储器状态码
**入口参数：无
**返回参数：Uint8 Status 状态字
********************************************************************************
*/
Uint8 SPI_DISK_GetStatus(void)
{
    Uint8 Status;
    FMEnable();                                 // Clr CS
    SPI_DISK_SendByte(MEM_RDSR);                // Read Status Register CMD
    Status = SPI_DISK_ReciveByte();             // Recive Status Register
    FMDisable();                                // Set CS
    return Status;
}

/*
********************************************************************************
**函数名称：Uint8 SPI_Flash_SendByte(Uint8 Byte)
**函数功能：SPI字节读取及写入
**入口参数：无
**返回参数：无
********************************************************************************
*/
Uint16 SPI_FLASH_SendByte(Uint16 Byte)
{
    return SPI2_ReadWriteByte(Byte);
}

Uint16 SPI_FLASH_ReciveByte(void)
{
    return SPI2_ReadWriteByte(0x00);
}
void SPI_FLASH_WriteEnable(void)
{
    FlashEnable();                   // Clr CS
    SPI_FLASH_SendByte(MEM_WREN);    // Set Write Enable Latch CMD
    FlashDisable();                  // Set CS
}

/*
********************************************************************************
**函数名称：void SPI_FLASH_SendAddr(Uint32 Addr, Uint8 CMD)
**函数功能：向SPI Flash 操作码及发送地址  8bit模式
**入口参数：Uint32 Addr 发送的地址
            Uint16 CMD  操作码
**返回参数：无
********************************************************************************
*/
void SPI_FLASH_SendAddr(Uint32 Addr, Uint8 CMD)
{
    SPI_FLASH_SendByte(CMD);                     // Read Memory Data CMD
    SPI_FLASH_SendByte((Uint8)(Addr >> 16));     // Recive Address MSB
    SPI_FLASH_SendByte((Uint8)(Addr >> 8));      // Recive Address MSB
    SPI_FLASH_SendByte((Uint8)Addr);             // Recive Address LSB
}

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
void SPI_FLASH_Read(Uint32 Addr, Uint8 * Buf, Uint32 Cont)
{
    FlashEnable();                                         // Clr CS
    SPI_FLASH_SendAddr(Addr,MEM_READ);                     //Send CMD and Address
    do{
        *Buf = SPI_FLASH_ReciveByte();                     // Recive Data
        Buf ++;
        Cont --;
    }while(Cont);
    FlashDisable();                                        // Set CS
}














