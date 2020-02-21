enum exampleStates {
	exampleIDLE,
	start,
	enterDigit1,
	enterDigit2,
	enterDigit3,
	enterDigit4,
	enterDigit5,
	win };

extern bool example(void); 
extern void exampleInit();
extern void exampleSetState(unsigned char);
extern unsigned char exampleGetState(void);
