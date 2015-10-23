//card library for poker and other card games
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14

#define HEARTS 0
#define DIAMONDS 1
#define CLUBS 2
#define SPADES 3

typedef struct card
{
	int suit; 
	int rank;
} card;

typedef struct deck
{
	card var[52];
} deck;

deck create_deck()
{
	int i;
	deck  d; //creating a deck
	for(i=0; i<52; i++)
	{

		if(i<13)
		{
			d.var[i].suit = HEARTS;
			d.var[i].rank = i + 2; //d.var[i].rank, no pointer
		}
		
		else if(i < 26)
		{
			d.var[i].suit = DIAMONDS;
			d.var[i].rank = i -13 +2;
		}

		else if(i < 39)
		{
			d.var[i].suit = CLUBS;
			d.var[i].rank = i - 26 + 2;
		}

		else
		{
			d.var[i].suit = SPADES;
			d.var[i].rank = i - 39 + 2;
		}
	}

	return d;
}


void print_deck(deck *d, int count)
{
	int i;
	card curr;

	for(i=0; i<count; i++)
	{
		curr = d->var[i];
		if(curr.rank == JACK)
			printf("Jack of ");
		else if(curr.rank == QUEEN)
			printf("Queen of ");
		else if(curr.rank == KING)
			printf("King of ");
		else if(curr.rank == ACE)
			printf("Ace of ");
		else
			printf("%d of ", curr.rank);

		if(curr.suit == HEARTS)
			printf("Hearts\n");
		else if(curr.suit == CLUBS)
			printf("Clubs\n");
		else if(curr.suit == DIAMONDS)
			printf("Diamonds\n");
		else
			printf("Spades\n");
	}
}

void shuffle_deck(deck *d)
{
	srand(time(NULL));

	int i;
	for(i = 0; i< 52; i++)
	{
		int num = rand() % 52;

		card temp = d->var[i];
		d->var[i] = d->var[num];
		d->var[num] = temp;
	
	}	

}

typedef struct stack //stack structure to deal cards
{
	deck d;
	card top;
	int count;
	
} stack;

void push(stack *s, card c)
{
	if(s->count == 51)
	{
		printf("Stack of Cards is full.\n");
		return;
	}
	
	else
	{
		s->count++;
		s->d.var[s->count] = c;
	}

	return;
}

//calling top then popping is equivalent to dealing
void pop(stack *s)
{
	if(s->count == -1)
	{
		printf("Stack of Cards is empty.\n");
		return;
	}
	else
		s->count--;

}

card top(stack *s)
{
	return s->d.var[s->count-1];
}

//black jack evaluator
int bj_evaluate(card *curr)
{
	if(curr->rank < 10)
		return curr->rank;
	else if(curr->rank != ACE)
		return 10;
	else
		return 11;
}

//function to print one card
//TODO: strcat() strings together --DONE! 
char * card_string(card c)
{   //Queen of Diamonds - biggest string
	char *rank = malloc(5);
	char *of = " of ";
	char *suit = NULL;	

	if(c.suit == HEARTS)
		suit = "Hearts";
	else if(c.suit == CLUBS)
		suit = "Clubs";
	else if(c.suit==DIAMONDS)
		suit = "Diamonds";
	else
		suit = "Spades";

	if(c.rank < JACK)
		sprintf(rank, "%d", c.rank);
		//rank = "NUMBERS";
	else if(c.rank == JACK)
		rank = "Jack";
	else if(c.rank == QUEEN)
		rank = "Queen";
	else if(c.rank == KING)
		rank = "King";
	else
		rank = "Ace";

	
	char *name = malloc(18);
	strcat(name, rank);
	strcat(name, of);
	strcat(name, suit); 

	return name;	
}
		
