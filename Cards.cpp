#include "Cards.h"
#include "Player.h"
#include "Map.h"

const string Card::types[] = { "bomb", "reinforcement", "blockade", "airlift", "diplomacy" };

Card::Card()
{
	int randomType = rand() % 5; //random number between 0-5 for types
	type = types[randomType];
}

Card::Card(string t)
{
	for (int i = 0; i < 4; i++) //check if one of the types allowed
	{
		if (t == types[i])
		{
			type = t;
			return;
		}
	}
	cout << "Error, type not recognized";
}

Card::Card(const Card &card2) // copy constructor
{
	type = card2.type;
	deck=card2.deck;
	hand=card2.hand;
}

ostream &operator<<(ostream &out, const Card &c) //stream insertion
{
	out << "Card type: " + c.type + "\n";
	return out;
}

string Card::getType()
{
	return type;
}

void Card::play() {
    Card* newCard=new Card(this->type, this->deck, this->hand);
    this->deck->add(newCard);
    for(int i=0;i<hand->getCardsVector().size(); i++){
        if(hand->getCardsVector()[i]==this){
            hand->getCardsVector().erase(hand->getCardsVector().begin()+i);
            break;
        }
    }

}

//////DECK DECK DECK///////

Deck::Deck()
{
	cardsVector = new vector<Card*>;

	for (int i = 0; i < 50; i++) //Fill the deck's vector of cards with 50 cards
	{
	    int randomNum = rand() % 5;
		cardsVector->push_back(new Card(Card::types[randomNum],this, nullptr));
	}
}

Deck::Deck(const Deck &deck2) //copy constructor
{
	cardsVector = new vector<Card*>;

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

Card* Deck::draw()
{
	int randomIndex = rand() % (cardsVector->size()); //get a random index within the deck
	Card* tempCard = cardsVector->at(randomIndex);	  //store a temporary card to return at the end

	// cardsVector->erase(cardsVector->begin() + randomIndex); //erase the chosen random card

	return tempCard;
}

void Deck::add(Card* newCard)
{
	cardsVector->push_back(newCard);
}

//////// HAND HAND HAND //////////

Hand::Hand(){} //default constructor

// Hand::Hand(Player *player)
// {
// 	cardsVector = new vector<Card>;
// 	owner = player;
// }

Hand::Hand(const Hand &hand2) //copy constructor
{
	owner = hand2.owner;
	cardsVector = hand2.cardsVector;

	for (int i = 0; i < hand2.cardsVector.size(); i++)
	{
		cardsVector.push_back(hand2.cardsVector.at(i));
	}
}

ostream &operator<<(ostream &out, const Hand &h) //stream insertion
{
	out << h.owner->getName() << "'s hand" << endl;
	out << "List of cards in this hand: " << endl;

	for (int i = 0; i < h.cardsVector.size(); i++)
	{
		out << h.cardsVector.at(i);
	}
	out << "\n\n";
	return out;
}

void Hand::add(Card* newCard) //add a card
{
	cardsVector.push_back(newCard);
}

void Hand::playCard(int index, Deck deck)
{
	//owner->issueOrder(cardsVector->at(index).getType());
	deck.add(cardsVector.at(index));
	cardsVector.erase(cardsVector.begin() + index);
}

bool Hand::isEmpty()
{
	return cardsVector.empty();
}

vector<Card*> Hand::getCardsVector()
{
	return cardsVector;
}

Card* Hand::firstAirlift() {
    for(int i=0; i<this->getCardsVector().size();i++){
        if(this->getCardsVector()[i]->getType()=="airlift"){
            return this->getCardsVector()[i];
        }
    }
    return nullptr;
}

Card* Hand::firstBlockade() {
    for(int i=0; i<this->getCardsVector().size();i++){
        if(this->getCardsVector()[i]->getType()=="blockade"){
            return this->getCardsVector()[i];
        }
    }
    return nullptr;
}

Card* Hand::firstBomb()  {
    for(int i=0; i<this->getCardsVector().size();i++){
        if(this->getCardsVector()[i]->getType()=="bomb"){
            return this->getCardsVector()[i];
        }
    }
    return nullptr;
}

Card* Hand::firstDiplomacy()  {
    for(int i=0; i<this->getCardsVector().size();i++){
        if(this->getCardsVector()[i]->getType()=="diplomacy"){
            return this->getCardsVector()[i];
        }
    }
    return nullptr;
}

Card* Hand::firstReinforcement()  {
    for(int i=0; i<this->getCardsVector().size();i++){
        if(this->getCardsVector()[i]->getType()=="reinforcement"){
            return this->getCardsVector()[i];
        }
    }
    return nullptr;
}

Deck *Hand::getDeck() {
    return deck;
}
