#include "main.h"






CAN_TxHeaderTypeDef can1_tx1;
CAN_TxHeaderTypeDef can1_tx2;
CAN_RxHeaderTypeDef can1_rx;


void CAN_Filter_FIFO0_AllPass_Init(void)
{
	CAN_FilterTypeDef filter;

	// === 选择 filter bank（CAN1 一般用 0~13）===
	filter.FilterBank = 0;

	// === 标准ID + 扩展ID 全通 ===
	filter.FilterMode = CAN_FILTERMODE_IDMASK;
	filter.FilterScale = CAN_FILTERSCALE_32BIT;

	// === 全通关键：ID = 0，MASK = 0 ===
	filter.FilterIdHigh = 0x0000;
	filter.FilterIdLow  = 0x0000;

	filter.FilterMaskIdHigh = 0x0000;
	filter.FilterMaskIdLow  = 0x0000;

	// === 接收 FIFO0 ===
	filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;

	// === 使能 filter ===
	filter.FilterActivation = ENABLE;

	// === F4 双 CAN 必须设置（即使你只用 CAN1）===
	filter.SlaveStartFilterBank = 14;

	// === 应用 filter ===
	HAL_CAN_ConfigFilter(&hcan1, &filter);
}

void CAN_TxData(const uint8_t *Tdata, const uint8_t len){//测试
	
	uint32_t pTxMailbox_Num;


	can1_tx1.StdId = 0x123;
	can1_tx1.IDE = CAN_ID_STD;
	can1_tx1.RTR = CAN_RTR_DATA;
	can1_tx1.DLC = len;
	uint8_t res = HAL_CAN_AddTxMessage(&hcan1,&can1_tx1,Tdata,&pTxMailbox_Num);

	
}




void CAN_GM6020_Current(const uint16_t*	I1234_below_16384 ){//测试

	uint32_t pTxMailbox_Num;


	can1_tx2.StdId = 0X1FE;//1234电机
	can1_tx2.IDE = CAN_ID_STD;
	can1_tx2.RTR = CAN_RTR_DATA;
	can1_tx2.DLC = 8;
	HAL_CAN_AddTxMessage(&hcan1,&can1_tx2,(uint8_t*)I1234_below_16384,&pTxMailbox_Num);


	u6_printf("6020_sent end \n\n");
}








uint8_t CAN_RxData(uint8_t *Rdata){


	uint8_t res = HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&can1_rx,Rdata);


	u6_printf("result:$ %s $\n ",Rdata);
	u6_printf("STDID:%d\n",can1_rx.StdId);
	u6_printf("DLC:%d\n",can1_rx.DLC);
	u6_printf("recived end \n\n");




	return res;


}






void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef  *hcan_){

	uint8_t Rdata[8];
	u6_printf("!!!!!!!!!@@@@@@@@#######\n ",Rdata);
	if(hcan_->Instance == CAN1){

		CAN_RxData(Rdata);




	}
}




















