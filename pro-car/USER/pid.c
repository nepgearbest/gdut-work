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
    float Kp=0.05;
    float Ki=0.01;
    float Kd=0.07;
    float lasterror=0;
    float preerror=0;
    float result=0;
    float setpofloat=0;
   /*
  pid����ͨ���������ͽ��������� 
  */
 /*ʹ������ʽpid*/
  void start_pid(float processValue)
{
    float thisError;
    float increment;
    float pError,dError,iError;
    thisError=setpofloat-processValue;
    pError=thisError-lasterror;
    dError=thisError-2*lasterror+preerror;
    iError=thisError;
    increment=Kp*pError+Ki*iError+Kd*dError;
    preerror=lasterror;
    lasterror=thisError;
    result+=increment;
    printf("resudlt:%f %f\n\r",result,setpofloat);
    TIM_SetCompare2(TIM3,-result);
}
/*pid��ʼ��*/
void pid_DeInit(float a,float b)
{
    lasterror=0;
    preerror=0;
    result=0;
    setpofloat=a;
    result=b;
}