/*
 * ADAS_CONTROL.h
 *
 *  Created on: ???/???/????
 *      Author: Ahmad Azab
 */

#ifndef ADAS_CONTROL_H_
#define ADAS_CONTROL_H_

/* I didn't use it */
#define GEAR_D 1
#define GEAR_N 0
#define GEAR_P 2
#define GEAR_R 3


u8 GRBOX_SELECT(void);
void SL_STATUS(void);
void CCS_STATUS(void);

void CCS_ON(void);
void CCS_OFF(void);
void SL_ON(void);
void SL_OFF(void);

void Ultrasonic_Init(void);
void UltrasonicTriggerAndEcho(void);
void Ultrasonic_CalcDist(void);
void update_BAS_SystemON(void);
void update_BAS_SystemOFF(void);

void BuzzerDriveMonitoring(void);
void ChangeInADC_CancelBuz(void);

#endif /* ADAS_CONTROL_H_ */
