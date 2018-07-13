#include <OSCARShared.h>

const int NUM_STRIPS_OSCAR=16;
const int NUM_PADS_OSCAR=16;
const int NUM_MAX_PARTICLES_PER_OSCAR=4;

char file_raw_output_path[] ="/home/daniele/Desktop/TAU-DEU/RAWDATA/";
char file_unpacker_output_path[] ="/home/daniele/Desktop/TAU-DEU/FAIRUnpacker_rootfiles/";
char file_mapper_output_path[] ="/home/daniele/Desktop/TAU-DEU/OSCARMapper_rootfiles/";
char file_daqconfig_name[] ="input-files/DAQConfig_TAUDEU_20180711.daq";
char file_mapping_name[] ="input-files/Mapping_TAUDEU_20180711.map";
char file_oscargeometry_name[] ="";
char file_oscaridentification_name[] ="";
char file_oscarcalibration_name[] ="";
char experiment_name[]="TAUDEU";
char experiment_title[]="TAU-DEU experiment at INFN-LNL";
const char *run_to_analyze;

std::vector<unsigned int>  *gBufferVector=0;
std::vector<unsigned int>  *gStartEvent=0; /*vettore contenente la word di inizio evento per ogni evento*/
EventBuffer                *gEventManager=0;
configurator               *gLayout=0;