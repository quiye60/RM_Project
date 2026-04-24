#include "main.h"                
#include "PID.h"
#include <math.h>

void PID_Update(PID_t *hpid)
{

	
	
	/*获取本次误差和上次误差*/
	hpid->Error1 = hpid->Error0;					//获取上次误差
	hpid->Error0 = hpid->Target - hpid->Actual;		//获取本次误差
	
	if(hpid->DeadZone&&
	fabs(hpid->Error0)<hpid->DeadZone){hpid->Actualfront=hpid->Actual;return;}		//死区代码

	if (hpid->Ki != 0	&&	fabs(hpid->ErrorInt)<hpid->IntSep)					//如果Ki不为0且积分未分离
	{
		hpid->ErrorInt += hpid->Error0;	//进行误差积分
		if (hpid->ErrorInt > hpid->IntMax) {hpid->ErrorInt = hpid->IntMax;}		
		if (hpid->ErrorInt <-hpid->IntMax) {hpid->ErrorInt =-hpid->IntMax;}		//积分限幅
		
	}
	else							
	{
		hpid->ErrorInt = 0;			
	}
	
	

	
	if(hpid->DifFront)	//微分先行
	{
		
		hpid->Out = hpid->Kp * hpid->Error0
			   + hpid->Ki * hpid->ErrorInt
			   + (1-hpid->DifFliter)*(hpid->Kd * (hpid->Actual - hpid->Actualfront)) + hpid->DifFliter  *  hpid->Actualfront;

	
	}else				//微分不先行
	{
		hpid->Out = hpid->Kp * hpid->Error0
			   + hpid->Ki * hpid->ErrorInt
			   + (1-hpid->DifFliter) * (hpid->Kd * (hpid->Error0 - hpid->Error1)) + hpid->DifFliter * hpid->Error1;
	}	
	
	

	if (hpid->Out > hpid->OutMax) {hpid->Out = hpid->OutMax;}	
	if (hpid->Out < hpid->OutMin) {hpid->Out = hpid->OutMin;}	//输出限幅


	hpid->Actualfront=hpid->Actual;								
	
}
