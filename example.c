#include <stdio.h>
#include "cards.h"

int main()
{
	//sorted deck has been created
	deck d  = create_deck();
	print_deck(&d,52);
	printf("\n\n");

	//shuffle and reprint the deck
	shuffle_deck(&d);
	print_deck(&d,52);

	printf("\n\n");

	//creating a "stack of cards"
	stack s;
	s.count = 52;
	s.d = d; //the stacks deck is equal to the created deck
			//s.d = create_deck() would work

	//get top card and remove it from s.d
	card curr = top(&s);
	pop(&s);

	char *ccard = card_string(curr);
	int sum = bj_evaluate(&curr);

//	printf("Card: %s.\n Sum: %d.\n ", ccard, sum);
	printf("\n\n");
	print_deck(&d, s.count);


	return 0;
}
