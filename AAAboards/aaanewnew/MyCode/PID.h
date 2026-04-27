#ifndef PID_H
#define PID_H

typedef struct {
	//内部参数
	float Target;
	float Actual;
	float Actual_front;		//上次实际值
	float Out;			
	float Error0;			//本次误差
	float Error1;			//上次误差
	float ErrorInt;			//误差积分
	
	
	//PID参数
	float Kp;
	float Ki;
	float Kd;

	
	//PID改进算法
	float DeadZone;				//输入死区|x|
	float OutOffset;			//输出偏移|x|
	float OutMax;				//			+
	float OutMin;				//输出限幅	-

	float IntMax;				//积分限幅|x|
	float IntSep;				//积分分离|x|
	float DifFilter;			//不完全微分0无1完全


	uint8_t	DifFront;			//微分先行0无1启动



} PID_t;


void PID_Init(PID_t *PID);














void PID_Update(PID_t *hpid,float actual);

#endif
