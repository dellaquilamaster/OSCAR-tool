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

//OSCAR Constants
extern const int NUM_STRIPS_OSCAR;
extern const int NUM_PADS_OSCAR;
extern const int NUM_MAX_PARTICLES_PER_OSCAR;

extern char file_raw_output_path[];   
extern char file_unpacker_output_path[];   
extern char file_mapper_output_path[];    
extern char file_daqconfig_name[];
extern char file_mapping_name[];
extern char experiment_name[];
extern char experiment_title[];
extern const char *run_to_analyze;


#endif