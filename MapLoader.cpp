#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

Map MapLoader::readMap(string mapFile) {
		try {
			Map map;
			ifstream dom(mapFile);
			vector <string> continentsList;
			vector<string> territoryList;
			string L;
			//moving to continents
			while (getline(dom, L) && L != "[continents]\r") {}
			while (getline(dom, L) && L != "\r") {
				string continent = L.substr(0, L.find(" "));
				continentsList.push_back(continent);
				map.addContinent(new Continent(continent));
			}
			//moving to Territory
			while (getline(dom, L) && L != "[contries]\r") {}
			while (getline(dom, L) && L != "\r") {
				stringstream st(L);
				string w;
				vector<string> LSplit;
				while (getline(st, w, ' ')) {
					LSplit.push_back(w);
				}
				territoryList.push_back(LSplit[1]);
				int continentIndex = stoi(LSplit[2]) - 1;
				map.addTerritory(new Territory(LSplit[1], map.getContinentByIndex(continentIndex, continentsList)));
			}
			//moving to Borders
			while (getline(dom, L) && L != "[borders]\r") {}
			while (getline(dom, L) && L != "\r") {
				stringstream st(L);
				string w;
				vector<string> LSplit;
				while (getline(st, w, ' ')) {
					LSplit.push_back(w);
				}
				int territoryIndex = stoi(LSplit[0])-1;
				for (int i = 1; i < LSplit.size(); i++) {
					int indexToAdd = stoi(LSplit[i]) - 1;
					map.getTerritoryByIndex(territoryIndex, territoryList)->addNeighbour(map.getTerritoryByIndex(indexToAdd, territoryList));
				}
			}
			if (map.validate()) {
				return map;
			}
			else {
				cerr << "This map is invalid!" << endl;
				return 0;
			}
				

		}
		catch (...) {
			cerr << "This map file contains some errors." << endl;
		}
	
}
