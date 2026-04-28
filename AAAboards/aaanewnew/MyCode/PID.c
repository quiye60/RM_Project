#include "main.h"                
#include "PID.h"
#include <math.h>


PID_t pid_6020_speed;
PID_t pid_6020_location;









void PID_Update(PID_t *hpid,float actual)
{

	
	hpid->Actual=actual;
	/*获取本次误差和上次误差*/
	hpid->Error1 = hpid->Error0;					//获取上次误差
	hpid->Error0 = hpid->Target - hpid->Actual;		//获取本次误差
	
	if(hpid->DeadZone&&
	fabs(hpid->Error0)<hpid->DeadZone)
		{hpid->Actual_front=hpid->Actual;return;}		//死区代码

	if (hpid->Ki != 0	&&	fabs(hpid->Error0)>pid_6020_speed.IntSep)					//如果Ki不为0且积分未分离
	{
		hpid->ErrorInt += hpid->Error0;	//进行误差积分
		if (hpid->ErrorInt > hpid->IntMax) {hpid->ErrorInt = hpid->IntMax;}
		if (hpid->ErrorInt <-hpid->IntMax) {hpid->ErrorInt =-hpid->IntMax;}		//积分限幅
		
	}
	else								//否则积分项清零
	{
		hpid->ErrorInt = 0;			
	}

	
	if(hpid->DifFront)	//微分先行			//给实际值阻尼
	{
		
		hpid->Out = hpid->Kp   * hpid->Error0
					+ hpid->Ki * hpid->ErrorInt
					+ (1-hpid->DifFilter)	*(hpid->Kd * (hpid->Actual - hpid->Actual_front))
					+ hpid->DifFilter		* hpid->Actual_front;

	
	}else				//微分不先行			//给误差阻尼
	{
		hpid->Out =
					hpid->Kp * hpid->Error0
					+ hpid->Ki * hpid->ErrorInt
					+ (1-hpid->DifFilter)	* (hpid->Kd * (hpid->Error0 - hpid->Error1))
					+ hpid->DifFilter		* hpid->Error1;
	}	

//	if (hpid->Out > hpid->OutMax) {hpid->Out = hpid->OutMax;}
//	if (hpid->Out < hpid->OutMin) {hpid->Out = hpid->OutMin;}	//输出限幅




	hpid->Actual_front=hpid->Actual;
}




void PID_Init(PID_t *PID) {
	//内部参数
	PID->Target = 0;
	PID->Actual = 0;
	PID->Actual_front = 0;		//上次实际值
	PID->Out = 0;			
	PID->Error0 = 0;			//本次误差
	PID->Error1 = 0;			//上次误差
	PID->ErrorInt = 0;			//误差积分
	
	//PID改进算法
	PID->DeadZone = 0;				//输入死区|x|
	PID->OutOffset = 0;			//输出偏移|x|
	PID->OutMax = 0;				//			+
	PID->OutMin = 0;				//输出限幅	-

	PID->IntMax = 0;				//积分限幅|x|
	PID->IntSep = 0;				//积分分离|x|
	PID->DifFilter = 0;			//不完全微分0无1完全


	PID->DifFront = 0;			//微分先行0无1启动



	
	
	
}