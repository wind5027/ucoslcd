/*
*************************************************************************************
**文件说明：任务
**文件名称：task.c 
**创建日期：2013.11.07  
**创 建 人：王玮
**-----------------------------------------------------------------------------------
**修改日期：2013.xx.xx
**修改说明：
*************************************************************************************
*/
#include "user_cfg.h"
#include "user_type.h"
#include "task.h"
#include "drivers.h"
#include "lcd_tft.h"
#include "memory.h"
#include "num_operation.h"




/***************************************************
说明：RTC更新任务
****************************************************/
void TaskRTCUpdate(void *pdata)
{
    Uint8 err;
    TimeDat    * CurrentTime;        //当前时间数据指针
    NUM_DisBuf * RTCDisBuf;          //RTC 数字显示缓冲区指针
    
    pdata = pdata;

    for(;;){
        CurrentTime = OSMemGet(MEMPointer,&err);      //申请内存空间
        if(err == OS_ERR_NONE){
            RTCDisBuf = (NUM_DisBuf *)(CurrentTime + sizeof(TimeDat));
            
            RTC_GetTime(CurrentTime);

            NUM_TimeDatToDisBuf(CurrentTime,RTCDisBuf);
     
            RTCDisBuf->Offset                  = 0;
            RTCDisBuf->DisN                    = 10;
            RTCDisBuf->DisControl.Place.X      = 700;
            RTCDisBuf->DisControl.Place.Y      = 16;
            RTCDisBuf->DisControl.WordColor    = HELIOTROPE;
            RTCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR;
            
            OSMboxPost(LCDNumDisBox,RTCDisBuf);         //发送消息邮箱内容是显示年月日
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号

            RTCDisBuf->Offset                  = 10;
            RTCDisBuf->DisN                    = 8;
            RTCDisBuf->DisControl.Place.X      = 710;
            RTCDisBuf->DisControl.Place.Y      = 32;
            RTCDisBuf->DisControl.WordColor    = HELIOTROPE;
            RTCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR;

            OSMboxPost(LCDNumDisBox,RTCDisBuf);         //发送消息邮箱内容是显示时分秒
            OSSemPend(LCDNumDisOverSemp,0,&err);        //等待LCD数字显示完成信号
            
            MEM_Set((Uint8 *)CurrentTime,0,PARTITION_LENGTH);        //内存清零
            err = OSMemPut(MEMPointer,CurrentTime);                  //释放内存            
        }
        OSTimeDlyHMSM(0,0,1,0); 
    }
}






