#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"

int main()
{
    
  
    u16 len,x,t;
    
	delay_init();	 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);    //延时函数初始化	  
    pwm_init_2(0,8999,100);//频率不能太高

    while(1)
    {
        if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的值为:\r\n\r\n");
            x=0;
			for(t=0;t<len;t++)
			{
				x+=(USART_RX_BUF[t]-'0')*pow0(len,t);
			}
            printf("\n\r%d",x);
            TIM_SetCompare2(TIM3,x);
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
        }
        
    } 
}

