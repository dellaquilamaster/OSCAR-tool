#ifndef OSCARSHARED_H
#define OSCARSHARED_H

class configurator;
class FAIRRootWriter;
class EventBuffer;
class Monitor;
class OSRunInfo;

#include <vector>

// Global variables

extern std::vector<unsigned int>  *gBufferVector;
extern std::vector<unsigned int>  *gStartEvent; /*vettore contenente la word di inizio evento per ogni evento*/
extern EventBuffer                *gEventManager;
extern configurator               *gLayout;

extern OSRunInfo                  *gRunInfo;

//OSCAR Constants
extern const int NUM_STRIPS_OSCAR;
extern const int NUM_PADS_OSCAR;
extern const int NUM_MAX_PARTICLES_PER_OSCAR;


#endif