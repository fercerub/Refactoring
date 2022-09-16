#include "pch.h"
#include "BillPrinter.h"

static void create_data_for_invoice(invoice* customer) {
	sprintf(customer->customer, "WITRAC");

	customer->performances[0].id = hamlet;
	customer->performances[0].audience = 55;

	customer->performances[1].id = dinner;
	customer->performances[1].audience = 35;

	customer->performances[2].id = othello;
	customer->performances[2].audience = 40;

	customer->performances_played = 3;
}

TEST(Test, Imprime_Factura) {
	string resultado;
	BillPrinter ejemplo;

	invoice WITRAC;
	create_data_for_invoice(&WITRAC);

	resultado = ejemplo.print_bill(WITRAC);
	
	printf("%s", resultado.c_str());

	ASSERT_STREQ("\nInvoice for WITRAC\n\tHamlet: $650.00 (55 seats)\n\tDinner Game: $580.00 (35 seats)\n\tOthello: $500.00 (40 seats)\nAmount owed is $1730.00\nYou earned 47 credits\n\n",resultado.c_str());
}

