/*
*************************************************************************************
**文件说明：系统配置文件
**文件名称： sys_about.c 
**创建日期：2013.09.08  
**创 建 人：王玮
**-----------------------------------------------------------------------------------
**修改日期：2013.xx.xx
**修改说明：
*************************************************************************************
*/
#include "user_cfg.h"
#include "drivers.h"
#include "memory.h"
#include "lcd_tft.h"

/*
*************************************************************************************
* 名    称：void SysTickConfig(void)
* 功    能：ucosii系统时钟节拍配置
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void SysTickConfig(void)
{
#ifdef OS_CRITICAL_METHOD  //如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
    Uint32 reload;
#endif
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //SYSTICK时钟源        
#ifdef OS_TICKS_PER_SEC                                   //如果时钟节拍数定义了,说明要使用ucosII了.
    reload = SystemCoreClock  / OS_TICKS_PER_SEC;         //根据OS_TICKS_PER_SEC设定溢出时间                  
    SysTick_Config(reload);                               //reload为24位寄存器,最大值:16777216,在72M下,约合1.86s左右
#endif
}

/*
*************************************************************************************
* 名    称：void IWDG_Init(void)
* 功    能：独立看门狗初始化使能
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);   //使能IWDG_PR 和IWDG_RLR 的写操作 
	IWDG_SetPrescaler(IWDG_Prescaler_32);           //设置IWDG 预分频值 
	IWDG_SetReload((40 * 1000 / 32)* 3);            //设置IWDG 重装载值 
	IWDG_ReloadCounter();                           //重装载IWDG 计数器 
	IWDG_Enable();                                  //使能IWDG 
}

/*
*************************************************************************************
* 名    称：void SysInit(void)
* 功    能：硬件初始化
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void SysInit(void)
{   
    SystemInit();          //系统时钟配置
    LCD_Init();            //LCD初始化
    RTC_Prepare();         //RTC初始化     
    SPI2_Config();         //SPI2配置
    ADC1_Config();         //ADC1配置    
    KEY_Config();          //键盘配置
  
//    IWDG_Init();           //开启看门狗
    
    SysTickConfig();       //ucos系统时钟配置
    
    NVIC_Configuration();  //中断配置
}

