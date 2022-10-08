#include "pch.h"
#include "BillPrinter.h"

BillPrinter::BillPrinter() {
	init_plays();
}

void BillPrinter::init_plays(void) {
	sprintf(play_vector[hamlet].name, "Hamlet");
	play_vector[hamlet].type = tragedy;

	sprintf(play_vector[dinner].name, "Dinner Game");
	play_vector[dinner].type = comedy;

	sprintf(play_vector[othello].name, "Othello");
	play_vector[othello].type = tragedy;
}

void BillPrinter::print_plays(void) {
	for (uint8_t i = 0; i < num_plays; i++) {
		printf("Play %u, %s, Type = %u\n", i, play_vector[i].name, play_vector[i].type);
	}
}

string BillPrinter::print_bill(invoice customer_invoice) {
	return render_plain_text(create_invoice(customer_invoice));
}

string BillPrinter::print_bill_html(invoice customer_invoice) {
	return render_html(create_invoice(customer_invoice));
}


play BillPrinter::play_for(performance a_performance) {
	return play_vector[a_performance.id];
}


float BillPrinter::usd(uint32_t amount) {
	return (float)amount / 100.0;
}

uint8_t BillPrinter::total_volume_credits(invoice customer_invoice) {
	uint8_t result = 0;
	for (uint8_t i = 0; i < customer_invoice.performances_played; i++) {		
		result += customer_invoice.performances[i].volume_credits_;
	}
	return result;
}

uint32_t BillPrinter::total_amount(invoice customer_invoice) {
	uint32_t result = 0;
	for (uint8_t i = 0; i < customer_invoice.performances_played; i++) {
		result += customer_invoice.performances[i].amount_;
	}
	return result;
}

string BillPrinter::render_plain_text(invoice bill_data){
	char string_to_print[100];
	string result("\nInvoice for ");

	result += bill_data.customer + string("\n");

	for (uint8_t i = 0; i < bill_data.performances_played; i++) {
		//print line for this order			
		sprintf(string_to_print, "	%s: $%2.2f (%u seats)\n", bill_data.performances[i].play_.name, usd(bill_data.performances[i].amount_), bill_data.performances[i].audience);
		result += string(string_to_print);
	}

	sprintf(string_to_print, "Amount owed is $%2.2f\nYou earned %u credits\n\n", usd(bill_data.total_amount_), bill_data.total_volume_credits_);
	result += string(string_to_print);
	return result;
}

string BillPrinter::render_html(invoice bill_data) {
	char string_to_print[100];
	string result("\n<h1>Invoice for ");

	result += bill_data.customer + string("</h1>\n") + string("<table>\n");
	result += string("<tr><th>play</th><th>seats</th><th>cost</th></tr>\n");

	for (uint8_t i = 0; i < bill_data.performances_played; i++) {
		//print line for this order			
		sprintf(string_to_print, "<tr><td>%s</td><td>:$%2.2f</td><td>(%u seats)</td></tr>\n", bill_data.performances[i].play_.name, usd(bill_data.performances[i].amount_), bill_data.performances[i].audience);
		result += string(string_to_print);
	}
	result += string("</table>\n");
	sprintf(string_to_print, "<p>Amount owed is <em>$%2.2f</em></p>\n<p>You earned <em>%u</em> credits</p>\n\n", usd(bill_data.total_amount_), bill_data.total_volume_credits_);
	result += string(string_to_print);
	return result;
}

invoice BillPrinter::create_invoice(invoice customer_invoice) {
	invoice bill_data = {};
	strcpy(bill_data.customer, customer_invoice.customer);
	bill_data.performances_played = customer_invoice.performances_played;

	for (uint8_t i = 0; i < bill_data.performances_played; i++) {		
		bill_data.performances[i] = customer_invoice.performances[i];
		PerformanceCalculator* calculator = create_calculator(bill_data.performances[i], play_for(bill_data.performances[i]));
		bill_data.performances[i].play_ = calculator->a_play;
		bill_data.performances[i].amount_ = calculator->get_amount();
		bill_data.performances[i].volume_credits_ = calculator->get_volume_credits();
		delete(calculator);
	}
	bill_data.total_amount_ = total_amount(bill_data);
	bill_data.total_volume_credits_ = total_volume_credits(bill_data);
	return bill_data;
}

PerformanceCalculator* BillPrinter::create_calculator(performance a_performance, play a_play) {
	switch (a_play.type) {
	case tragedy:
		return new TragedyCalculator(a_performance, a_play);
		break;
	case comedy:
		return new ComedyCalculator(a_performance, a_play);
		break;
	}
}
