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

TEST(Test, Imprime_Factura_Data1) {
	string resultado;
	BillPrinter ejemplo;

	invoice WITRAC;
	create_data_for_invoice(&WITRAC);

	resultado = ejemplo.print_bill(WITRAC);
	
	printf("%s", resultado.c_str());

	ASSERT_STREQ("\nInvoice for WITRAC\n\tHamlet: $650.00 (55 seats)\n\tDinner Game: $580.00 (35 seats)\n\tOthello: $500.00 (40 seats)\nAmount owed is $1730.00\nYou earned 47 credits\n\n",resultado.c_str());
}

static void create_data_for_invoice2(invoice* customer) {
	sprintf(customer->customer, "WITRAC");

	customer->performances[0].id = dinner;
	customer->performances[0].audience = 40;

	customer->performances[1].id = hamlet;
	customer->performances[1].audience = 27;

	customer->performances_played = 2;
}

TEST(Test, Imprime_Factura_Data2) {
	string resultado;
	BillPrinter ejemplo;

	invoice WITRAC;
	create_data_for_invoice2(&WITRAC);

	resultado = ejemplo.print_bill(WITRAC);

	printf("%s", resultado.c_str());

	ASSERT_STREQ("\nInvoice for WITRAC\n\tDinner Game: $620.00 (40 seats)\n\tHamlet: $400.00 (27 seats)\nAmount owed is $1020.00\nYou earned 18 credits\n\n", resultado.c_str());		
}

static void create_data_for_invoice3(invoice* customer) {
	sprintf(customer->customer, "IFCO");

	customer->performances[0].id = dinner;
	customer->performances[0].audience = 1020;

	customer->performances[1].id = othello;
	customer->performances[1].audience = 980;

	customer->performances[2].id = hamlet;
	customer->performances[2].audience = 1000;

	customer->performances[3].id = dinner;
	customer->performances[3].audience = 2000;

	customer->performances_played = 4;
}

TEST(Test, Imprime_Factura_Data3) {
	string resultado;
	BillPrinter ejemplo;

	invoice WITRAC;
	create_data_for_invoice3(&WITRAC);

	resultado = ejemplo.print_bill(WITRAC);
	
	printf("%s", resultado.c_str());

	ASSERT_STREQ("\nInvoice for IFCO\n\tDinner Game: $8460.00 (1020 seats)\n\tOthello: $9900.00 (980 seats)\n\tHamlet: $10100.00 (1000 seats)\n\tDinner Game: $16300.00 (2000 seats)\nAmount owed is $44760.00\nYou earned 108 credits\n\n", resultado.c_str());
	ASSERT_EQ(1, 1);
}