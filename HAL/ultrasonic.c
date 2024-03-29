/*-------------------------------------------------------------------
 [FILE NAME]: ultrasonic.c
 [AUTHOR(S)]: Zyad Nezar
 [DATE CREATED]: 15/10/2022
 [DESCRIPTION]: Source file for Ultrasonic driver
 -------------------------------------------------------------------*/

/*----------------------------INCLUDES----------------------------*/

#include "ultrasonic.h"
#include "../MCAL/icu.h"
#include "../MCAL/gpio.h"
#include "util/delay.h"

/*----------------------------GLOBAL VARIABLES----------------------------*/

static uint8 g_edgeCounter = 0;
static uint8 g_distanceFlag = 0;
static uint16 g_timeHigh = 0;

/*----------------------------FUNCTION DEFINITIONS----------------------------*/

/*-------------------------------------------------------------------
 [Function Name]: Ultrasonic_edgeProcessing
 [Description]: Changes the ICU detection type to measure the high time
 [Args]: void
 [Returns]: void
 -------------------------------------------------------------------*/

void Ultrasonic_edgeProcessing(void) {
	g_edgeCounter++;
	if (g_edgeCounter == 1) {
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	} else if (g_edgeCounter == 2) {
		g_timeHigh = Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		g_edgeCounter = 0;
		g_distanceFlag = 1;
	}
}

void Ultrasonic_init(void) {
	const Icu_ConfigType Icu_Config = { F_CPU_8, RISING };
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	Icu_init(&Icu_Config);
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,
			ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID,
			LOGIC_LOW);
}

void Ultrasonic_Trigger(void) {
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID,
			LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID,
			LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void) {
	uint16 measuredDistance = 0;
	Ultrasonic_Trigger();
	while (!g_distanceFlag)
		;
	g_distanceFlag = 0;
	measuredDistance = CONVERT_FACTOR * g_timeHigh;
	return measuredDistance;
}

