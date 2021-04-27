#include "sys.h" 
#include "usart.h"
#include "pid.h"
//void pwm_init(u32 psc,u32 arr);//tim1 通道1
void pwm_init_2(u32 psc,u32 arr,u16 cmp);//tim3通道2
void speed_rpm_read(u16 *a);
u16 getTIMX_data(TIM_TypeDef *TIMx);
void tim_tick(u16 psc,u32 arr);//tim 5 ch1 pb6,5ms定时，arr=7200-1,psc
void pulse_encode(u32 psc);//tim2 ch1//pb 6 7
u16 pow0(u16 len,u16 t);
extern u16 speed;
