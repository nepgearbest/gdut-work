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
    u16 Kp=5;
    u16 Ki=100;
    u16 Kd=10;
    u16 lasterror=0;
    u16 preerror=0;
    u16 result=0;
    u16 setpoint=0;
   /*
  pid参数通过蓝牙发送接受来控制 
  */
 /*使用增量式pid*/
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
/*pid初始化*/
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