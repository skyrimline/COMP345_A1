#ifndef MapLoader_H
#define MapLoader_H
#include "Map.h"
#include <iostream>
using namespace std;

class MapLoader
{
public:
	static Map readMap(string mapFile);
};

#endif //MapLoader_H