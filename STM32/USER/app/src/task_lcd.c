/*
*************************************************************************************
**文件说明：LCD操作任务
**文件名称：task_lcd.c 
**创建日期：2014.03.20  
**创 建 人：王玮
**-----------------------------------------------------------------------------------
**修改日期：2014.xx.xx
**修改说明：
*************************************************************************************
*/
#include "user_cfg.h"

#include "drivers.h"
#include "task.h"
#include "lcd_tft.h"
#include "memory.h"

Uint8 * BuffAddr[2];
DMA_ControlDat  ControlDat;

/***************************************************
说明：LCD背景更新任务
****************************************************/
void TaskLCDBrgUpdate(void *pdata)
{
    Uint8 err1;
    Uint8 err2;
    Uint16 cnt;
    pdata = pdata;    
    
    for(;;){
        cnt = 0;
        BuffAddr[0] = OSMemGet(MEMPointer,&err1);      //申请内存空间
        BuffAddr[1] = OSMemGet(MEMPointer,&err2);      //申请内存空间
        if((err1 == OS_ERR_NONE) && (err2 == OS_ERR_NONE)){          
            
            OSMutexPend(FSMCMutex,0,&err1);     //等待FSMC互斥信号量
            
            LCD_SetCursorXY(0,0);               //设置光标起点 准备写数据          

            while(cnt < 800 * 480 * 2 / PARTITION_LENGTH){ //计算满屏数据搬运次数  使用双buff交替传输
                ControlDat.DMA_PeripheralBaseAddr = (Uint32)&SPI2->DR;             //SPI2->DR  外设地址
                ControlDat.DMA_MemoryBaseAddr     = (Uint32)BuffAddr[cnt & 0x01];  //存储器地址
                ControlDat.DMA_BufferSize         = PARTITION_LENGTH;              //DMA传输长度
                LCD_SetBkgrdSpiOfDma((Uint32)cnt * PARTITION_LENGTH,&ControlDat);       
                OSSemPend(DMAC4OverSemp,0,&err1);                                  //等待DMA通道4传输完成信号
                FlashDisable();      //SPI Flash器件使用完成 
                
                ControlDat.DMA_PeripheralBaseAddr = LCD_ADDR_DAT;                  //LCD  外设地址
                ControlDat.DMA_MemoryBaseAddr     = (Uint32)BuffAddr[cnt & 0x01];  //存储器地址
                ControlDat.DMA_BufferSize         = PARTITION_LENGTH / 2;          //DMA传输长度
                DMA_Config(&ControlDat,EN_DMA_LCD_DAT);                            //配置DMA通道1 FSMC传输
                DMA_ChannelCmd(EN_DMA_LCD_DAT,ENABLE);                             //打开DMA通道1 写LCD
                cnt ++;
            }
 
            OSTimeDlyHMSM(0,0,0,100);          //等待最后一次DMA使用FSMC
            OSMutexPost(FSMCMutex);            //释放FSMC互斥信号量
            
            MEM_Set((Uint8 *)BuffAddr[0],0,PARTITION_LENGTH);        //内存清零
            MEM_Set((Uint8 *)BuffAddr[1],0,PARTITION_LENGTH);        //内存清零            
            err1 = OSMemPut(MEMPointer,BuffAddr[0]);                 //释放内存
            err2 = OSMemPut(MEMPointer,BuffAddr[1]);                 //释放内存
        }
        OSTimeDlyHMSM(0,5,0,0); 
    }
}

/***************************************************
说明：数字显示任务
****************************************************/
void TaskLCDNumDis(void *pdata)
{
    Uint8 err;
    NUM_DisBuf * DisBufP;
    pdata = pdata;
   
    for(;;){
        DisBufP = OSMboxPend(LCDNumDisBox,0,&err); //等待LCD数字显示邮箱
        OSMutexPend(FSMCMutex,0,&err);             //等待FSMC互斥信号量
        LCD_WriteNum(DisBufP);                     //写数字到LCD
        OSMutexPost(FSMCMutex);                    //释放FSMC互斥信号量
        OSSemPost(LCDNumDisOverSemp);              //发送数字写完成信号
    }
}













