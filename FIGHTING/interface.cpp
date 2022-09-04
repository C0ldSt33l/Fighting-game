#include"interface.h"

void initInterface(Interface& interface) {

	interface.hp1.y = interface.hp2.y = WINDOW_HEIGHT / 10;
	interface.hp1.w = interface.hp2.w = WINDOW_WIDTH / 5;
	interface.hp1.h = interface.hp2.h = WINDOW_HEIGHT / 20;
	
	
	interface.meter1.y = interface.meter2.y = WINDOW_HEIGHT / 10 * 9;
	interface.meter1.w = interface.meter2.w = WINDOW_WIDTH / 3;
	interface.meter1.h = interface.meter2.h = WINDOW_HEIGHT / 20;
}

void deInitInterface(Interface& interface) {


}

void updateInterface(Interface& interface) {


}

void drawInterface(const Interface& interface) {


}