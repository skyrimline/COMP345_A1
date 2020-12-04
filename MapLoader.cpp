#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

Map * MapLoader::readMap(string mapFile) {
		try {
			Map* map=new Map();
			ifstream file(mapFile);
			vector <string> continentsList;
			vector<string> territoryList;
			string str;
			//moving to continents
			while (getline(file, str) && str != "[continents]") {}
			while (getline(file, str) && str != "") {
                stringstream st(str);
                string w;
                vector<string> LSplit;
                while (getline(st, w, ' ')) {
                    LSplit.push_back(w);
                }
                continentsList.push_back(LSplit[0]);
                int* bonus = new int(stoi(LSplit[1]));
                Continent* c=new Continent(LSplit[0], bonus);
                map->addContinent(c);
			}
			//moving to Territory
			while (getline(file, str) && str != "[countries]") {}
			while (getline(file, str) && str != "") {
				stringstream st(str);
				string w;
				vector<string> LSplit;
				while (getline(st, w, ' ')) {
					LSplit.push_back(w);
				}
				territoryList.push_back(LSplit[1]);
				int continentIndex = stoi(LSplit[2]) - 1;
				map->addTerritory(new Territory(LSplit[1], map->getContinents()[continentIndex], nullptr));
			}

			//moving to Borders
			while (getline(file, str) && str != "[borders]") {}
			while (getline(file, str) && str != "") {
				stringstream st(str);
				string w;
				vector<string> LSplit;
				while (getline(st, w, ' ')) {
					LSplit.push_back(w);
				}
				for (int i = 1; i < LSplit.size(); i++) {
					map->getTerritories()[stoi(LSplit[0]) - 1]->addNeighbour(map->getTerritories()[stoi(LSplit[i]) - 1]);
				}
			}
			if (map->validate()) {
			    map->print();
				return map;
			}
			else {
				cerr << "This map is invalid!" << endl;
				return nullptr;
			}
		}
		catch (...) {
			cerr << "This map file contains some errors." << endl;
		}
	
}

MapLoader::~MapLoader() {

}

MapLoader::MapLoader() {

}

ConquestFileReader::ConquestFileReader()
{
}

ConquestFileReader::~ConquestFileReader()
{
}

Map * ConquestFileReader::readConquestFile(string conquestFile)
{
	return nullptr;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader cfreader)
{
	con = cfreader;
	
}





conquestFile::conquestFile()
{
}

conquestFile::conquestFile(conquestFile * conFile)
{
}

conquestFile::~conquestFile()
{
}

vector<Continent*> conquestFile::getContinents()
{
	return vector<Continent*>();
}

vector<Territory*> conquestFile::getTerritories()
{
	return vector<Territory*>();
}

void conquestFile::addContinent(Continent * continent)
{
}

void conquestFile::addTerritory(Territory * territory)
{
}

void conquestFile::print()
{
}

bool conquestFile::isConnectedGraph()
{
	return false;
}

bool conquestFile::validate()
{
	return false;
}
