#ifndef CAN_USER_H
#define CAN_USER_H


void CAN_Filter_FIFO0_AllPass_Init(void);

void CAN_TxData(const uint8_t *Tdata, uint8_t len);
void CAN_GM6020_Current(const int16_t*	I1234_below_16384 );
void CAN_GM6020_voltage(const int16_t*	V1234below_25000 );











uint8_t CAN_RxData(uint8_t *Rdata);


#endif
