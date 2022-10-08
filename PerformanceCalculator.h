#pragma once
#include "Data.h"

class PerformanceCalculator {
public:
	PerformanceCalculator(performance a_performance, play a_play);

	virtual uint32_t get_amount(void) = 0;
	virtual uint8_t get_volume_credits(void) = 0;
	performance a_performance;
	play a_play;

};

class TragedyCalculator : public PerformanceCalculator {
public:
	TragedyCalculator(performance a_performance, play a_play);

	uint32_t get_amount(void);
	uint8_t get_volume_credits(void);
};

class ComedyCalculator : public PerformanceCalculator {
public:
	ComedyCalculator(performance a_performance, play a_play);

	uint32_t get_amount(void);
	uint8_t get_volume_credits(void);
};
