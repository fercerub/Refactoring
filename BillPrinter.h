#pragma once
#include <string>

using namespace std;

typedef enum {
	tragedy = 0,
	comedy = 1,
} play_type;

typedef enum {
	hamlet = 0,
	dinner = 1,
	othello = 2,
	num_plays = 3
}play_id;

typedef struct {
	char name[20];
	play_type type;
}play;

typedef struct {
	uint8_t id;
	uint16_t audience;
}performance;

typedef struct {
	char customer[20];
	performance performances[20];
	uint8_t performances_played;
}invoice;

class BillPrinter
{
public:
	BillPrinter();

	void print_plays(void);

	string print_bill(invoice customer_invoice);

private:
	void init_plays(void);
	play play_vector[num_plays];
};
