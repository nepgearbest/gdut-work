#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"

int main()
{
    
  
    u16 len,x,t;
    
	delay_init();	 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);    //��ʱ������ʼ��	  
    pwm_init_2(0,8999,100);//Ƶ�ʲ���̫��

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
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
        }
        
    } 
}

