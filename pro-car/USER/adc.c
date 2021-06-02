#include "adc.h"

u32 adc_value[3];

void adc_init()
{
    GPIO_InitTypeDef gpio_initure;
    DMA_InitTypeDef dma_initure;
    ADC_InitTypeDef adc_initure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    gpio_initure.GPIO_Mode=GPIO_Mode_AIN;
    gpio_initure.GPIO_Speed=GPIO_Speed_50MHz;
    gpio_initure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
    GPIO_Init(GPIOC,&gpio_initure);

    DMA_DeInit(DMA1);

    dma_initure.DMA_PeripheralBaseAddr=(u32) (&(ADC1->DR));
    dma_initure.DMA_MemoryBaseAddr=(u32) &adc_value;
    dma_initure.DMA_DIR=DMA_DIR_PeripheralSRC;
    dma_initure.DMA_BufferSize=3;
    dma_initure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
    dma_initure.DMA_MemoryInc=DMA_MemoryInc_Enable;
    dma_initure.DMA_M2M=DMA_M2M_Disable;
    dma_initure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
    dma_initure.DMA_Mode=DMA_Mode_Circular;
    dma_initure.DMA_Priority=DMA_Priority_High;
    dma_initure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;

    DMA_Init(DMA1,&dma_initure);
    DMA_Cmd(DMA1_Channel1,ENABLE);

    adc_initure.ADC_Mode=ADC_Mode_Independent;
    adc_initure.ADC_ScanConvMode=ENABLE;
    adc_initure.ADC_ContinuousConvMode=ENABLE;
    adc_initure.ADC_DataAlign=ADC_DataAlign_Right;
    adc_initure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
    adc_initure.ADC_NbrOfChannel=3;
    
    ADC_Init(ADC1,&adc_initure);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_12,1,ADC_SampleTime_55Cycles5);

    ADC_DMACmd(ADC1,ENABLE);
    ADC_Cmd(ADC1,ENABLE);
    
    ADC_ResetCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}