#ifndef OSCARSHARED_H
#define OSCARSHARED_H

class configurator;
class FAIRRootWriter;
class EventBuffer;
class Monitor;

#include <vector>

// Global variables

extern std::vector<unsigned int>  *gBufferVector;
extern std::vector<unsigned int>  *gStartEvent; /*vettore contenente la word di inizio evento per ogni evento*/
extern EventBuffer                *gEventManager;
extern configurator               *gLayout;


#endif