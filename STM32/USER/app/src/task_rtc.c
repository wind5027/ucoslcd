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


TimeDat    * CurrentTime;        //当前时间数据指针
NUM_DisBuf * RTCDisBuf;          //RTC 数字显示缓冲区指针

/***************************************************
说明：RTC更新任务
****************************************************/
void TaskRTCUpdate(void *pdata)
{
    Uint8 err;

    for(;;){
        CurrentTime = OSMemGet(MEMPointer,&err);      //申请内存空间
        if(err == OS_ERR_NONE)
            {
            RTCDisBuf = (NUM_DisBuf *)(CurrentTime + sizeof(TimeDat));
            
            RTC_GetTime(CurrentTime);

            NUM_TimeDatToDisBuf(CurrentTime,RTCDisBuf);
            
            OSMutexPend(FSMCMutex,0,&err);     //等待FSMC互斥信号量
            
            RTCDisBuf->Offset                  = 0;
            RTCDisBuf->DisN                    = 10;
            RTCDisBuf->DisControl.Place.X      = 720;
            RTCDisBuf->DisControl.Place.Y      = 16;
            RTCDisBuf->DisControl.WordColor    = HELIOTROPE;
            RTCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR;
            LCD_WriteNum(RTCDisBuf);           //使用FSMC 显示年月日

            RTCDisBuf->Offset                  = 10;
            RTCDisBuf->DisN                    = 8;
            RTCDisBuf->DisControl.Place.X      = 730;
            RTCDisBuf->DisControl.Place.Y      = 32;
            RTCDisBuf->DisControl.WordColor    = HELIOTROPE;
            RTCDisBuf->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR;
            LCD_WriteNum(RTCDisBuf);           //使用FSMC  显示时分秒
          
            OSMutexPost(FSMCMutex);            //释放FSMC互斥信号量
            
            MEM_Set((Uint8 *)CurrentTime,0,PARTITION_LENGTH);        //内存清零
            err = OSMemPut(MEMPointer,CurrentTime);                  //释放内存            
        }
        OSTimeDlyHMSM(0,0,0,100); 
    }
}






