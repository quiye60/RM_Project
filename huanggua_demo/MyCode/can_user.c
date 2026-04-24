#include "main.h"





CAN_FilterTypeDef can1_filter;
CAN_TxHeaderTypeDef can1_tx;
CAN_RxHeaderTypeDef can1_rx;

void CAN_Filter_AllPass_Init(void)//CAN_FILTER_FIFO0
{
	CAN_FilterTypeDef filter;

	filter.FilterBank = 0;
	filter.FilterMode = CAN_FILTERMODE_IDMASK;
	filter.FilterScale = CAN_FILTERSCALE_32BIT;

	filter.FilterIdHigh = 0x0000;
	filter.FilterIdLow  = 0x0000;

	filter.FilterMaskIdHigh = 0x0000;
	filter.FilterMaskIdLow  = 0x0000;

	filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	filter.FilterActivation = ENABLE;

	HAL_CAN_ConfigFilter(&hcan1, &filter);
}

void CAN_TxData(const uint8_t *Tdata, const uint8_t len){
	
	uint32_t pTxMailbox_Num;


	can1_tx.StdId = 0x123;
	can1_tx.ExtId = 0x12345673;
	can1_tx.IDE = CAN_ID_STD;
	can1_tx.RTR = CAN_RTR_DATA;
	can1_tx.DLC = len; 
	uint8_t res = HAL_CAN_AddTxMessage(&hcan1,&can1_tx,Tdata,&pTxMailbox_Num);
	u1_printf("res = %d pTxMailbox_Num = %d\r\n",res,pTxMailbox_Num);
	u1_printf("sent end \n\n");
}

uint8_t CAN_RxData(uint8_t *Rdata){


	uint8_t res = HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&can1_rx,Rdata);
	u1_printf("result:$ %s $\n ",Rdata);
	u1_printf("STDID:%d\n",can1_rx.StdId);
	u1_printf("DLC:%d\n",can1_rx.DLC);
	u1_printf("recived end \n\n");




	return res;


}


























