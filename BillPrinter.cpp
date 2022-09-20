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
	char string_to_print[100];
	uint32_t total_amount = 0;
	uint8_t volume_credits = 0;
	string result("\nInvoice for ");

	result += customer_invoice.customer + string("\n");

	for (uint8_t i = 0; i < customer_invoice.performances_played; i++) {
		play current_play = play_vector[customer_invoice.performances[i].id];
		uint32_t this_amount = 0;

		switch (current_play.type) {
		case tragedy:
			this_amount = 40000;
			if (customer_invoice.performances[i].audience > 30) {
				this_amount += 1000 * (customer_invoice.performances[i].audience - 30);
			}
			break;
		case comedy:
			this_amount = 30000;
			if (customer_invoice.performances[i].audience > 20) {
				this_amount += 10000 + 500 * (customer_invoice.performances[i].audience - 20);
			}
			this_amount += 300 * (customer_invoice.performances[i].audience);
			break;
		default:
			break;
		}

		//add volume credits
		volume_credits += std::max(customer_invoice.performances[i].audience - 30, 0);

		//add extra credit for every ten comedy attendees
		if (current_play.type == comedy)
			volume_credits += std::floor(customer_invoice.performances[i].audience / 5);

		//print line for this order			
		sprintf(string_to_print, "	%s: $%2.2f (%u seats)\n", current_play.name, (float)this_amount / 100.0, customer_invoice.performances[i].audience);
		result += string(string_to_print);
		total_amount += this_amount;
	}
	sprintf(string_to_print, "Amount owed is $%2.2f\nYou earned %u credits\n\n", (float)total_amount / 100.0, volume_credits);
	result += string(string_to_print);
	return result;
}
