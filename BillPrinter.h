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

class BillPrinter
{
public:
	BillPrinter();

	void print_plays(void);

	string print_bill(invoice customer_invoice);
	string print_bill_html(invoice customer_invoice);

private:
	void init_plays(void);
	play play_vector[num_plays];

	play play_for(performance a_performance);	
	float usd(uint32_t amount);
	uint8_t total_volume_credits(invoice customer_invoice);
	uint32_t total_amount(invoice customer_invoice);

	string render_plain_text(invoice bill_data);
	string render_html(invoice bill_data);
	invoice create_invoice(invoice customer_invoice);
	PerformanceCalculator* create_calculator(performance a_performance, play a_play);
};


