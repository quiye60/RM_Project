#include "main.h"

uint8_t Rdata[8];
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

u6_printf("config_fliter%d\n",    HAL_CAN_ConfigFilter(&hcan1, &filter));
}

void CAN_TxData(const uint8_t *Tdata, const uint8_t len){//测试
	
	uint32_t pTxMailbox_Num;


	can1_tx1.StdId = 0x123;
	can1_tx1.IDE = CAN_ID_STD;
	can1_tx1.RTR = CAN_RTR_DATA;
	can1_tx1.DLC = len;
	uint8_t res = HAL_CAN_AddTxMessage(&hcan1,&can1_tx1,(uint8_t*)Tdata,&pTxMailbox_Num);


	u6_printf("res1 = %d \n",res);
	u6_printf("sent end \n\n");
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
	uint8_t res = HAL_CAN_AddTxMessage(&hcan1,&can1_tx2,CAN_TxData,&pTxMailbox_Num);
	
	
	int16_t M1 = (int16_t)((CAN_TxData[0] << 8) | CAN_TxData[1]);
    int16_t M2 = (int16_t)((CAN_TxData[2] << 8) | CAN_TxData[3]);
    int16_t M3 = (int16_t)((CAN_TxData[4] << 8) | CAN_TxData[5]);
    int16_t M4 = (int16_t)((CAN_TxData[6] << 8) | CAN_TxData[7]);

    u6_printf("M1=%d M2=%d M3=%d M4=%d\r\n", M1, M2, M3, M4);
	
	
	
	
	
	
	u6_printf("6020_sent end \n\n");
	
	
	
	}


	
static uint8_t CAN_voltage14[8];

void CAN_GM6020_voltage(const int16_t*	V1234below_25000 ){//测试

	   CAN_TxHeaderTypeDef tx_header;
    uint32_t used_mailbox;

	HAL_CAN_AddTxMessage(&hcan1, &tx_header, CAN_voltage14, &used_mailbox);
	

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





HAL_StatusTypeDef res = HAL_ERROR;
uint8_t CAN_RxData(uint8_t *Rdata){


	res = HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&can1_rx,Rdata);
	RxID=can1_rx.StdId;



	return res;


}






void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef  *hcan_){

    
	if(hcan_->Instance == CAN1){

		CAN_RxData(Rdata);
		



	}
}




















