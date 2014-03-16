/*
*************************************************************************************
**文件说明：spi配置
**文件名称：spi_cfg.c 
**创建日期：2013.12.08  
**创 建 人：ww
**-----------------------------------------------------------------------------------
**修改日期：2013.xx.xx
**修改说明：
*************************************************************************************
*/
#include "spi_cfg.h"


/*
*************************************************************************************
* 名    称：void SPI1_Config(void)
* 功    能：SPI配置
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void SPI1_Config(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1, ENABLE);  //开启SPI1模块时钟，辅助功能时钟
    
    GPIO_Config(EN_GPIO_SPI1,0);                                                //配置SPI1端口
    
	SPI_I2S_DeInit(SPI1);	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI全双工模式	
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //主机模式	
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //SPI通信数据位--8位	
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;							//SCLK空闲时  置低电平	
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						//第一个时钟沿捕获数据	
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //软件管理NSS信号	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  //SPI波特率   分频值  72M/2=36M	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //SPI通信 高位在前	
	SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC冗余校验多项式	
	SPI_Init(SPI1,&SPI_InitStructure);                                  //初始化SPI1
	SPI_Cmd(SPI1,ENABLE);                                               //SPI使能
}

/*
*************************************************************************************
* 名    称：Uint16 SPI1_ReadWriteByte(Uint16 TxData)
* 功    能：SPI发送/接收单字节数据
* 入口参数：Uint16 TxData
* 出口参数：Uint16 RxData
*************************************************************************************
*/
Uint16 SPI1_ReadWriteByte(Uint16 TxData)
{		
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);		//等待发送缓冲区空
	SPI_I2S_SendData(SPI1, TxData);	               						//发一个字节

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);	 	//等待数据接收
	return SPI_I2S_ReceiveData(SPI1);	        						//返回接收到的数据   
}

/*
*************************************************************************************
* 名    称：void SPI1_Config(void)
* 功    能：SPI配置
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void SPI2_Config(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //开启辅助功能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  //开启SPI2模块时钟
    
    GPIO_Config(EN_GPIO_SPI2,0);                          //配置SPI2端口
    
	SPI_I2S_DeInit(SPI2);	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI全双工模式	
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //主机模式	
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //SPI通信数据位--16位	
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;							//SCLK空闲时  置高电平	
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;						//第二个时钟沿捕获数据	
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //软件管理NSS信号	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  //SPI波特率   分频值  72M/2=36M	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //SPI通信 高位在前	
	SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC冗余校验多项式	
	SPI_Init(SPI2,&SPI_InitStructure);                                  //初始化SPI2
	SPI_Cmd(SPI2,ENABLE);                                               //SPI使能
}


/*
*************************************************************************************
* 名    称：Uint16 SPI2_ReadWriteByte(Uint16 TxData)
* 功    能：SPI发送/接收单字节数据
* 入口参数：Uint16 TxData
* 出口参数：Uint16 RxData
*************************************************************************************
*/
Uint16 SPI2_ReadWriteByte(Uint16 TxData)
{		
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);		//等待发送缓冲区空
	SPI_I2S_SendData(SPI2, TxData);	               						//发一个字节

    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	 	//等待数据接收
	return SPI_I2S_ReceiveData(SPI2);	        						//返回接收到的数据			    
}



















