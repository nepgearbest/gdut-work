#include "pid.h"
/*
    为减少浮点数的使用，特把系数全部乘以100
*/
/*
    Kp为比例系数，Ki为积分系数，Kd为微分系数,增量式pid算法
*/
/*
数学公式放在这里：

*/
    float Kp=0.05;
    float Ki=0.01;
    float Kd=0.07;
    float lasterror=0;
    float preerror=0;
    float result=0;
    float setpofloat=0;
   /*
  pid参数通过蓝牙发送接受来控制 
  */
 /*使用增量式pid*/
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
/*pid初始化*/
void pid_DeInit(float a,float b)
{
    lasterror=0;
    preerror=0;
    result=0;
    setpofloat=a;
    result=b;
}