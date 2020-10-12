#include "Cards.h"


int main()
{
    cout << "Hello World!\n";
    Deck deck1;

    cout << deck1;

    Hand hand1;

    cout << hand1;

    for (int i = 0; i < 5; i++)
    {
        hand1.add(deck1.draw());
    }

    cout << "\nafter drawing 5 cards" << endl;

    cout << hand1 << endl;

    while (!hand1.isEmpty())
    {
        hand1.playCard(0,deck1);
    }

    cout << hand1 << endl;


}