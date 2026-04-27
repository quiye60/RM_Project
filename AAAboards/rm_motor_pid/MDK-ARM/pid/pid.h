#ifndef __pid_H
#define __pid_H
typedef struct {
    float Kp;          // 比例系数
    float Ki;          // 积分系数
    float Kd;          // 微分系数
    float setpoint;    // 目标转速
    float last_error;  // 上一次误差
    float integral;    // 积分项
    float integral_min; // 积分最小值限制
    float integral_max; // 积分最大值限制
    float output_min;  // 输出最小值(电压)
    float output_max;  // 输出最大值(电压)
} Simple_PID;
void PID_Init(Simple_PID*pid,float kp, float ki, float kd, float min_int, float max_int, float min_out, float max_out);
float PID_Calculate(Simple_PID*pid,float target,float current_speed) ;

extern Simple_PID motor_speed;
extern Simple_PID motor_pos;
// PID控制器结构体
//typedef struct {
//float kp, ki, kd;           // 比例、积分、微分系数
//float prev_error;          // 上一次误差
//float integral;            // 积分累积
//float output_limit;        // 输出限幅
//} PID_Controller;

// 双环PID控制器结构体
//typedef struct {
//    PID_Controller position_pid;  // 位置环PID
//    PID_Controller velocity_pid;  // 速度环PID
//} DualLoopPID;
//void DualLoopPID_Init(DualLoopPID* dual_pid, float pos_kp, float pos_ki, float pos_kd,float vel_kp, float vel_ki, float vel_kd);
//float DualLoopPID_Update(DualLoopPID* dual_pid, float current_pos, float target_pos, float current_vel) ;
#endif
