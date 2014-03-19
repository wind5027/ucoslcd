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
#include "sin.c"

/***************************************************
任务堆栈
****************************************************/
OS_STK  TASK_RTC_DIS_UPDATE_STK[RTC_STK_SIZE];

TimeDat    * CurrentTime;
NUM_DisBuf * RTCDisBuf;
WordDisBuf * WordDisCP;
CoordinateDisDat * CordDat;
CoordinateDat CDat;
ChartDat CharDat;
Uint16 TmpBuf[1024];
/***************************************************
说明：RTC更新任务
****************************************************/
void TaskRTCUpdate(void *pdata)
{
    Uint8 err;

//    Uint32 tmp;   
//    tmp = 0;  
//    PD1->Buf[0] = 0;
//    for(PD1->Buf[0] = 0; PD1->Buf[0] < 100;PD1->Buf[0] ++){
//        PD1->Buf[PD1->Buf[0]] = PD1->Buf[0];
//        TmpBuf[PD1->Buf[0]] = 0;
//    }
    
    CDat.YMaxDat  = 100;
    CDat.XMaxDat  = 4096;
    CharDat.CDatP = &CDat;
    CharDat.Color = GREEN;
    CharDat.DatSize = 4096;
    CharDat.DatBuf = SinDat;
    CharDat.DisP   = TmpBuf;
    for(;;){
        CurrentTime = OSMemGet(MEMPointer,&err);      //申请内存空间
        if(err == 0)//OS_NO_ERR)
            {
            RTCDisBuf = (NUM_DisBuf *)(CurrentTime + sizeof(TimeDat));
            WordDisCP = (WordDisBuf *)(CurrentTime + sizeof(TimeDat) + sizeof(NUM_DisBuf));
            CordDat   = (CoordinateDisDat *)(CurrentTime + sizeof(TimeDat) + sizeof(NUM_DisBuf) + sizeof(WordDisBuf));
            CordDat->CDatP = &CDat;
            CordDat->CoorDisP = RTCDisBuf;
            
            RTC_GetTime(CurrentTime);
 


//            if((CurrentTime->Second) % ){
                //OSTaskResume(LED2_TASK_Prio);

//                WordDisCP->WordSize                = WORD_24_24;
//                WordDisCP->DisN                    = 10;
//                WordDisCP->DisBuf                  = W_HGYBJDZYJY;
//                WordDisCP->DisControl.Place.X      = 200;
//                WordDisCP->DisControl.Place.Y      = 200;
//                WordDisCP->DisControl.WordColor    = HELIOTROPE;
//                WordDisCP->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR;
//                LCD_WriteWord(WordDisCP);
//                
//                WordDisCP->WordSize                = WORD_40_40;
//                WordDisCP->DisN                    = 4;
//                WordDisCP->DisBuf                  = W_ZKJG;
//                WordDisCP->DisControl.Place.X      = 200;
//                WordDisCP->DisControl.Place.Y      = 300;
//                WordDisCP->DisControl.WordColor    = HELIOTROPE;
//                WordDisCP->DisControl.BackgrdColor = LCD_BACKGROUND_COLOR;
//                LCD_WriteWord(WordDisCP);

//            CordDat->CDatP->YMaxDat  = tmp;

            CordDat->CDatP->Origin.X = 4;
            CordDat->CDatP->Origin.Y = 4;
            CordDat->CDatP->YPixel   = 410;
            CordDat->CDatP->XPixel   = 693;
            
            CDat.XMaxDat = 200;
            
            //CordDat->YMaxDat  = 400;
            //CordDat->XMaxDat  = 683;
            CordDat->PosColor = RED;
            LCD_DrawCoordinate(CordDat);
            
            if(LCD_DrawChart(&CharDat) == LCD_ERROR_COVER) {
                CDat.YMaxDat = CDat.YMaxDat + 100;
            }


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
            
            
                
            MEM_Set((Uint8 *)TmpBuf,0,200);
            
            OSMutexPost(FSMCMutex);            //释放FSMC互斥信号量
            
            MEM_Set((Uint8 *)CurrentTime,0,PARTITION_LENGTH);        //内存清零
            err = OSMemPut(MEMPointer,CurrentTime);                  //释放内存            
        }
        OSTimeDlyHMSM(0,0,0,30); 
    }
}






