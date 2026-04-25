#ifndef CAN_USER_H
#define CAN_USER_H











void CAN_Filter_AllPass_Init(void);
void CAN_TxData(const uint8_t *Tdata, uint8_t len);
uint8_t CAN_RxData(uint8_t *Rdata);







#endif
