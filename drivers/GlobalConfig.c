#include "../headers/GlobalConfig.h"

const unsigned long CyclesPerSec = 80000000;
const double GameDiffTimes[] = {1.5, 1.0, 0.5};
const double HoldDelay = 1.75;

short int GameDiff = 0;
short int score = 0;
short int attempt = 0;

short int LDR_Threshold = 1000;
volatile unsigned int isLight = 0;

/* At vcc = 3.3v, Resistor = 10 Kohm, 
	 By voltage divider, vout = 3.3 * (2/(2 + 10)) = 0.55v (where 2 is the LDR resistance at bright light)
   ADC = (vout / vref) * 4095 = 682 (where vref = 3.3v)
Same operations at darkness will produce: 
	vout = 3v
	ADC = 3723
So, a value between both ADC values is choosen
*/