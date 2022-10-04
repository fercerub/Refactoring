#include "pch.h"
#include "BillPrinter.h"

static void create_data_for_invoice_A(invoice* customer) {
	sprintf(customer->customer, "Group A");

	customer->performances[0].id = hamlet;
	customer->performances[0].audience = 55;

	customer->performances[1].id = dinner;
	customer->performances[1].audience = 35;

	customer->performances[2].id = othello;
	customer->performances[2].audience = 40;

	customer->performances_played = 3;
}

TEST(Test, Print_bill_for_group_A) {
	string result;
	BillPrinter bill1;

	invoice Group_A;
	create_data_for_invoice_A(&Group_A);

	result = bill1.print_bill(Group_A);
	
	printf("%s", result.c_str());

	ASSERT_STREQ("\nInvoice for Group A\n\tHamlet: $650.00 (55 seats)\n\tDinner Game: $580.00 (35 seats)\n\tOthello: $500.00 (40 seats)\nAmount owed is $1730.00\nYou earned 47 credits\n\n",result.c_str());
}

static void create_data_for_invoice_B(invoice* customer) {
	sprintf(customer->customer, "Group B");

	customer->performances[0].id = dinner;
	customer->performances[0].audience = 40;

	customer->performances[1].id = hamlet;
	customer->performances[1].audience = 27;

	customer->performances_played = 2;
}

TEST(Test, Print_bill_for_group_B) {
	string result;
	BillPrinter bill2;

	invoice Group_B;
	create_data_for_invoice_B(&Group_B);

	result = bill2.print_bill(Group_B);

	printf("%s", result.c_str());

	ASSERT_STREQ("\nInvoice for Group B\n\tDinner Game: $620.00 (40 seats)\n\tHamlet: $400.00 (27 seats)\nAmount owed is $1020.00\nYou earned 18 credits\n\n", result.c_str());		
}

static void create_data_for_invoice_C(invoice* customer) {
	sprintf(customer->customer, "Group C");

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

TEST(Test, Print_bill_for_group_C) {
	string result;
	BillPrinter bill3;

	invoice Group_C;
	create_data_for_invoice_C(&Group_C);

	result = bill3.print_bill(Group_C);
	
	printf("%s", result.c_str());

	ASSERT_STREQ("\nInvoice for Group C\n\tDinner Game: $8460.00 (1020 seats)\n\tOthello: $9900.00 (980 seats)\n\tHamlet: $10100.00 (1000 seats)\n\tDinner Game: $16300.00 (2000 seats)\nAmount owed is $44760.00\nYou earned 108 credits\n\n", result.c_str());
}

TEST(Test, Print_bill_for_group_C_in_HTML) {
	string result;
	BillPrinter bill3;

	invoice Group_C;
	create_data_for_invoice_C(&Group_C);

	result = bill3.print_bill_html(Group_C);

	printf("%s", result.c_str());
																																																																																																												
	ASSERT_STREQ("\n<h1>Invoice for Group C</h1>\n<table>\n<tr><th>play</th><th>seats</th><th>cost</th></tr>\n<tr><td>Dinner Game</td><td>:$8460.00</td><td>(1020 seats)</td></tr>\n<tr><td>Othello</td><td>:$9900.00</td><td>(980 seats)</td></tr>\n<tr><td>Hamlet</td><td>:$10100.00</td><td>(1000 seats)</td></tr>\n<tr><td>Dinner Game</td><td>:$16300.00</td><td>(2000 seats)</td></tr>\n</table>\n<p>Amount owed is <em>$44760.00</em></p>\n<p>You earned <em>108</em> credits</p>\n\n", result.c_str());
}