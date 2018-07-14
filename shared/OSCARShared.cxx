#include <OSCARShared.h>

const int NUM_STRIPS_OSCAR=16;
const int NUM_PADS_OSCAR=16;
const int NUM_MAX_PARTICLES_PER_OSCAR=4;

OSRunInfo * gRunInfo;

std::vector<unsigned int>  *gBufferVector=0;
std::vector<unsigned int>  *gStartEvent=0; /*vettore contenente la word di inizio evento per ogni evento*/
EventBuffer                *gEventManager=0;
configurator               *gLayout=0;