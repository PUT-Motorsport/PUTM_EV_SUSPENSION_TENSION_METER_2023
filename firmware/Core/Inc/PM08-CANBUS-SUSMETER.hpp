#ifndef SUSMETER_H_
#define SUSMETER_H_

#include <cstdint>
#include "main.h"

namespace PUTM_CAN {

struct __attribute__ ((packed)) Susmeter_data {
	uint8_t tension_left;
	uint8_t tension_right;
};

const uint16_t SUSMETER_DATA_CAN_ID = 0x8E;
const uint8_t SUSMETER_DATA_CAN_DLC = sizeof(Susmeter_data);
const uint8_t SUSMETER_DATA_FREQUENCY = 100;

const CAN_TxHeaderTypeDef can_tx_header_SUSMETER_DATA {
	SUSMETER_DATA_CAN_ID,
	0xFFF,
	CAN_ID_STD,
	CAN_RTR_DATA,
	SUSMETER_DATA_CAN_DLC,
	DISABLE
};

} /* PUTM_CAN */
#endif /* SUSMETER_H_ */
