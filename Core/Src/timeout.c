/*
 * timeout.c
 *
 *  Created on: Oct 12, 2020
 *      Author: piotr
 */

#include "timeout.h"

TIM_HandleTypeDef * timeModule;
static uint32_t currentTimeMS;
static uint32_t currentTimeUS;
static uint32_t heartbeatStartTime;


void initTimeout(TIM_HandleTypeDef * htim2)
{
	timeModule = htim2;
	currentTimeMS = 0;
	currentTimeUS = 0;
	heartbeatStartTime = 0;
    HAL_TIM_Base_Start_IT(htim2);
}


uint32_t getTimeoutMS(void)
{
	return currentTimeMS;
}

bool addTimeoutMS(uint32_t addMS)
{
	if(addMS > UINT32_MAX - currentTimeMS)
	{
		return false;
	}

	currentTimeMS += addMS;
	return true;
}

void clearTimeutMS(void)
{
	currentTimeMS = 0;
}

uint32_t getTimeoutUS(void)
{
	return currentTimeUS;
}

bool addTimeoutUS(uint32_t addUS)
{
	if(addUS > UINT32_MAX - currentTimeUS)
	{
		return false;
	}

	currentTimeUS += addUS;
	return true;
}

void clearTimeutUS(void)
{
	currentTimeUS = 0;
}

bool hasTimedOut(uint32_t timeoutLimit, uint32_t startTime)
{
	if(timeoutLimit > UINT32_MAX - currentTimeMS)
		return true;

	if(timeoutLimit <= currentTimeMS - startTime)
		return true;
	return false;
}

bool hasTimedOutUS(uint32_t timeoutLimit, uint32_t startTime)
{
	if(timeoutLimit > UINT32_MAX - currentTimeUS)
		return true;

	if(timeoutLimit <= currentTimeUS - startTime)
		return true;
	return false;
}

void handleHeartbeatLED(GPIO_TypeDef * GPIO, uint16_t pin)
{
	if(hasTimedOut(HEARTBEATTIME, heartbeatStartTime))
	{
		heartbeatStartTime = currentTimeMS;
		HAL_GPIO_TogglePin(GPIO, pin);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == timeModule)
  {
	  currentTimeUS += 250;
	  if(currentTimeUS % 1000 == 0)
	  {
		  currentTimeMS++;
	  }

  }
}
