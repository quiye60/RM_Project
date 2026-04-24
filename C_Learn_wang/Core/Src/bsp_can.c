#include "bsp_can.h"
#include "uart_basics.h"
GM6020_Info_t motor_yaw_info;											//自定义的电机信息结构体
uint16_t can_cnt;
volatile uint8_t motor_data_update_flag = 0; 



void can_filter_init(void) //筛选器配置
{
    CAN_FilterTypeDef can_filter_st;

    // 1. 关键：先把整个结构体清零，避免垃圾值导致参数错误
//    memset(&can_filter_st, 0, sizeof(can_filter_st));

    // 2. 配置第一个过滤器（FilterBank 0）
    can_filter_st.FilterActivation     = ENABLE;
    can_filter_st.FilterMode           = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale          = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh         = 0x0000;
    can_filter_st.FilterIdLow          = 0x0000;
    can_filter_st.FilterMaskIdHigh     = 0x0000;
    can_filter_st.FilterMaskIdLow      = 0x0000;
    can_filter_st.FilterBank           = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    can_filter_st.SlaveStartFilterBank = 14;  // 必须设置，否则报错

    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);

    // 3. 只需要调用一次！
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}
 
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
 /*   CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
	uart_printf("1");
    if (hcan->Instance == CAN1)
    {
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK)
        {
            switch (rx_header.StdId)
            {
                case 0x205: 
                {
                    motor_yaw_info.rotor_angle    = (uint16_t)((rx_data[0] << 8) | rx_data[1]);           
                    motor_yaw_info.rotor_speed     = (int16_t)((rx_data[2] << 8) | rx_data[3]);
                    motor_yaw_info.torque_current  = (int16_t)((rx_data[4] << 8) | rx_data[5]);
                    motor_yaw_info.temp            = rx_data[6];
				    motor_data_update_flag = 1;		
                    break;
                }
                // 可以在这里加其他电机的 case，比如 0x206, 0x207 等
                default:
                    break;
            }
        }
        else
        {
            // 可选：错误处理，比如记录错误标志
            // Error_Handler();
        }
    }
*/  motor_data_update_flag = 1;		
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}
 
void set_GM6020_motor_voltage(CAN_HandleTypeDef* hcan,int16_t v1)
{
  CAN_TxHeaderTypeDef tx_header;
  uint8_t             tx_data[8] = {0};
    
  tx_header.StdId = 0x1FF;
  tx_header.IDE   = CAN_ID_STD;
  tx_header.RTR   = CAN_RTR_DATA;
  tx_header.DLC   = 8;
 
  tx_data[0] = (v1>>8)&0xff;
  tx_data[1] =    (v1)&0xff;
	 
  HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data,(uint32_t*)CAN_TX_MAILBOX0);
}
