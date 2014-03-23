/*
*************************************************************************************
**文件说明：ADC操作任务
**文件名称：task_adc.c 
**创建日期：2014.03.22  
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




/***************************************************
说明：ADC 电压值获取任务
****************************************************/
void TaskGetADCVolt(void *pdata)
{
    Uint8 err;
    VoltageDat * VoltAverage;    //电压平均值
    NUM_DisBuf * ADCDisBuf;      //ADC 数字显示缓冲区指针
    Uint8 i;
    pdata = pdata;
   
    for(;;){
        VoltAverage = OSMemGet(MEMPointer,&err);      //申请内存空间
        ADCDisBuf   = (NUM_DisBuf *)(VoltAverage + sizeof(VoltageDat));
        if(err == OS_ERR_NONE){
            for(i = 0; i < 32; i ++){
                OSTimeDlyHMSM(0,0,0,20);
                VoltAverage->AVolt[0] += ADC1ValueArray[0];
                VoltAverage->AVolt[1] += ADC1ValueArray[1];
                VoltAverage->AVolt[2] += ADC1ValueArray[2];
                VoltAverage->AVolt[3] += ADC1ValueArray[3];
                VoltAverage->AVolt[4] += ADC1ValueArray[4];
                VoltAverage->AVolt[5] += ADC1ValueArray[5];
            }
            VoltAverage->AVolt[0] = VoltAverage->AVolt[0] * ADC_VOLT_MAG_IN0;
            VoltAverage->AVolt[1] = VoltAverage->AVolt[1] * ADC_VOLT_MAG_IN1; 
            VoltAverage->AVolt[2] = VoltAverage->AVolt[2] * ADC_VOLT_MAG_IN2; 
            VoltAverage->AVolt[3] = VoltAverage->AVolt[3] * ADC_VOLT_MAG_IN3; 
            VoltAverage->AVolt[4] = VoltAverage->AVolt[4] * ADC_VOLT_MAG_IN4; 
            VoltAverage->AVolt[5] = VoltAverage->AVolt[5] * ADC_VOLT_MAG_IN5; 
            
            ADCDisBuf->NumSize                 = ASCII_32_64;
            ADCDisBuf->DisControl.Place.X      = 140;                 //VIN0 X
            ADCDisBuf->DisControl.Place.Y      = 125;                 //VIN0 Y
            ADCDisBuf->DisControl.WordColor    = RED;
            ADCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR; 
            NUM_ShortHexToBCD(VoltAverage->AVolt[0],ADCDisBuf); //数据到显示缓存
            NUM_OffZeroDisBuf(ADCDisBuf);                       //灭零
            ADCDisBuf->Offset                  = 0;
            ADCDisBuf->DisN                    = 4;                    
            OSMboxPost(LCDNumDisBox,ADCDisBuf);         //发送消息邮箱内容是显示VIN0
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号

            ADCDisBuf->NumSize                 = ASCII_32_64;
            ADCDisBuf->DisControl.Place.X      = 530;                 //VIN1 X
            ADCDisBuf->DisControl.Place.Y      = 125;                 //VIN1 Y
            ADCDisBuf->DisControl.WordColor    = RED;
            ADCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR; 
            NUM_ShortHexToBCD(VoltAverage->AVolt[1],ADCDisBuf);
            NUM_OffZeroDisBuf(ADCDisBuf);                       //灭零
            ADCDisBuf->Offset                  = 0;
            ADCDisBuf->DisN                    = 4;                    
            OSMboxPost(LCDNumDisBox,ADCDisBuf);         //发送消息邮箱内容是显示VIN1
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号
            
            ADCDisBuf->NumSize                 = ASCII_32_64;
            ADCDisBuf->DisControl.Place.X      = 140;                 //VIN2 X
            ADCDisBuf->DisControl.Place.Y      = 236;                 //VIN2 Y
            ADCDisBuf->DisControl.WordColor    = RED;
            ADCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR; 
            NUM_ShortHexToBCD(VoltAverage->AVolt[2],ADCDisBuf);
            NUM_OffZeroDisBuf(ADCDisBuf);                       //灭零
            ADCDisBuf->Offset                  = 0;
            ADCDisBuf->DisN                    = 4;                    
            OSMboxPost(LCDNumDisBox,ADCDisBuf);         //发送消息邮箱内容是显示VIN2
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号
            
            ADCDisBuf->NumSize                 = ASCII_32_64;
            ADCDisBuf->DisControl.Place.X      = 530;                 //VIN3 X
            ADCDisBuf->DisControl.Place.Y      = 236;                 //VIN3 Y
            ADCDisBuf->DisControl.WordColor    = RED;
            ADCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR; 
            NUM_ShortHexToBCD(VoltAverage->AVolt[3],ADCDisBuf);
            NUM_OffZeroDisBuf(ADCDisBuf);                       //灭零
            ADCDisBuf->Offset                  = 0;
            ADCDisBuf->DisN                    = 4;                    
            OSMboxPost(LCDNumDisBox,ADCDisBuf);         //发送消息邮箱内容是显示VIN3
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号
            
            ADCDisBuf->NumSize                 = ASCII_32_64;
            ADCDisBuf->DisControl.Place.X      = 140;                 //VIN4 X
            ADCDisBuf->DisControl.Place.Y      = 355;                 //VIN4 Y
            ADCDisBuf->DisControl.WordColor    = RED;
            ADCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR; 
            NUM_ShortHexToBCD(VoltAverage->AVolt[4],ADCDisBuf);
            NUM_OffZeroDisBuf(ADCDisBuf);                       //灭零
            ADCDisBuf->Offset                  = 0;
            ADCDisBuf->DisN                    = 4;                    
            OSMboxPost(LCDNumDisBox,ADCDisBuf);         //发送消息邮箱内容是显示VIN4
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号
            
            ADCDisBuf->NumSize                 = ASCII_32_64;
            ADCDisBuf->DisControl.Place.X      = 530;                 //VIN5 X
            ADCDisBuf->DisControl.Place.Y      = 344;                 //VIN5 Y
            ADCDisBuf->DisControl.WordColor    = RED;
            ADCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR; 
            NUM_ShortHexToBCD(VoltAverage->AVolt[5],ADCDisBuf);
            NUM_OffZeroDisBuf(ADCDisBuf);                       //灭零
            ADCDisBuf->Offset                  = 0;
            ADCDisBuf->DisN                    = 4;                    
            OSMboxPost(LCDNumDisBox,ADCDisBuf);         //发送消息邮箱内容是显示VIN5
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号
          
            MEM_Set((Uint8 *)VoltAverage,0,PARTITION_LENGTH);       //内存清零            
            err = OSMemPut(MEMPointer,VoltAverage);                 //释放内存

        }
        OSTimeDlyHMSM(0,0,0,300); 
    }
}















