#ifndef OSRUNINFO_H
#define OSRUNINFO_H

#include <TString.h>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class OSRunInfo
{
public :
  OSRunInfo();
  ~OSRunInfo();
  
  int LoadRunConfiguration(const char *, const char *);
  
  const char * GetProgramPath() const {return fProgramPath.c_str();}
  const char * GetExperimentName() const {return fExperimentName.c_str();}
  const char * GetExperimentTitle() const {return fExperimentTitle.c_str();}
  const char * GetRunNumber() const {return fRunNumber.c_str();}
  const char * GetRawDataPath() const {return fRawDataPath.c_str();}
  const char * GetFAIRUnpackerDataPath() const {return fFAIRUnpackerDataPath.c_str();}
  const char * GetOSCARMapperDataPath() const {return fOSCARMapperDataPath.c_str();}
  
  const char * GetDAQConfigFileName() const {return fDAQConfigFileName.c_str();}
  const char * GetPedestalFileName() const {return fPedestalFileName.c_str();}
  const char * GetMappingFileName() const {return fMappingFileName.c_str();}
  const char * GetOSCARCalibrationFileName() const {return fOSCARCalibrationFileName.c_str();}
  const char * GetOSCARIdentificationFileName() const {return fOSCARIdentificationFileName.c_str();}
  const char * GetOSCARGeometryFileName() const {return fOSCARIGeometryFileName.c_str();}
  const char * GetSingleTelescopeCalibrationFileName() const {return fSingleTelescopeCalibrationFileName.c_str();}
  const char * GetSingleTelescopeIdentificationFileName() const {return fSingleTelescopeIdentificationFileName.c_str();}
  const char * GetSingleTelescopeGeometryFileName() const {return fSingleTelescopeGeometryFileName.c_str();}
  
private :
  std::string fProgramPath;
  std::string fExperimentName;
  std::string fExperimentTitle;
  std::string fRunNumber;
  std::string fRawDataPath;
  std::string fFAIRUnpackerDataPath;
  std::string fOSCARMapperDataPath;
  std::string fDAQConfigFileName;  
  std::string fPedestalFileName;  
  std::string fMappingFileName;  
  std::string fOSCARCalibrationFileName;  
  std::string fOSCARIdentificationFileName;  
  std::string fOSCARIGeometryFileName;  
  std::string fSingleTelescopeCalibrationFileName;  
  std::string fSingleTelescopeIdentificationFileName;  
  std::string fSingleTelescopeGeometryFileName;  
  
  int ParseExperimentSetLine(std::string);
  int ParseRunSetLine(std::string);
};

#endif