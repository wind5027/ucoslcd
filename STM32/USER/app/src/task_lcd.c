/*
*************************************************************************************
**文件说明：LCD操作任务
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

Uint8 * p;
/***************************************************
说明：LCD背景更新任务
****************************************************/
void TaskLCDBrgUpdate(void *pdata)
{
    Uint8 err;

    for(;;){
        p = OSMemGet(MEMPointer,&err);      //申请内存空间
        if(err == OS_ERR_NONE){          
            MEM_Set((Uint8 *)p,0,PARTITION_LENGTH);        //内存清零
            err = OSMemPut(MEMPointer,p);                  //释放内存            
        }
        
        LCD_SetBkgrdSpiOfDma(0);
        OSSemPend(DMAC4OverSemp,0,&err);                   //等待DMA通道4传输完成信号
        OSTimeDlyHMSM(0,0,0,500); 
    }
}













