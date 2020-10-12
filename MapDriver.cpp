#include <iostream>
#include <vector>
#include "Map.h"
using namespace std;

int main() {
    //tests on territory
    Territory* t1=new Territory("abc");
    cout<<t1->getName()<<endl;
    t1->setName("cde");
    cout<<t1->getName()<<endl;
    //tests on neighbour
    cout<<"----------"<<endl;
    Territory* t2=new Territory("bcd");
    t1->addNeighbour(t2);
    vector<Territory*> neighbours1=t1->getNeighbours();
    vector<Territory*> neighbours2=t2->getNeighbours();
    for (int i=0; i<neighbours1.size(); i++){
        cout<<neighbours1[i]->getName()<<endl;
    }
    for (int i=0; i<neighbours2.size(); i++){
        cout<<neighbours2[i]->getName()<<endl;
    }
    //test on continent
    cout<<"----------"<<endl;
    Continent* c1=new Continent("Continent1");
    cout<<c1->getName()<<endl;
    Continent* c2=new Continent("Continent2");
    Territory* t3=new Territory("def",c1);
    t2->setContinent(c1);
    c2->addTerritory(t1);
    c1->print();
    c2->print();
    //test on map
    cout<<"----------"<<endl;
    Map* m=new Map();
    m->addContinent(c1);
    m->addContinent(c2);
    m->print();
}