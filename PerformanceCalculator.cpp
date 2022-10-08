#include "pch.h"
#include "PerformanceCalculator.h"

PerformanceCalculator::PerformanceCalculator(performance a_performance, play a_play):a_performance(a_performance), a_play(a_play) {}

TragedyCalculator::TragedyCalculator(performance a_performance, play a_play):PerformanceCalculator(a_performance, a_play) {}

uint32_t TragedyCalculator::get_amount(void) {
	uint32_t result = 40000;
	if (a_performance.audience > 30) {
		result += 1000 * (a_performance.audience - 30);
	}
	return result;
}

uint8_t TragedyCalculator::get_volume_credits(void) {
	uint8_t result = 0;
	result += std::max(a_performance.audience - 30, 0);
	return result;
}

ComedyCalculator::ComedyCalculator(performance a_performance, play a_play) :PerformanceCalculator(a_performance, a_play) {}

uint32_t ComedyCalculator::get_amount(void) {
	uint32_t result = 30000;
	if (a_performance.audience > 20) {
		result += 10000 + 500 * (a_performance.audience - 20);
	}
	result += 300 * (a_performance.audience);

	return result;
}

uint8_t ComedyCalculator::get_volume_credits(void) {
	uint8_t result = 0;
	result += std::max(a_performance.audience - 30, 0);
	result += std::floor(a_performance.audience / 5);
	return result;
}
