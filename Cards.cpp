#include "Cards.h"

Card::Card()
{
	int randomType = rand() % 5; //random number between 0-5 for types
	type = new string(types[randomType]);
}

Card::Card(string t)
{
	for (int i = 0; i < 4; i++) //check if one of the types allowed
	{
		if (t == types[i])
		{
			type = new string(t);
			return;
		}
	}
	cout << "Error, type not recognized";
}

Card::Card(const Card &card2) // copy constructor
{
	type = new string(*card2.type);
}

ostream &operator<<(ostream &out, const Card &c) //stream insertion
{
	out << "Card type: " + *c.type + "\n";
	return out;
}

string Card::getType()
{
	return *type;
}

//////DECK DECK DECK///////

Deck::Deck()
{
	cardsVector = new vector<Card>;

	for (int i = 0; i < 50; i++) //Fill the deck's vector of cards with 50 cards
	{
		cardsVector->push_back(Card());
	}
}

Deck::Deck(const Deck &deck2) //copy constructor
{
	cardsVector = new vector<Card>;

	for (int i = 0; i < deck2.cardsVector->size(); i++)
	{
		cardsVector->push_back(deck2.cardsVector->at(i));
	}
}

ostream &operator<<(ostream &out, const Deck &d) //stream insertion
{
	out << "the number of cards in the deck is: " << d.cardsVector->size() << endl;

	for (int i = 0; i < d.cardsVector->size(); i++)
	{
		out << d.cardsVector->at(i);
	}
	out << "\n\n";
	return out;
}

Card Deck::draw()
{
	int randomIndex = rand() % (cardsVector->size()); //get a random index within the deck
	Card tempCard = cardsVector->at(randomIndex);	  //store a temporary card to return at the end

	cardsVector->erase(cardsVector->begin() + randomIndex); //erase the chosen random card

	return tempCard;
}

void Deck::add(Card newCard)
{
	cardsVector->push_back(newCard);
}

//////// HAND HAND HAND //////////

Hand::Hand() //default constructor
{
	cardsVector = new vector<Card>;

	owner = NULL;
}

Hand::Hand(Player *player)
{
	cardsVector = new vector<Card>;
	owner = player;
}

Hand::Hand(const Hand &hand2) //copy constructor
{
	owner = hand2.owner;
	cardsVector = new vector<Card>;

	for (int i = 0; i < hand2.cardsVector->size(); i++)
	{
		cardsVector->push_back(hand2.cardsVector->at(i));
	}
}

ostream &operator<<(ostream &out, const Hand &h) //stream insertion
{
	out << h.owner->getName() << "'s hand" << endl;
	out << "List of cards in this hand: " << endl;

	for (int i = 0; i < h.cardsVector->size(); i++)
	{
		out << h.cardsVector->at(i);
	}
	out << "\n\n";
	return out;
}

void Hand::add(Card newCard) //add a card
{
	cardsVector->push_back(newCard);
}

void Hand::playCard(int index, Deck deck)
{
	//owner->issueOrder(cardsVector->at(index).getType());
	deck.add(cardsVector->at(index));
	cardsVector->erase(cardsVector->begin() + index);
}

bool Hand::isEmpty()
{
	return cardsVector->empty();
}