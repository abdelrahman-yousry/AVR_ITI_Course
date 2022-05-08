/*
 * Ext_Int.h
 *
 *  Created on: April 25, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef EXT_INT_H_
#define EXT_INT_H_

/*Macros for setting the mode of the interrupt 0 (Interrupt Sense Control)
 * bit no --> 0,1
 * */
#define EXT_u8INT0_LOW_LEVEL			0b00000000
#define EXT_u8INT0_LOGICAL_CHANGE		0b00000001
#define EXT_u8INT0_RISING_EDGE			0b00000010
#define EXT_u8INT0_FALLING_EDGE			0b00000011
#define EXT_u8INT0_CLEAR_MASK			((u8)0xFC)
/*MCUCR Register*/
/*Macros for setting the mode of the interrupt 1 (Interrupt Sense Control)
 * bit no --> 2,3
 * */

#define EXT_u8INT1_LOW_LEVEL			0b00000000
#define EXT_u8INT1_LOGICAL_CHANGE		0b00000100
#define EXT_u8INT1_RISING_EDGE			0b00001000
#define EXT_u8INT1_FALLING_EDGE			0b00001100


/*Register – MCUCSR*/
/*bit no --> 6*/
/*Macro for setting the mode of the interrupt 2 (Interrupt Sense Control)*/
#define EXT_u8INT2_FALLING_EDGE			((u8)0x40)
#define EXT_u8INT2_RISING_EDGE			((u8)0x00)

/*General Interrupt Control
Register – GICR*/
/*Macros for controlling interrupt for INT0/INT1/INT2*/
#define EXT_INT0_ENABLE					((u8)0x40)
#define EXT_INT1_ENABLE					((u8)0x80)
#define EXT_INT2_ENABLE					((u8)0x20)
#define EXT_INT_DISABLE					((u8)0x01)

typedef void(*pcbf)(void);

typedef enum
{
	Ext_INT_0,
	Ext_INT_1,
	Ext_INT_2,
	Ext_MaxNum
}Ext_enuNum;

typedef enum
{
	Ext_enuOk,
	Ext_InvalidIntNum,
	Ext_NullPtr,
}Ext_tenuErrorStatus;
typedef struct
{
	Ext_enuNum Ext_NUM;
	u8 Ext_u8IntSenseCtrl;
	u8 Ext_u8IntCtrl;
}Ext_tstrCfg;

Ext_tenuErrorStatus Ext_enuInit(Ext_tstrCfg* Ext_strCfg);
Ext_tenuErrorStatus Ext_enuIntEnable(Ext_enuNum Ext_enuIntNum);
Ext_tenuErrorStatus Ext_enuIntDisable(Ext_enuNum Ext_enuIntNum);
Ext_tenuErrorStatus Ext_enuRegCallBackFun(pcbf Copy_pcbf,Ext_enuNum Ext_enuIntNum);
#endif /* EXT_INT_H_ */
