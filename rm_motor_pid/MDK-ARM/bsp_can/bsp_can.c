#include "stm32f4xx.h"                  // Device header
#include "bsp_can.h" 
#include "main.h" 
#include "stdio.h"
extern CAN_HandleTypeDef hcan1;
void can_filter_init(void)
{

    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    can_filter_st.FilterBank = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);


    can_filter_st.SlaveStartFilterBank = 14;
//    can_filter_st.FilterBank = 14;
//    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
//    HAL_CAN_Start(&hcan2);
//    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);



}
static uint8_t  dt[8] ; 
void CAN_Send_Data(CAN_HandleTypeDef *hcan, int a)
{
    CAN_TxHeaderTypeDef tx_header;
    uint32_t used_mailbox;

    //assert_param(hcan != NULL);
if (HAL_CAN_AddTxMessage(hcan, &tx_header, dt, &used_mailbox) != HAL_OK) {
    printf("%d/n",1);
}
    tx_header.StdId = 0x1FF;
    tx_header.ExtId = 0;
    tx_header.IDE = CAN_ID_STD;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 0x08;
	dt[0] = (a >> 8);
    dt[1] = a;
	dt[2] = (a >> 8);
    dt[3] = a;
    dt[4] = (a >> 8);
    dt[5] = a;
    dt[6] = (a >> 8);
    dt[7] = a;
    HAL_CAN_AddTxMessage(hcan, &tx_header, dt, &used_mailbox);
}
 motor_measure_t  motor_chassis[7];

