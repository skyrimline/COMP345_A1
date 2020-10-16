#include <iostream>
#include <vector>
#include "Map.h"
using namespace std;

int main() {
    //tests on territory
    Territory* t1=new Territory("Territory0");
    cout<<t1->getName()<<endl;
    t1->setName("Territory1");
    cout<<t1->getName()<<endl;
    //tests on neighbour
    cout<<"----------"<<endl;
    Territory* t2=new Territory("Territory2");
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
    cout<<c2->getName()<<endl;
    Territory* t3=new Territory("Territory3",c1);
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
    cout<<"----------"<<endl;
    if(c2->isConnectedGraph()){
        cout<<"true"<<endl;
    }
    else{
        cout<<"false"<<endl;
    }
    cout<<"----------"<<endl;
    t3->addNeighbour(t2);
    if(m->isConnectedGraph()){
        cout<<"true"<<endl;
    }
    else{
        cout<<"false"<<endl;
    }
    cout<<"----------"<<endl;
    if(m->validate()){
        cout<<"true"<<endl;
    }
    else{
        cout<<"false"<<endl;
    }
}