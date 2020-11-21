#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>

class Player;

using namespace std;

class Deck;
class Hand;

class Card
{
public:
	static const string types[];

	Card();												 //default constructor
	~Card();
	Card(string t);											 //constructor
    Card(string t, Deck* deck, Hand* hand);
    Card(const Card &card2);								 //copy constructor
	friend ostream &operator<<(ostream &out, const Card &c); //stream insertion operator
	string getType();
	void play();

private:
	string type;//The card's type
	Deck* deck;
	Hand* hand;
};

class Deck
{
public:
	Deck();													 //default constructor
	~Deck();
	Deck(const Deck &deck2);								 //copy constructor
	friend ostream &operator<<(ostream &out, const Deck &d); //stream insertion operator
	//Card getCardAt(int index);
	Card* draw();
	void add(Card* newCard);
	vector<Card*> getCards();

private:
	vector<Card*> *cardsVector;
};

class Hand
{
public:
	Hand();													 //constructor
	~Hand();
	Hand(Player*, Deck*);
	Hand(const Hand &hand2);								 //copy constructor
	friend ostream &operator<<(ostream &out, const Hand &h); //stream insertion operator
	void add(Card* newCard);
	void playCard(int index, Deck deck);
	bool isEmpty();
	vector<Card*> getCardsVector();
    Card* firstAirlift();
    Card* firstBlockade();
    Card* firstReinforcement();
    Card* firstBomb();
    Card* firstDiplomacy();
    Deck* getDeck();

private:
	Player *owner;
	vector<Card*> cardsVector;
	Deck* deck;
};
