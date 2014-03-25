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


#include "drivers.h"
#include "task.h"
#include "lcd_tft.h"
#include "memory.h"
#include "word.h"



/***************************************************
任务代码
****************************************************/
#include "task_rtc.c"#include "task_lcd.c"
#include "task_adc.c"
//#include "task_key.c"



/***************************************************
任务堆栈
****************************************************/
OS_STK  TASK_START_STK[START_STK_SIZE];                  //开始任务堆栈



/***************************************************
任务堆栈
****************************************************/
OS_STK  TASK_RTC_DIS_UPDATE_STK[RTC_STK_SIZE];            //RTC更新任务堆栈
OS_STK  TASK_LCD_BKRG_UPDATE_STK[LCD_STK_SIZE];           //LCD背景更新任务堆栈
OS_STK  TASK_NUM_DIS_STK[LCD_STK_SIZE];                   //LCD数字显示任务堆栈OS_STK  TASK_GET_VOLT_STK[GET_VOLT_STK_SIZE];             //ADC电压获取任务堆栈



/***************************************************
开始任务
****************************************************/
void TaskStart(void * pdata)
{
    Uint8 err;
    pdata = pdata;
    
    MEMPointer        = OSMemCreate(MEMPartition,PARTITION_NUM,PARTITION_LENGTH,&err); //创建内存分区
    FSMCMutex         = OSMutexCreate(2,&err);   //创建FSMC互斥型信号量
    DMAC4OverSemp     = OSSemCreate(0);          //创建DMA通道4传输完成信号量 
    LCDNumDisOverSemp = OSSemCreate(0);          //创建LCD数字显示完成信号量
    LCDNumDisBox      = OSMboxCreate((void *)0); //LCD数字显示消息邮箱


    
    OS_ENTER_CRITICAL();                    //进入临界区

    OSTaskCreate(TaskLCDNumDis, (void * )0,                           //创建LCD数字显示任务
                 (OS_STK *)&TASK_NUM_DIS_STK[LCD_STK_SIZE-1], 
                 NUM_DIS_TASK_PRIO);   
    OSTaskCreate(TaskLCDBrgUpdate, (void * )0,                        //创建背景图片更新任务 
                 (OS_STK *)&TASK_LCD_BKRG_UPDATE_STK[LCD_STK_SIZE-1], 
                 LCD_BRG_TASK_PRIO);
    OSTaskCreate(TaskGetADCVolt, (void * )0,                          //创建ADC 电压值获取任务 
                 (OS_STK *)&TASK_GET_VOLT_STK[GET_VOLT_STK_SIZE-1], 
                 GET_VOLT_TASK_PRIO);
//    OSTaskCreate(TaskRTCUpdate, (void * )0,                           //创建RTC更新任务 
//                 (OS_STK *)&TASK_RTC_DIS_UPDATE_STK[RTC_STK_SIZE-1], 
//                 RTC_TASK_PRIO);
                 
    OS_EXIT_CRITICAL();                     //退出临界区
    
    OSTaskDel(OS_PRIO_SELF);                //开始任务完成，删除自身。
}






