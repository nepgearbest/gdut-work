#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
int main()
{

	delay_init();	    	 //��ʱ������ʼ��	  
    pwm_init(899,0);
    TIM_SetCompare1(TIM1,0);
} 

