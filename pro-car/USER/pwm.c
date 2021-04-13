
#include "pwm.h"

void pwm_init(u32 psc,u32 arr)
{
    GPIO_InitTypeDef gpio_initure;
    TIM_TimeBaseInitTypeDef tim_initure;
    TIM_OCInitTypeDef tim_ociniture;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    
    gpio_initure.GPIO_Mode=GPIO_Mode_AF_PP;
    gpio_initure.GPIO_Speed=GPIO_Speed_50MHz;
    gpio_initure.GPIO_Pin=GPIO_Pin_8;
    GPIO_Init(GPIOA,&gpio_initure);
    
    gpio_initure.GPIO_Pin=GPIO_Pin_13;
    GPIO_Init(GPIOB,&gpio_initure);
    
    tim_initure.TIM_ClockDivision=TIM_CKD_DIV1;
    tim_initure.TIM_CounterMode=TIM_CounterMode_Up;
    tim_initure.TIM_Period=arr;
    tim_initure.TIM_Prescaler=psc;
    TIM_TimeBaseInit(TIM1,&tim_initure);
    
    tim_ociniture.TIM_OCMode=TIM_OCMode_PWM1;
    tim_ociniture.TIM_OutputState=TIM_OutputState_Enable;
    tim_ociniture.TIM_OutputNState=TIM_OutputNState_Enable;
    tim_ociniture.TIM_Pulse=4;
    tim_ociniture.TIM_OCPolarity=TIM_OCPolarity_High;
    tim_ociniture.TIM_OCNPolarity=TIM_OCNPolarity_Low;
    tim_ociniture.TIM_OCIdleState=TIM_OCIdleState_Set;
    tim_ociniture.TIM_OCNIdleState=TIM_OCNIdleState_Reset;

    TIM_OC1Init(TIM1,&tim_ociniture);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
    TIM_Cmd(TIM1,ENABLE);
    
}
