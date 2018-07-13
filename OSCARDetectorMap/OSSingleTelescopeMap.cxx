#include <OSSingleTelescopeMap.h>

//________________________________________________
OSSingleTelescopeMap::OSSingleTelescopeMap(const char * name) : OSDetectorMap(name)
{
  Clear();
}

//________________________________________________
OSSingleTelescopeMap::~OSSingleTelescopeMap()
{}

//________________________________________________
void OSSingleTelescopeMap::Clear()
{
  fEnergyFirstModule=-1;
  fEnergyFirstChannel=-1;
  fTimeFirstModule=-1;
  fTimeFirstChannel=-1;
  fEnergySecondModule=-1;
  fEnergySecondChannel=-1;
  fTimeSecondModule=-1;
  fTimeSecondChannel=-1;
}

//________________________________________________
int OSSingleTelescopeMap::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string DetectorToSet;
  std::string ModuleName;
  std::string ModuleChannelString;
  LineStream>>DetectorName>>ChName>>DetectorToSet>>ModuleName>>ModuleChannelString;
  if(DetectorName.compare(fName)!=0) return 0;

  DetectorToSet.assign(DetectorToSet.substr(DetectorToSet.find("detector=\"")+10,DetectorToSet.find_last_of("\"")-(DetectorToSet.find("detector=\"")+10)));
  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));
  ModuleChannelString.assign(ModuleChannelString.substr(ModuleChannelString.find("channel=\"")+9,ModuleChannelString.find_last_of("\"")-(ModuleChannelString.find("channel=\"")+9)));

  int DetectorNumber=std::stoi(DetectorToSet); //WARNING: 0 is first stage 1 is second stage
  int ModuleNumber=std::stoi(ModuleName);
  int ModuleChannel=std::stoi(ModuleChannelString);

  if(ChName.compare("ENERGY")==0) {
    if(DetectorNumber==0) {
      fEnergyFirstModule=ModuleNumber;
      fEnergyFirstChannel=ModuleChannel;
    } else if(DetectorNumber==1) {
      fEnergySecondModule=ModuleNumber;
      fEnergySecondChannel=ModuleChannel;
    }
  } else if(ChName.compare("TIME")==0) {
    if(DetectorNumber==0) {
      fTimeFirstModule=ModuleNumber;
      fTimeFirstChannel=ModuleChannel;
    } else if(DetectorNumber==1) {
      fTimeSecondModule=ModuleNumber;
      fTimeSecondChannel=ModuleChannel;
    }
  }

  return 1;
}