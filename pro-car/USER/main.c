#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "pid.h"
int main()
{
    
  
    u16 len,x,t;
    extern u16 speed;
	delay_init();	 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);    //��ʱ������ʼ��	  
    pwm_init_2(0,8999,100);//Ƶ�ʲ���̫��
    pulse_encode(0);
    tim_tick(7200-1,10000);//72000000/7200/10000=1s
    pid_DeInit(2000,100);
    while(1)
    {
        if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵�ֵΪ:\r\n\r\n");
            x=0;
			for(t=0;t<len;t++)
			{
				x+=(USART_RX_BUF[t]-'0')*pow0(len,t);
			}
            printf("\n\r%d",x);
            TIM_SetCompare2(TIM3,x);
            printf("speed is %d",speed-32767);
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
        }
        
    } 
}

