/*
 * Servo_cfg.c
 *
 *  Created on: May 29, 2022
 *      Author: Abdelrahman Yousry
 */
#include "../Services/Std_types.h"
#include "Serrvo.h"
#include "Servo_cfg.h"


const Servo_tCfg Servo_Cfg[SERVO_MAX_NUM]=
{
		[SERVO_NUM1]={
				.InitialAngle = 10,
				.ChNum = Pwm_enuCh1A
		}
};

