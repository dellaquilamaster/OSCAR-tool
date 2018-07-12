#include <OSCARShared.h>

std::vector<unsigned int>  *gBufferVector=0;
std::vector<unsigned int>  *gStartEvent=0; /*vettore contenente la word di inizio evento per ogni evento*/
EventBuffer                *gEventManager=0;
configurator               *gLayout=0;
