#include "control.h"


/*
	pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd*[e(k)-e(k-1)*2+e(k-2)]
	float Velocity_KP=50,Velocity_KI=20,Velocity_KD=10;      //60°PID系数,放大100倍
	
	函数功能：增量式PID控制器
	入口参数：风板上的现在AD值，风板上的目标AD值
	返回  值：风扇PWM
	根据增量式离散PID公式 
	pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd*[e(k)-e(k-1)*2+e(k-2)]
	e(k)代表本次偏差 
	e(k-1)代表上一次的偏差  
	e(k-2)代表上上一次的偏差
	∑e(k)代表e(k)以及之前的偏差的累积和;
	pwm代表输出
*/



uint16_t Incremental_PID (uint16_t AD_Now,uint16_t AD_Target)
{ 	
	 static float Bias=0,Pwm=0,Last_bias=0,Last_Last_bias=0;
	
	 Last_Last_bias=Last_bias;							     //保存上上一次偏差
	 Last_bias=Bias;	                                     //保存上一次偏差 	
	 Bias=AD_Target-AD_Now;                                  //计算偏差
	
	 Pwm += Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias+Velocity_KD*(Bias-2*Last_bias+Last_Last_bias);   //增量式PID控制器
	 
	 //Pwm_last=Pwm;											//记录现输出
	if(Pwm>650)	{Pwm = 400;Bias=AD_Target-AD_Now;}
	 
	return Pwm;                                           
}




/**************************************************************************
	函数功能：位置式PID控制器
	入口参数：风板上的现在AD值，风板上的目标AD值
	返回  值：风扇PWM
	根据位置式离散PID公式 
	pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
	e(k)代表本次偏差 
	e(k-1)代表上一次的偏差  
	∑e(k)代表e(k)以及之前的偏差的累积和;
	pwm代表输出
**************************************************************************/


uint16_t Position_PID (int AD_Now,int AD_Target)			//风板上的AD值，风板角度
{ 	
	//本次偏差，pwm，总偏差，上一次偏差
	 static float Bias,Pwm,Integral_bias,Last_Bias;				

	 Bias=AD_Now-AD_Target;                                  //计算偏差

	 Integral_bias+=Bias;	                                 //求出偏差的积分

	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器

	 Last_Bias=Bias;                                       //保存上一次偏差 

	 return Pwm;                                           //增量输出
}









