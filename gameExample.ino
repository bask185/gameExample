#include "src/basics/timers.h"
#include "src/basics/io.h"
#include "roundRobinTasks.h"
#include "example.h"

void setup() {
	initTimers();
	initIO();
	Serial.begin(115200);
	exampleInit();
}

void loop() {
	processRoundRobinTasks();

	example();
}