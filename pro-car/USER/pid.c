#include "pid.h"
/*
    Ϊ���ٸ�������ʹ�ã��ذ�ϵ��ȫ������100
*/
/*
    KpΪ����ϵ����KiΪ����ϵ����KdΪ΢��ϵ��,����ʽpid�㷨
*/
/*
��ѧ��ʽ�������

*/
    u16 Kp=5;
    u16 Ki=100;
    u16 Kd=10;
    u16 lasterror=0;
    u16 preerror=0;
    u16 result=0;
    u16 setpoint=0;
   /*
  pid����ͨ���������ͽ��������� 
  */
 /*ʹ������ʽpid*/
  void start_pid(u16 processValue)
{
    u16 thisError;
    u16 increment;
    u16 pError,dError,iError;
    thisError=setpoint-processValue;
    pError=thisError-lasterror;
    dError=thisError-2*lasterror+preerror;
    iError=thisError;
    increment=Kp*pError+Ki*dError+Kd*dError;
    preerror=lasterror;
    lasterror=thisError;
    result+=increment;
}
/*pid��ʼ��*/
void pid_DeInit(void)
{
    Kp=0;
    Ki=0;
    Kd=0;
    lasterror=0;
    preerror=0;
    result=0;
    setpoint=0;
}