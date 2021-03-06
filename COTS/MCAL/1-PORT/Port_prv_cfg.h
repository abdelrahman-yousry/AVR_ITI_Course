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
//
//#define CONC(PORT_PIN_7_INIT_CFG,PORT_PIN_6_INIT_CFG,PORT_PIN_5_INIT_CFG,PORT_PIN_4_INIT_CFG,PORT_PIN_3_INIT_CFG,PORT_PIN_2_INIT_CFG,PORT_PIN_1_INIT_CFG,PORT_PIN_0_INIT_CFG)	CONC_HELPER(PORT_PIN_7_INIT_CFG,PORT_PIN_6_INIT_CFG,PORT_PIN_5_INIT_CFG,PORT_PIN_4_INIT_CFG,PORT_PIN_3_INIT_CFG,PORT_PIN_2_INIT_CFG,PORT_PIN_1_INIT_CFG,PORT_PIN_0_INIT_CFG)
//#endif /* PORT_PRV_CFG_H_ */
