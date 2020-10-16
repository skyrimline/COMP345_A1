#include "MapLoader.h"
#include <iostream>

using namespace std;

int main() {
	cout << "Hello" << endl;
	cout << "Map is Loading......" << endl;
	MapLoader Loader;
    Map map1 = Loader.readMap("C:\\Users\\admin\\Desktop\\Comp\\Comp345\\Assignment1\\Map\\canada.map");
	Map map2 = Loader.readMap("C:\\Users\\admin\\Desktop\\Comp\\Comp345\\Assignment1\\Map\\artic.map");
	Map map3 = Loader.readMap("C:\\Users\\admin\\Desktop\\Comp\\Comp345\\Assignment1\\Map\\solar.map");
	cout<<"For the invalid map..."<< endl;
    Map map4 = Loader.readMap("C:\\Users\\admin\\Desktop\\Comp\\Comp345\\Assignment1\\Map\\austria-hungary.map");

	return 0;
}
