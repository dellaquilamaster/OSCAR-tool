#include <OSOSCARMap.h>

//________________________________________________
OSOSCARMap::OSOSCARMap(const char * name, int num_telescopes) : OSDetectorMap(name),
fNumTelescopes(num_telescopes),
fStripEnergyModule(new int*[fNumTelescopes]),
fStripEnergyChannel(new int*[fNumTelescopes]),
fStripTimeModule(new int*[fNumTelescopes]),
fStripTimeChannel(new int*[fNumTelescopes]),
fPadEnergyModule(new int*[fNumTelescopes]),
fPadEnergyChannel(new int*[fNumTelescopes]),
fPadTimeModule(new int*[fNumTelescopes]),
fPadTimeChannel(new int*[fNumTelescopes])
{
  for(int i=0; i<fNumTelescopes; i++) {
    fStripEnergyModule[i] = new int[NUM_STRIPS_OSCAR];
    fStripEnergyChannel[i] = new int[NUM_STRIPS_OSCAR];
    fStripTimeModule[i] = new int[NUM_STRIPS_OSCAR];
    fStripTimeChannel[i] = new int[NUM_STRIPS_OSCAR];
    fPadEnergyModule[i] = new int[NUM_PADS_OSCAR];
    fPadEnergyChannel[i] = new int[NUM_PADS_OSCAR];
    fPadTimeModule[i] = new int[NUM_PADS_OSCAR];
    fPadTimeChannel[i] = new int[NUM_PADS_OSCAR];
  }
  Clear();
}

//________________________________________________
OSOSCARMap::~OSOSCARMap()
{
  for(int i=0; i<fNumTelescopes; i++) {
    delete [] fStripEnergyModule[i];
    delete [] fStripEnergyChannel[i];
    delete [] fStripTimeModule[i];
    delete [] fStripTimeChannel[i];
    delete [] fPadEnergyModule[i];
    delete [] fPadEnergyChannel[i];
    delete [] fPadTimeModule[i];
    delete [] fPadTimeChannel[i];
  }
  delete [] fStripEnergyModule;
  delete [] fStripEnergyChannel;
  delete [] fStripTimeModule;
  delete [] fStripTimeChannel;
  delete [] fPadEnergyModule;
  delete [] fPadEnergyChannel;
  delete [] fPadTimeModule;
  delete [] fPadTimeChannel;
}

//________________________________________________
void OSOSCARMap::Clear()
{
  for(int i=0; i<fNumTelescopes; i++) {
    for(int j=0; j<NUM_STRIPS_OSCAR; j++) {
      fStripEnergyModule[i][j]=-1;
      fStripEnergyChannel[i][j]=-1;
      fStripTimeModule[i][j]=-1;
      fStripTimeChannel[i][j]=-1;
    }
    for(int j=0; j<NUM_PADS_OSCAR; j++) {
      fPadEnergyModule[i][j]=-1;
      fPadEnergyChannel[i][j]=-1;
      fPadTimeModule[i][j]=-1;
      fPadTimeChannel[i][j]=-1;
    }
  }
}

//________________________________________________
int OSOSCARMap::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string TelescopeToSet;
  std::string DetectorToSet;
  std::string ModuleName;
  std::string ModuleChannelString;
  LineStream>>DetectorName>>ChName>>TelescopeToSet>>DetectorToSet>>ModuleName>>ModuleChannelString;
  if(DetectorName.compare(fName)!=0) return 0;

  TelescopeToSet.assign(TelescopeToSet.substr(TelescopeToSet.find("telescope=\"")+11,TelescopeToSet.find_last_of("\"")-(TelescopeToSet.find("telescope=\"")+11)));
  DetectorToSet.assign(DetectorToSet.substr(DetectorToSet.find("detector=\"")+10,DetectorToSet.find_last_of("\"")-(DetectorToSet.find("detector=\"")+10)));
  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));
  ModuleChannelString.assign(ModuleChannelString.substr(ModuleChannelString.find("channel=\"")+9,ModuleChannelString.find_last_of("\"")-(ModuleChannelString.find("channel=\"")+9)));

  int TelescopeNumber=std::stoi(TelescopeToSet);
  int DetectorNumber=std::stoi(DetectorToSet)-1; //WARNING: OSCAR detectors start from 1 but the array starts from 0.
  int ModuleNumber=std::stoi(ModuleName);
  int ModuleChannel=std::stoi(ModuleChannelString);

  if(ChName.compare("STRIPENERGY")==0) {
    fStripEnergyModule[TelescopeNumber][DetectorNumber]=ModuleNumber;
    fStripEnergyChannel[TelescopeNumber][DetectorNumber]=ModuleChannel;
  } else if(ChName.compare("PADENERGY")==0) {
    fPadEnergyModule[TelescopeNumber][DetectorNumber]=ModuleNumber;
    fPadEnergyChannel[TelescopeNumber][DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("STRIPTIME")==0) {
    fStripTimeModule[TelescopeNumber][DetectorNumber]=ModuleNumber;
    fStripTimeChannel[TelescopeNumber][DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("PADTIME")==0) {
    fPadTimeModule[TelescopeNumber][DetectorNumber]=ModuleNumber;
    fPadTimeChannel[TelescopeNumber][DetectorNumber]=ModuleChannel;
  }

  return 1;
}