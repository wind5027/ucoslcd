/*
*************************************************************************************
**文件说明：dma配置
**文件名称： dma_cfg.c 
**创建日期：2013.11.06  
**创 建 人：王玮
**-----------------------------------------------------------------------------------
**修改日期：2013.xx.xx
**修改说明：
*************************************************************************************
*/
#include "dma_cfg.h"

/*
*************************************************************************************
* 名    称：void DMA_Config(DMA_ControlDat * ControlDat,Uint16 DMAMask)
* 功    能：DMA配置
* 入口参数：DMA_ControlDat * ControlDat                
            Uint16 DMAMask
* 出口参数：无
*************************************************************************************
*/
void DMA_Config(DMA_ControlDat * ControlDat,Uint16 DMAMask )
{
    DMA_InitTypeDef DMA_InitStructure;
    Uint16 Tmp = 0x8001;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    if(ReadMask(DMAMask,EN_DMA_ADC1) == EN_DMA_ADC1) {
        
        DMA_DeInit(DMA1_Channel1);                                                     //复位DMA1通道1
        DMA_InitStructure.DMA_PeripheralBaseAddr = ControlDat->DMA_PeripheralBaseAddr; //设置外部设备基地址    ADC地址
        DMA_InitStructure.DMA_MemoryBaseAddr     = ControlDat->DMA_MemoryBaseAddr;     //设置内存地址
        DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;          //源地址每次传输完成后不变
        DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;               //目的地内存地址每次传输完成后自增
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //源数据大小为半字
        DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;        //目的地数据大小为半字
        DMA_InitStructure.DMA_BufferSize         = ControlDat->DMA_BufferSize;         //DMA传送数据块大小
        DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;              //数据方向 0：从外设读 1：从存储器读
        DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;                  //DMA循环传送
        DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                  //DMA 优先级--高
        DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                    //DMA内存到内存关闭
        DMA_Init(DMA1_Channel1,&DMA_InitStructure);
        DMA_Cmd(DMA1_Channel1,ENABLE);
    }
    if(ReadMask(DMAMask,EN_DMA_LCD_CLR) == EN_DMA_LCD_CLR) {
        
        DMA_DeInit(DMA1_Channel6);
        DMA_InitStructure.DMA_PeripheralBaseAddr = ControlDat->DMA_PeripheralBaseAddr; //外设地址
        DMA_InitStructure.DMA_MemoryBaseAddr     = ControlDat->DMA_MemoryBaseAddr;     //存储器地址               
        DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;          //外设地址增量模式
        DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable;              //存储器地址增量模式
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //外设数据宽度
        DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;        //存储器数据宽度
        DMA_InitStructure.DMA_BufferSize         = ControlDat->DMA_BufferSize;         //数据传输数量
        DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;              //数据传输方向 0：从外设读 1：从存储器读
        DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;                  //循环模式
        DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                  //通道优先级
        DMA_InitStructure.DMA_M2M                = DMA_M2M_Enable;                     //存储器到存储器模式
        DMA_Init(DMA1_Channel6,&DMA_InitStructure);
    }
    if(ReadMask(DMAMask,EN_DMA_LCD_DAT) == EN_DMA_LCD_DAT) {
        
        DMA_DeInit(DMA1_Channel6);
        DMA_InitStructure.DMA_PeripheralBaseAddr = ControlDat->DMA_PeripheralBaseAddr; //外设地址
        DMA_InitStructure.DMA_MemoryBaseAddr     = ControlDat->DMA_MemoryBaseAddr;     //存储器地址               
        DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;          //外设地址增量模式
        DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;               //存储器地址增量模式
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //外设数据宽度
        DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;        //存储器数据宽度
        DMA_InitStructure.DMA_BufferSize         = ControlDat->DMA_BufferSize;         //数据传输数量
        DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;              //数据传输方向 0：从外设读 1：从存储器读
        DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;                    //循环模式
        DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                  //通道优先级
        DMA_InitStructure.DMA_M2M                = DMA_M2M_Enable;                     //存储器到存储器模式
        DMA_Init(DMA1_Channel6,&DMA_InitStructure);
    }
    if(ReadMask(DMAMask,EN_DMA_SPI1) == EN_DMA_SPI1){
        DMA_DeInit(DMA1_Channel2);
        DMA_InitStructure.DMA_PeripheralBaseAddr = ControlDat->DMA_PeripheralBaseAddr; //外设地址
        DMA_InitStructure.DMA_MemoryBaseAddr     = ControlDat->DMA_MemoryBaseAddr;     //存储器地址 
        DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;          //外设地址增量模式
        DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;               //存储器地址增量模式
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;        //外设数据宽度
        DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;            //存储器数据宽度
        DMA_InitStructure.DMA_BufferSize         = ControlDat->DMA_BufferSize;         //数据传输数量
        DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;              //数据传输方向 0：从外设读 1：从存储器读
        DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;                    //循环模式
        DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                  //通道优先级 
        DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                    //存储器到存储器模式
        DMA_Init(DMA1_Channel2,&DMA_InitStructure);

        DMA_DeInit(DMA1_Channel3);
        DMA_InitStructure.DMA_PeripheralBaseAddr = ControlDat->DMA_PeripheralBaseAddr;
        DMA_InitStructure.DMA_MemoryBaseAddr     = ControlDat->DMA_MemoryBaseAddr;
        DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
        DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable;
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
        DMA_InitStructure.DMA_BufferSize         = ControlDat->DMA_BufferSize;
        DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
        DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
        DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium; 
        DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
        DMA_Init(DMA1_Channel3,&DMA_InitStructure);
        
        SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
        SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    }
    if(ReadMask(DMAMask,EN_DMA_SPI2) == EN_DMA_SPI2){  //使用DMA将SPI2 flash数据搬运到FSMC lcd上
        DMA_DeInit(DMA1_Channel4);                     //启用通道4 SPI2_RX
        DMA_InitStructure.DMA_PeripheralBaseAddr = ControlDat->DMA_PeripheralBaseAddr; //外设地址
        DMA_InitStructure.DMA_MemoryBaseAddr     = ControlDat->DMA_MemoryBaseAddr;     //存储器地址 
        DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;          //外设地址增量模式
        DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;               //存储器地址增量模式
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;        //外设数据宽度
        DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;            //存储器数据宽度
        DMA_InitStructure.DMA_BufferSize         = ControlDat->DMA_BufferSize;         //数据传输数量
        DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;              //数据传输方向 0：从外设读 1：从存储器读
        DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;                    //循环模式
        DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                  //通道优先级 
        DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                    //存储器到存储器模式
        DMA_Init(DMA1_Channel4,&DMA_InitStructure);
        
        
        DMA_DeInit(DMA1_Channel5);                     //启用通道5 SPI2_TX
        DMA_InitStructure.DMA_PeripheralBaseAddr = ControlDat->DMA_PeripheralBaseAddr; //外设地址
        DMA_InitStructure.DMA_MemoryBaseAddr     = (Uint32)(&Tmp);                     //存储器地址      
        DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;          //外设地址增量模式
        DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable;              //存储器地址增量模式
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;            //外设数据宽度
        DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;            //存储器数据宽度
        DMA_InitStructure.DMA_BufferSize         = ControlDat->DMA_BufferSize;         //数据传输数量
        DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;              //数据传输方向 0：从外设读 1：从存储器读
        DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;                    //循环模式
        DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                  //通道优先级 
        DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                    //存储器到存储器模式
        DMA_Init(DMA1_Channel5,&DMA_InitStructure);

        SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
        SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
    }
}

/*
*************************************************************************************
* 名    称：void DMA_ChannelCmd(Uint16 DMAMask ,FunctionalState NewState)
* 功    能：DMA通道使能配置
* 入口参数：Uint16 DMAMask ,FunctionalState NewState
* 出口参数：无
*************************************************************************************
*/
void DMA_ChannelCmd(Uint16 DMAMask ,FunctionalState NewState)
{
    if((ReadMask(DMAMask,EN_DMA_LCD_CLR) == EN_DMA_LCD_CLR) || 
       (ReadMask(DMAMask,EN_DMA_LCD_DAT) == EN_DMA_LCD_DAT)) {       
        DMA_ClearFlag(DMA1_FLAG_GL6|DMA1_FLAG_TC6|DMA1_FLAG_HT6|DMA1_FLAG_TE6);
//        DMA_ITConfig(DMA1_Channel6,DMA_IT_TC,NewState);
        DMA_Cmd(DMA1_Channel6,NewState);
    }
    
    if(ReadMask(DMAMask,EN_DMA_SPI1) == EN_DMA_SPI1){
        DMA_ClearFlag(DMA1_FLAG_GL3|DMA1_FLAG_TC3|DMA1_FLAG_HT3|DMA1_FLAG_TE3);
        DMA_Cmd(DMA1_Channel2,NewState);
        DMA_Cmd(DMA1_Channel3,NewState);
        
        DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,NewState); 
        DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,NewState);         
    }
    if(ReadMask(DMAMask,EN_DMA_SPI2) == EN_DMA_SPI2){
       
        DMA_ClearFlag(DMA1_FLAG_GL4|DMA1_FLAG_TC4|DMA1_FLAG_HT4|DMA1_FLAG_TE4);
        DMA_ClearFlag(DMA1_FLAG_GL5|DMA1_FLAG_TC5|DMA1_FLAG_HT5|DMA1_FLAG_TE5); 
        DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
        
        DMA_Cmd(DMA1_Channel4,NewState);
        DMA_Cmd(DMA1_Channel5,NewState);  
    }
}




































