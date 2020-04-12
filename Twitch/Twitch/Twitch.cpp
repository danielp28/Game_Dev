#include "Engine/engine.h"

#include <iostream>
using namespace std;

int main() {
	cout << "Hello world" << endl;

	Engine engine;
	while (true) {
		engine.Update();
		engine.Render();
	}
	
	
	
	return 0;
}