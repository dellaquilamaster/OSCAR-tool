#include <OSRunInfo.h>

//____________________________________________________
OSRunInfo::OSRunInfo()
{}

//____________________________________________________
OSRunInfo::~OSRunInfo()
{}

//____________________________________________________
int OSRunInfo::LoadRunConfiguration(const char * run_name, const char * config_file)
{
std::ifstream FileIn(config_file);
  
  if(!FileIn.is_open()) {
    return -1;
  }

  int NRead=0;
  
  fRunNumber.assign(run_name);

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("set ")!=std::string::npos) {   
      if(LineReadCommentLess.find("--run=")!=std::string::npos) {
        NRead+=ParseRunSetLine(LineReadCommentLess); 
      } else {
        NRead+=ParseExperimentSetLine(LineReadCommentLess); 
      }
    }
  }
  
  return NRead;
}

//____________________________________________________
int OSRunInfo::ParseExperimentSetLine(std::string line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse.substr(line_to_parse.find("set ")+4));
  std::istringstream LineStream(LineReadCommentLess);
  
  std::string WhatToSet;
  std::string ValueToSet;
  
  LineStream>>WhatToSet>>ValueToSet;
  ValueToSet.assign(ValueToSet.substr(ValueToSet.find("\"")+1, ValueToSet.find_last_of("\"")-(ValueToSet.find("\"")+1)));
  
  if(WhatToSet.compare("OSCAR_DIR")==0) {
    fProgramPath.assign(ValueToSet);
    return 1;
  } else if(WhatToSet.compare("RAWDATA_FILE_PATH")==0) {
    fRawDataPath.assign(ValueToSet);
    return 1;
  } else if(WhatToSet.compare("FAURUNPACKER_ROOT_FILE_PATH")==0) {
    fFAIRUnpackerDataPath.assign(ValueToSet);
    return 1;
  } else if(WhatToSet.compare("OSCARMAPPER_ROOT_FILE_PATH")==0) {
    fOSCARMapperDataPath.assign(ValueToSet);
    return 1;
  } else if(WhatToSet.compare("EXPERIMENT_NAME")==0) {
    fExperimentName.assign(ValueToSet);
    return 1;
  } else if(WhatToSet.compare("EXPERIMENT_TITLE")==0) {
    fExperimentTitle.assign(ValueToSet);
    return 1;
  }
  
  return 0;
}

//____________________________________________________
int OSRunInfo::ParseRunSetLine(std::string line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse.substr(line_to_parse.find("set ")+4));
  std::istringstream LineStream(LineReadCommentLess);
  
  std::string ValueToSet;
  std::string Option;
  std::string ValueRead;
  
  LineStream>>ValueToSet;
  
  bool RunFound=false;
  
  while(LineStream>>Option && Option.find("--")!=std::string::npos) {
    if(Option.find("--run=")!=std::string::npos) {
      Option.assign(Option.substr(Option.find("--run=")+6));
      std::istringstream LineRunStream(Option);
      if(Option.find(",")!=std::string::npos) {
        std::string RunToInclude;
        while(std::getline(LineRunStream, RunToInclude, ',')) {
          if(fRunNumber.compare(RunToInclude)==0) RunFound=true;
        }
      }
      if(Option.find("-")!=std::string::npos) {
        std::string StartRun;
        std::string StopRun;
        std::getline(LineRunStream, StartRun, '-');
        std::getline(LineRunStream, StopRun, '-');
        if(fRunNumber.compare(StartRun)>=0 && fRunNumber.compare(StopRun)<=0) RunFound=true;
      }
    } else if (Option.find("--exclude=")!=std::string::npos) {
        std::istringstream LineExcludeStream(Option.substr(Option.find("--exclude=")+10));
        std::string RunToExclude;
        while(std::getline(LineExcludeStream, RunToExclude, ',')) {
          if(fRunNumber.compare(RunToExclude)==0) return 0; //this run is excluded
        }
      }
    }

  if(RunFound) {
    ValueRead.assign(LineReadCommentLess.substr(LineReadCommentLess.find("\"")+1,LineReadCommentLess.find_last_of("\"")-(LineReadCommentLess.find("\"")+1)));
  } else return 0;
  
  
  if(RunFound) {
    ValueRead.assign(ValueRead.substr(ValueRead.find("\"")+1, ValueRead.find_last_of("\"")-(ValueRead.find("\"")+1)));
    if(ValueToSet.compare("DAQ_CONFIG")==0) {
      fDAQConfigFileName.assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("PEDESTAL_VALUES")==0) {
      fPedestalFileName.assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("CHANNEL_MAPPING")==0) {
      fMappingFileName.assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("OSCAR_CALIBRATION")==0) {
      fOSCARCalibrationFileName.assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("OSCAR_IDENTIFICATION")==0) {
      fOSCARIdentificationFileName .assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("OSCAR_GEOMETRY")==0) {
      fOSCARIGeometryFileName.assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("SINGLETEL_CALIBRATION")==0) {
      fSingleTelescopeCalibrationFileName.assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("SINGLETEL_IDENTIFICATION")==0) {
      fSingleTelescopeIdentificationFileName.assign(ValueRead);
      return 1;
    } else if(ValueToSet.compare("SINGLETEL_GEOMETRY")==0) {
      fSingleTelescopeGeometryFileName.assign(ValueRead);
      return 1;
    }
  }
  
  return 0;
}