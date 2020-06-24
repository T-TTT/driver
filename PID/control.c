#include "control.h"


/*
	pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd*[e(k)-e(k-1)*2+e(k-2)]
	float Velocity_KP=50,Velocity_KI=20,Velocity_KD=10;      //60��PIDϵ��,�Ŵ�100��
	
	�������ܣ�����ʽPID������
	��ڲ���������ϵ�����ADֵ������ϵ�Ŀ��ADֵ
	����  ֵ������PWM
	��������ʽ��ɢPID��ʽ 
	pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd*[e(k)-e(k-1)*2+e(k-2)]
	e(k)������ƫ�� 
	e(k-1)������һ�ε�ƫ��  
	e(k-2)��������һ�ε�ƫ��
	��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;
	pwm�������
*/



uint16_t Incremental_PID (uint16_t AD_Now,uint16_t AD_Target)
{ 	
	 static float Bias=0,Pwm=0,Last_bias=0,Last_Last_bias=0;
	
	 Last_Last_bias=Last_bias;							     //��������һ��ƫ��
	 Last_bias=Bias;	                                     //������һ��ƫ�� 	
	 Bias=AD_Target-AD_Now;                                  //����ƫ��
	
	 Pwm += Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias+Velocity_KD*(Bias-2*Last_bias+Last_Last_bias);   //����ʽPID������
	 
	 //Pwm_last=Pwm;											//��¼�����
	if(Pwm>650)	{Pwm = 400;Bias=AD_Target-AD_Now;}
	 
	return Pwm;                                           
}




/**************************************************************************
	�������ܣ�λ��ʽPID������
	��ڲ���������ϵ�����ADֵ������ϵ�Ŀ��ADֵ
	����  ֵ������PWM
	����λ��ʽ��ɢPID��ʽ 
	pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
	e(k)������ƫ�� 
	e(k-1)������һ�ε�ƫ��  
	��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;
	pwm�������
**************************************************************************/


uint16_t Position_PID (int AD_Now,int AD_Target)			//����ϵ�ADֵ�����Ƕ�
{ 	
	//����ƫ�pwm����ƫ���һ��ƫ��
	 static float Bias,Pwm,Integral_bias,Last_Bias;				

	 Bias=AD_Now-AD_Target;                                  //����ƫ��

	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���

	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������

	 Last_Bias=Bias;                                       //������һ��ƫ�� 

	 return Pwm;                                           //�������
}









