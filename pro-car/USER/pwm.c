
#include "pwm.h"
u16 speed=0;
/*
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
    
}*/
void pwm_init_2(u32 psc,u32 arr,u16 cmp)//tim3通道2
{
    GPIO_InitTypeDef gpio_initure;
    TIM_TimeBaseInitTypeDef tim_initure;
    TIM_OCInitTypeDef tim_ociniture;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    tim_initure.TIM_ClockDivision=TIM_CKD_DIV1;
    tim_initure.TIM_CounterMode=TIM_CounterMode_Up;
    tim_initure.TIM_Period=arr;
    tim_initure.TIM_Prescaler=psc;
    TIM_TimeBaseInit(TIM3,&tim_initure);
    
    gpio_initure.GPIO_Mode=GPIO_Mode_AF_PP;
    gpio_initure.GPIO_Speed=GPIO_Speed_50MHz;
    gpio_initure.GPIO_Pin=GPIO_Pin_7;
    GPIO_Init(GPIOA,&gpio_initure);
    

    tim_ociniture.TIM_OCMode=TIM_OCMode_PWM2;
    tim_ociniture.TIM_OutputState=TIM_OutputState_Enable;
    tim_ociniture.TIM_Pulse=cmp;
    tim_ociniture.TIM_OCPolarity=TIM_OCPolarity_High;
    tim_ociniture.TIM_OCIdleState=TIM_OCIdleState_Set;

    TIM_OC2Init(TIM3,&tim_ociniture);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
    TIM_Cmd(TIM3,ENABLE);
}
void pulse_encode(u32 psc)//tim2 ch1
{
     GPIO_InitTypeDef gpio_initure;
    TIM_TimeBaseInitTypeDef tim_initure;
    TIM_ICInitTypeDef tim_iciniture;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    tim_initure.TIM_ClockDivision=TIM_CKD_DIV1;
    tim_initure.TIM_CounterMode=TIM_CounterMode_Up;
    tim_initure.TIM_Period=65535;
    tim_initure.TIM_Prescaler=psc;
    TIM_TimeBaseInit(TIM2,&tim_initure);
    
        gpio_initure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    gpio_initure.GPIO_Speed=GPIO_Speed_50MHz;
    gpio_initure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_Init(GPIOA,&gpio_initure);
    
    TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    tim_iciniture.TIM_ICFilter=10;
    TIM_ICInit(TIM5,&tim_iciniture);
    TIM_SetCounter(TIM2,0x7fff);
    TIM_ClearFlag(TIM2,TIM_IT_Update);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2,ENABLE);
    TIM2->CNT=0x7fff;
}
void tim_tick(u16 psc,u32 arr)//tim 5 ch1 pb6,5ms定时，arr=7200-1,psc
{
    GPIO_InitTypeDef gpio_initure;
    TIM_TimeBaseInitTypeDef tim_initure;
    TIM_OCInitTypeDef tim_ociniture;
    NVIC_InitTypeDef nvic_initure;
    
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
    
    //gpio_initure.GPIO_Mode=GPIO_Mode_AF_PP;
    //gpio_initure.GPIO_Speed=GPIO_Speed_50MHz;
    //gpio_initure.GPIO_Pin=GPIO_Pin_6;
   // GPIO_Init(GPIOB,&gpio_initure);
    
    
    tim_initure.TIM_ClockDivision=TIM_CKD_DIV1;
    tim_initure.TIM_CounterMode=TIM_CounterMode_Up;
    tim_initure.TIM_Period=arr;
    tim_initure.TIM_Prescaler=psc;
    TIM_TimeBaseInit(TIM5,&tim_initure);
    TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
    
    nvic_initure.NVIC_IRQChannel=TIM5_IRQn;
    nvic_initure.NVIC_IRQChannelCmd=ENABLE;
    nvic_initure.NVIC_IRQChannelSubPriority=3;
    nvic_initure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_Init(&nvic_initure);
    
    TIM_Cmd(TIM5,ENABLE);
}
void TIM5_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
    {
        
        printf("speed is %d",speed);
        speed_rpm_read(&speed);
        start_pid(speed);
        TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
    }
}
u16 getTIMX_data(TIM_TypeDef *TIMx)
{
    u16 cnt;
    cnt=TIMx->CNT-0x7fff;
    TIMx->CNT=0x7fff;
    return cnt;
}
void speed_rpm_read(u16 *a)
{
    *a=getTIMX_data(TIM2);
}
u16 pow0(u16 len,u16 t)
{
    u16 i=0,res=1,h;
    h=len-t-1;
    for(i=0;i<h;i++)
    {
        res*=10;
    }
    return res;
}