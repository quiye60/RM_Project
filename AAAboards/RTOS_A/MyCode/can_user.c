#include <stdlib.h>

#include "can.h"
#include "cmsis_os2.h"
#include "main.h"

#include "uart_printf.h"
#include "freertos_extern.h"



CAN_Packet_t can1_RX;
uint16_t RxID=0x111;



CAN_TxHeaderTypeDef can1_tx1;
CAN_TxHeaderTypeDef can1_tx2;
CAN_RxHeaderTypeDef can1_rx;


void CAN_Filter_FIFO0_AllPass_Init(void)
{
    CAN_FilterTypeDef filter;

    filter.FilterBank = 0;                     // CAN1用0-13
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;

    // ===== 全通关键 =====
    filter.FilterIdHigh = 0x0000;
    filter.FilterIdLow  = 0x0000;
    filter.FilterMaskIdHigh = 0x0000;
    filter.FilterMaskIdLow  = 0x0000;

    // FIFO0
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;

    // 使能
    filter.FilterActivation = ENABLE;

    // F4双CAN必须写（即使只用CAN1）
    filter.SlaveStartFilterBank = 14;

	u6_printf("config_fliter%d\n",	HAL_CAN_ConfigFilter(&hcan1, &filter));
	u6_printf("start: %d\n",		HAL_CAN_Start(&hcan1));
	u6_printf("fifo: %d\n",			HAL_CAN_ActivateNotification(&hcan1,
														 CAN_IT_RX_FIFO0_MSG_PENDING));


}




void CAN_GM6020_Current(const int16_t*	I1234_below_16384 ){//测试

	uint32_t pTxMailbox_Num;
		
	uint8_t CAN_TxData[8];
	CAN_TxData[0] = (uint8_t)(I1234_below_16384[0] >> 8);
	CAN_TxData[1] = (uint8_t)(I1234_below_16384[0]);

	CAN_TxData[2] = (uint8_t)(I1234_below_16384[1] >> 8);
	CAN_TxData[3] = (uint8_t)(I1234_below_16384[1]);

	CAN_TxData[4] = (uint8_t)(I1234_below_16384[2] >> 8);
	CAN_TxData[5] = (uint8_t)(I1234_below_16384[2]);

	CAN_TxData[6] = (uint8_t)(I1234_below_16384[3] >> 8);
	CAN_TxData[7] = (uint8_t)(I1234_below_16384[3]);

	can1_tx2.StdId = 0X1FE;//1234电机
	can1_tx2.IDE = CAN_ID_STD;
	can1_tx2.RTR = CAN_RTR_DATA;
	can1_tx2.DLC = 8;
	HAL_CAN_AddTxMessage(&hcan1,&can1_tx2,CAN_TxData,&pTxMailbox_Num);

	}


static uint8_t CAN_voltage14[8];

void CAN_GM6020_voltage(const int16_t*	V1234below_25000 ){//测试

	CAN_TxHeaderTypeDef tx_header;
    uint32_t used_mailbox;

	tx_header.StdId = 0x1FF;
    tx_header.ExtId = 0;
    tx_header.IDE = CAN_ID_STD;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 0x08;
	CAN_voltage14[0] = (V1234below_25000[0] >> 8);
    CAN_voltage14[1] = V1234below_25000[0];
	CAN_voltage14[2] = (V1234below_25000[1] >> 8);
    CAN_voltage14[3] = V1234below_25000[1];
    CAN_voltage14[4] = (V1234below_25000[2] >> 8);
    CAN_voltage14[5] = V1234below_25000[2];
    CAN_voltage14[6] = (V1234below_25000[3] >> 8);
    CAN_voltage14[7] = V1234below_25000[3];
    HAL_CAN_AddTxMessage(&hcan1, &tx_header,CAN_voltage14 , &used_mailbox);
	
	
	}




uint8_t CAN_RxData(CAN_Packet_t * pack) {

	HAL_StatusTypeDef res=HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&can1_rx,pack->data);
	pack->ID=can1_rx.StdId|can1_rx.ExtId;
	return res;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef  *hcan_){

    
	if(hcan_->Instance == CAN1){



		CAN_Packet_t *pkt = (CAN_Packet_t *)malloc(sizeof(CAN_Packet_t));
		CAN_RxData(pkt);
		osMessageQueuePut(canrx_QHandle,&pkt,0,osWaitForever);


	}
}




















