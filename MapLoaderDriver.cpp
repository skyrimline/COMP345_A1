#include "MapLoader.h"
#include <iostream>

using namespace std;

int main() {
	cout << "Hello" << endl;
	cout << "Map is Loading......" << endl;
	MapLoader Loader;
    Map map1 = Loader.readMap("E:\\Clion\\Comp345\\Map\\canada.map");
	Map map2 = Loader.readMap("E:\\Clion\\Comp345\\Map\\artic.map");
	Map map3 = Loader.readMap("E:\\Clion\\Comp345\\Map\\solar.map");
    Map map4 = Loader.readMap("E:\\Clion\\Comp345\\Map\\austria-hungary.map");

	return 0;
}
