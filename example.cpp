// HEADER FILES
#include <Arduino.h>
#include "example.h"
#include "src/basics/timers.h"
#include "src/basics/io.h"
#include <EEPROM.h>

// MACROS
#define stateFunction(x) static bool x##F(void)
#define entryState if(runOnce) 
#define onState runOnce = false; if(!runOnce)
#define exitState if(!exitFlag) return false; else
#define State(x) break; case x: if(x##F())
#define STATE_MACHINE_BEGIN if(!enabled) { \
	if(!exampleT) enabled = true; } \
else switch(state){\
	default: Serial.println("unknown state executed, state is idle now"); state = exampleIDLE; case exampleIDLE: return true;
#define STATE_MACHINE_END break;}return false;


#define beginState start
#ifndef beginState
#error beginState not yet defined
#endif

// VARIABLES
static unsigned char state;
static bool enabled = true, runOnce = true, exitFlag = false;

static byte digit, serialByte, timeOutTime = 25, randoMizer;
static bool error;
enum errorReasons {
	none = 0,
	timeOut,
	wrongNumber
};

// FUNCTIONS
extern void exampleInit(void) { 
	state = beginState; 
	randoMizer = EEPROM.read(0x01); 
	randomSeed(randoMizer);
}
extern byte exampleGetState(void) { return state;}
extern void exampleSetState(unsigned char _state) { state = _state; runOnce = true; }
static void nextState(unsigned char _state, unsigned char _interval) {
	runOnce = true;
	exitFlag = false;
	if(_interval) {
		enabled = false;
		exampleT = _interval; } 
	state = _state; }

static void emptySerialBuffer() {
	while(Serial.available()) {
		Serial.read();
	}
}

static void printError(byte error) {
	switch(error) {
		case none:			Serial.println("next level in 1 second"); break;
		case timeOut:		Serial.println("you were to slow"); break;
		case wrongNumber:	Serial.println("you entered the wrong digit"); break;
	}
}

// STATE FUNCTIONS
stateFunction(start) {
	entryState {
		timeOutTime += 5; // make it easier
		Serial.println("Press any key to start the game");
		emptySerialBuffer();
	}
	onState {
		if(Serial.available()) {
			exitFlag = true; 
		}
	}
	exitState {
		Serial.println("starting game in 2 seconds");
		randoMizer++;	// uses the eeprom for random seed
		EEPROM.write(0x01, randoMizer);
		return true; } }


stateFunction(enterDigit1) {
	entryState {
		digit = random('0', '9');
		Serial.print("enter ");	Serial.println(digit);
		exampleT = timeOutTime; 
		emptySerialBuffer();
	}
	onState {
		if(Serial.available()) {
			serialByte = Serial.read();

			if(digit == serialByte) error = none;
			else					error = wrongNumber;
		
			exitFlag = true;
		}
		else if(!exampleT) {
			error = timeOut;
			exitFlag = true; 
		}
	}
	exitState {
		printError(error);
		return true; 
	} 
}


stateFunction(enterDigit2) {
	entryState {
		digit = random('0', '9');
		Serial.print("enter ");	Serial.println(digit);
		exampleT = timeOutTime; 
		emptySerialBuffer();
	}
	onState {
		if(Serial.available()) {
			serialByte = Serial.read();

			if(digit == serialByte) error = none;
			else					error = wrongNumber;
		
			exitFlag = true;
		}
		else if(!exampleT) {
			error = timeOut;
			exitFlag = true; 
		}
	}
	exitState {
		printError(error);
		return true; 
	} 
}


stateFunction(enterDigit3) {
	entryState {
		digit = random('0', '9');
		Serial.print("enter ");	Serial.println(digit);
		exampleT = timeOutTime; 
		emptySerialBuffer();
	}
	onState {
		if(Serial.available()) {
			serialByte = Serial.read();

			if(digit == serialByte) error = none;
			else					error = wrongNumber;
		
			exitFlag = true;
		}
		else if(!exampleT) {
			error = timeOut;
			exitFlag = true; 
		}
	}
	exitState {
		printError(error);
		return true; 
	} 
}


stateFunction(enterDigit4) {
	entryState {
		digit = random('0', '9');
		Serial.print("enter ");	Serial.println(digit);
		exampleT = timeOutTime; 
		emptySerialBuffer();
	}
	onState {
		if(Serial.available()) {
			serialByte = Serial.read();

			if(digit == serialByte) error = none;
			else					error = wrongNumber;
		
			exitFlag = true;
		}
		else if(!exampleT) {
			error = timeOut;
			exitFlag = true; 
		}
	}
	exitState {
		printError(error);
		return true; 
	} 
}


stateFunction(enterDigit5) {
	entryState {
		digit = random('0', '9');
		Serial.print("enter ");	Serial.println(digit);
		exampleT = timeOutTime; 
		emptySerialBuffer();
	}
	onState {
		if(Serial.available()) {
			serialByte = Serial.read();

			if(digit == serialByte) error = none;
			else					error = wrongNumber;
		
			exitFlag = true;
		}
		else if(!exampleT) {
			error = timeOut;
			exitFlag = true; 
		}
	}
	exitState {
		printError(error);
		return true; 
	} 
}


stateFunction(win) {
	entryState {
		Serial.println("you won the game! Press any key to continu");
		emptySerialBuffer();
	}
	onState {
		if(Serial.available()) {
			exitFlag = true; 
		}
	}
	exitState {
		Serial.println("game restarting in 2.5 seconds");
		timeOutTime -= 10; // every time you play it gets harder
		return true; 
	} 
}


// STATE MACHINE
extern bool example(void) {
	STATE_MACHINE_BEGIN

	State(start) {
		nextState(enterDigit1, 200); }

	State(enterDigit1) {
		if(!error) nextState(enterDigit2, 100);
		else       nextState(start, 0); }

	State(enterDigit2) {
		if(!error) nextState(enterDigit3, 100);
		else       nextState(start, 0); }

	State(enterDigit3) {
		if(!error) nextState(enterDigit4, 100);
		else       nextState(start, 0); }

	State(enterDigit4) {
		if(!error) nextState(enterDigit5, 100);
		else       nextState(start, 0); }

	State(enterDigit5) {
		if(!error) nextState(start, 100);
		else       nextState(win, 0); }

	State(win) {
		nextState(start, 250); }

	STATE_MACHINE_END
}
