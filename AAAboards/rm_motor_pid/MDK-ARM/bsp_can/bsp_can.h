#ifndef __bsp_can_H
#define __bsp_can_H
typedef struct{
    uint16_t ecd;
    int16_t speed_rpm;
    int16_t given_current;
    uint8_t temperate;
    int16_t last_ecd;
} motor_measure_t;
void can_filter_init(void);
void CAN_Send_Data(CAN_HandleTypeDef *hcan, int a);
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan);
extern motor_measure_t  motor_chassis[7];
#endif
