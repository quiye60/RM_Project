#include "stm32f4xx.h"                  // Device header
#include "pid.h"
#include "math.h"
#include <stdio.h>

Simple_PID motor_speed = {0};
Simple_PID motor_pos ={0};

/**
 * @brief  初始化PID
 * @param  kp, ki, kd: PID参数
 * @param  min_int, max_int: 积分限幅范围
 * @param  min_out, max_out: 输出电压范围
 */

void PID_Init(Simple_PID*pid,float kp, float ki, float kd, float min_int, float max_int, float min_out, float max_out) 
	{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->integral_min = min_int;
    pid->integral_max = max_int;
    pid->output_min = min_out;
    pid->output_max = max_out;
    pid->last_error = 0;
    pid->integral = 0;
	pid->setpoint = 0;	
}

/**
 * @brief  PID计算 - 输入当前转速，输出控制电压
 * @param  current_speed: 当前转速反馈值
 * @retval 控制电压输出
 */
float PID_Calculate(Simple_PID*pid,float target,float current_speed) 
	{
		
	pid->setpoint = target;
    float error = target - current_speed;
    
    // 积分项累加
    pid->integral += error;
    
    // 积分限幅
    if (pid->integral > pid->integral_max) {
        pid->integral = pid->integral_max;
    } else if (pid->integral < pid->integral_min) {
        pid->integral = pid->integral_min;
    }
    
    // 微分项
    float derivative = error - pid->last_error;
    
    // PID公式
    float output = pid->Kp * error + 
                   pid->Ki * pid->integral + 
                   pid->Kd * derivative;
    
    // 输出限幅
    if (output > pid->output_max) output = pid->output_max;
    if (output < pid->output_min) output = pid->output_min;
    
    pid->last_error = error;
    return output;
}



