#ifndef GLOBALCONFIG
#define GLBOALCONFIG

const unsigned long CyclesPerSec = 80000000; 					// number of cycles per second
const double GameDiffTimes[] = {1.5, 1.0, 0.5};				// array for time factors for each difficulty
static short int GameDiff = 0;												// current index for the GameDiffTimes
static short int score = 0; 													// game score
const double HoldDelay = 1.75;												// time factor between two counts

#endif