/*
*************************************************************************************
**文件说明：adc配置
**文件名称：adc_cfg.c 
**创建日期：2014.03.20  
**创 建 人：ww
**-----------------------------------------------------------------------------------
**修改日期：2014.xx.xx
**修改说明：
*************************************************************************************
*/
#include "adc_cfg.h"




/******************************************************************************************************************
*   名    称：void ADC_MODE_Config(void)
*   功    能：ADC模式配置函数
*   入口参数：无
*   出口参数：无
*   说    明：
*******************************************************************************************************************/
void ADC_MODE_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;      //独立ADC模式
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; //不选用外部触发
	ADC_InitStructure.ADC_ScanConvMode       = ENABLE;                    //采用扫描模式（用于多通道AD信号采集）
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;       //数据存放采用右靠齐
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                    //开启连续转换	
	ADC_InitStructure.ADC_NbrOfChannel       = 6;                         //需要转换的通道数  6个通道
	ADC_Init(ADC1,&ADC_InitStructure);
}
/******************************************************************************************************************
*   名    称：void ADC_Clock_Config(void)
*   功    能：ADC时钟配置函数
*   入口参数：无
*   出口参数：无
*   说    明：
*******************************************************************************************************************/
void ADC_Clock_Config(void)
{	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//PCLK2是72MHz,ADC的最高输入时钟为14MHZ，所以72/6=12
	//选择ADC1，通道0，转换序号1,28.5个采样周期,(28.5+12.5)*1/12=3.4us
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_28Cycles5);
	//选择ADC1，通道1，转换序号2,28.5个采样周期,(28.5+12.5)*1/12=3.4us
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_28Cycles5);
    //选择ADC1，通道2，转换序号3,28.5个采样周期,(28.5+12.5)*1/12=3.4us
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_28Cycles5);
    //选择ADC1，通道3，转换序号4,28.5个采样周期,(28.5+12.5)*1/12=3.4us
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_28Cycles5);
    //选择ADC1，通道4，转换序号5,28.5个采样周期,(28.5+12.5)*1/12=3.4us
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5,ADC_SampleTime_28Cycles5);
    //选择ADC1，通道5，转换序号6,28.5个采样周期,(28.5+12.5)*1/12=3.4us
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,6,ADC_SampleTime_28Cycles5);
    
	ADC_DMACmd(ADC1,ENABLE);                   //使能ADC1~DMA
	ADC_Cmd(ADC1,ENABLE);                      //使能ADC1
    
	ADC_ResetCalibration(ADC1);                //复位ADC校准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位完成
    
	ADC_StartCalibration(ADC1);                //开启ADC校准
	while(ADC_GetCalibrationStatus(ADC1));     //等待ADC校准完成
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);     //通过软件开启ADC转换
}



/*
*************************************************************************************
* 名    称：void ADC1_Config(void)
* 功    能：ADC1配置
* 入口参数：无
* 出口参数：无
*************************************************************************************
*/
void ADC1_Config(void)
{
    DMA_ControlDat  ControlDat;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);            //开启ADC1时钟
    
    ControlDat.DMA_PeripheralBaseAddr = (Uint32)&ADC1->DR;         //ADC1->DR  外设地址
    ControlDat.DMA_MemoryBaseAddr     = (Uint32)ADC1ValueArray;    //存储器地址
    ControlDat.DMA_BufferSize         = 6;                         //DMA传输长度
    DMA_Config(&ControlDat,EN_DMA_ADC1);                           //配置DMA通道1 FSMC传输
    
    GPIO_Config(EN_GPIO_ADC1,0);                                   //配置ADC1管脚    ADC_MODE_Config();
    ADC_Clock_Config();    
}

