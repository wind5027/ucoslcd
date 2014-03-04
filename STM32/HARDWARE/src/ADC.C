

#include "adc.h"


__IO u16 ADC1_ConvertValue[6] = {0};
/******************************************************************************************************************
*   名    称：void ADC_GPIO_Config(void)
*   功    能：六路ADC通路IO口配置函数
*   入口参数：无
*   出口参数：无
*   说    明：
*******************************************************************************************************************/
void ADC_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
/******************************************************************************************************************
*   名    称：void ADC_DMA_Config(void)
*   功    能：ADC的DMA传输功能配置函数
*   入口参数：无
*   出口参数：无
*   说    明：
*******************************************************************************************************************/
void ADC_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//使能DMA时钟

	DMA_DeInit(DMA1_Channel1);//复位DMA1通道1
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//设置外部设备基地址    ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC1_ConvertValue;//设置内存地址
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//源地址每次传输完成后不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//目的地内存地址每次传输完成后自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//源数据大小为半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//目的地数据大小为半字
	DMA_InitStructure.DMA_BufferSize = 6;//DMA传送数据块大小~6个
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//数据方向 由AD到内存
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA循环传送
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA 优先级--高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//DMA内存到内存关闭
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

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

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立ADC模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不选用外部触发
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//采用扫描模式（用于多通道AD信号采集）
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据存放采用右靠齐
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//开启连续转换	
	ADC_InitStructure.ADC_NbrOfChannel = 6;//需要转换的通道数  6个通道
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
    
	ADC_DMACmd(ADC1,ENABLE);//使能ADC1~DMA
	ADC_Cmd(ADC1,ENABLE);//使能ADC1
	ADC_ResetCalibration(ADC1);//复位ADC校准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位完成
	ADC_StartCalibration(ADC1);//开启ADC校准
	while(ADC_GetCalibrationStatus(ADC1));//等待ADC校准完成
	//通过软件开启ADC转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
/******************************************************************************************************************
*   名    称：void ADC_Config(void)
*   功    能：ADC配置函数
*   入口参数：无
*   出口参数：无
*   说    明：
*******************************************************************************************************************/
void ADC_Config(void)
{
    ADC_GPIO_Config();
    ADC_DMA_Config();
    ADC_MODE_Config();
    ADC_Clock_Config();
}


