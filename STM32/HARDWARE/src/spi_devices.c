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









