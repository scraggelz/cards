#include <stdio.h>
#include "cards.h"


void play_bj()
{
	stack s;
	card player[2];
	card dealer[2];

	int psum;
	int dsum;
	char action;
	double bankroll;
	double wager;
	int playagain = 1; //1 for yes, 0 for no
	
	printf("Welcome to the Blackjack table.\n");

	printf("Enter your bankroll: ");
	scanf("%lf", &bankroll);
	while(bankroll < 1)
	{
		printf("Bankroll is too small.\n");
		printf("Enter another bankroll: ");
		scanf("%lf", &bankroll);
	}


//	printf("%0.2lf\n%0.2lf\n", bankroll, wager);	
	while(playagain != 0)
	{
		s.d = create_deck();
		s.count = 52;
		playagain = 0;
		psum = 0;
		dsum = 0;
		printf("Enter your wager: ");
		scanf("%lf", &wager);
		while(wager > bankroll || wager <= 0)
		{
			printf("Wager is too big.\n");
			printf("Enter another wager: ");
			scanf("%lf", &wager);
		}

		shuffle_deck(&s.d);
		player[0] = top(&s);
		pop(&s);
		dealer[0] = top(&s);
		pop(&s);
		player[1] = top(&s);
		pop(&s);
		dealer[1] = top(&s);	
		pop(&s);

		psum = bj_evaluate(&player[0]) + bj_evaluate(&player[1]);
		dsum = bj_evaluate(&dealer[0]) + bj_evaluate(&dealer[1]);

		printf("----Your cards---------\n");
		printf("%s\n%s\n",card_string(player[0]), card_string(player[1]));
		printf("Sum:%d\n", psum);
		printf("-----------------------\n\n");	

		printf("----Dealer's cards-----\n");
		printf("%s\n%s\n",card_string(dealer[1]), "Facedown Card");
		printf("Sum:%d\n", (dsum-bj_evaluate(&dealer[0])));

		printf("-----------------------\n\n");	

		while(psum < 21 && dsum < 21)
		{
			printf("Dealer's total is: %d\n",dsum-bj_evaluate(&dealer[0]));
			printf("Your total is: %d\n", psum);
			printf("(h)it or (s)tand: ");
			scanf("%c", &action);
			action = getchar();
			card delt;

			if(action == 'h')
			{
				delt = top(&s);
				pop(&s);
				printf("---You're delt----\n");
				printf("%s\n", card_string(delt));
				printf("------------------\n");
				psum += bj_evaluate(&delt);
			}

			if(dsum == 13 || dsum == 16 || dsum < 11)
			{
				delt = top(&s);
				pop(&s);
				printf("----Dealer deals----\n");
				printf("%s\n", card_string(delt));
				printf("---------------------\n");
				dsum += bj_evaluate(&delt);
			}

			else if(action == 's')
				break;
		}

		printf("\nDealer has: %d\nYou have: %d\n", dsum, psum);				
		if(psum == 21)	
		{
			printf("Blackjack. You win $%0.2lf.\n", wager);
			bankroll = bankroll + wager;
		}
	
		else if(dsum == 21)
		{
			printf("Dealer hit Blackjack. You lose $%0.2lf.\n", wager);
			bankroll = bankroll - wager;
		}

		else if(psum > 21)
		{
			printf("You busted. You lose %0.2lf.\n", wager);
			bankroll = bankroll - wager;
		}

		else if(dsum > psum && dsum <= 21)
		{
			printf("Dealer wins. You lose %0.2lf.\n", wager);
			bankroll = bankroll - wager;
		}
	
		else
		{
			printf("You win %0.2lf.\n", wager);
			bankroll += wager;
		}

		printf("Current bankroll: %0.2lf.\n", bankroll);
		printf("Do you wish to play again(1 for yes, 0 for no): ");
		scanf("%d", &playagain);
			

	}		


}

int main(int argc, char *argv[])
{
	play_bj();
	return 0;
}
