/*-------------------------------------------------------------------
 [FILE NAME]: ultrasonic.h
 [AUTHOR(S)]: Zyad Nezar
 [DATE CREATED]: 15/10/2022
 [DESCRIPTION]: Header file for Ultrasonic driver
 -------------------------------------------------------------------*/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*----------------------------INCLUDES----------------------------*/

#include "../std_types.h"

/*----------------------------DEFINITIONS----------------------------*/

#define ULTRASONIC_TRIGGER_PORT_ID PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID PIN5_ID
#define CONVERT_FACTOR 0.017

/*----------------------------FUNCTION DECLARATIONS----------------------------*/

/*-------------------------------------------------------------------
 [Function Name]: Ultrasonic_init
 [Description]: Configures the ports for the Ultrasonic and initializes
 the ICU with a callback function
 [Args]: void
 [Returns]: void
 -------------------------------------------------------------------*/

void Ultrasonic_init(void);

/*-------------------------------------------------------------------
 [Function Name]: Ultrasonic_Trigger
 [Description]: Triggers the Ultrasonic to send an echo
 [Args]: void
 [Returns]: void
 -------------------------------------------------------------------*/

void Ultrasonic_Trigger(void);

/*-------------------------------------------------------------------
 [Function Name]: Ultrasonic_readDistance
 [Description]: Gets the measured distance by the Ultrasonic
 [Args]: void
 [Returns]: distance
 -------------------------------------------------------------------*/

uint16 Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */
