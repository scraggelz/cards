#include <stdio.h>
#include "cards.h"

int main()
{
	stack s;
	s.count = 52;
	s.d = create_deck();

	shuffle_deck(&s.d);
	card curr = top(&s);

	printf("%s\n", card_string(curr));

}
