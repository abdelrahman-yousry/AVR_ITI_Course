/*
 * Port_prv_cfg.h
 *
 *  Created on: Mar 16, 2022
 *      Author: U3
 */

#ifndef PORT_PRV_CFG_H_
#define PORT_PRV_CFG_H_

#define MAX_PIN_NUM   			31
#define PIN_AND_PORT_DIVISOR 	8


#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0) 	0b##b7##b6##b5##b4##b3##b2##b1##b0

#endif /* PORT_PRV_CFG_H_ */

