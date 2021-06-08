#include "exti.h"
void key_init()
{
    GPIO_InitTypeDef gpio_initure;
    NVIC_InitTypeDef nvic_initure;
    EXTI_InitTypeDef exti_initure;
    gpio_initure.GPIO_Speed=GPIO_Speed_50MHz;
    gpio_initure.GPIO_Pin=GPIO_Pin_3;
    gpio_initure.GPIO_Mode=GPIO_Mode_IPU;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
    GPIO_Init(GPIOE,&gpio_initure);

    
    exti_initure.EXTI_Line=EXTI3_IRQn;
    exti_initure.EXTI_Mode=EXTI_Mode_Interrupt;
    exti_initure.EXTI_Trigger=EXTI_Trigger_Falling;
    exti_initure.EXTI_LineCmd=ENABLE;
    EXTI_Init(&exti_initure);

    
    nvic_initure.NVIC_IRQChannel=EXTI3_IRQn;
    nvic_initure.NVIC_IRQChannelPreemptionPriority=1;
    nvic_initure.NVIC_IRQChannelSubPriority=1;
    nvic_initure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&nvic_initure);
}
void EXTI3_IRQnHandler()
{
    if(EXTI_GetITStatus(EXTI3_IRQn)==RESET)
    {
        EXTI_ClearITPendingBit(EXTI3_IRQn);
    }
}