/*
*************************************************************************************
**文件说明：中断配置
**文件名称：isr_cfg.c 
**创建日期：2014.03.23  
**创 建 人：ww
**-----------------------------------------------------------------------------------
**修改日期：2014.xx.xx
**修改说明：
*************************************************************************************
*/
#include "isr_cfg.h"

/*
*************************************************************************************
* 名    称：void NVIC_Configuration(void)
* 功    能：NVIC中断设置
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级    

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn ;   //指定中断源  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         // 指定响应优先级别1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn ;   //指定中断源
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         // 指定响应优先级别1
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn ;   //指定中断源
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         // 指定响应优先级别1
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn ;   //指定中断源
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;         // 指定响应优先级别1
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn ;   //指定中断源
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;         // 指定响应优先级别1
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn ;   //指定中断源
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;         // 指定响应优先级别1
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

}



/*
*************************************************************************************
* 名    称：void EXTI_Configuration(void) 
* 功    能：外部中断设置
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void EXTI_Configuration(void) 
{     
    EXTI_InitTypeDef EXTI_InitStructure;
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);   //选择 GPIO管脚用作外部中断线路 
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);   //选择 GPIO管脚用作外部中断线路
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);   //选择 GPIO管脚用作外部中断线路
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5);   //选择 GPIO管脚用作外部中断线路
    
    EXTI_InitStructure.EXTI_Line    = EXTI_Line2 | EXTI_Line3 
                                    | EXTI_Line4 | EXTI_Line5;    //外部中断线     
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;        //中断模式     
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;       //中断触发方式     
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //打开中断     
    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearITPendingBit(EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5);	
} 















