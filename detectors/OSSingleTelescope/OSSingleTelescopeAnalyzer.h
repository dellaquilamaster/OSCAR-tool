#ifndef OSSINGLETELESCOPEANALYZER_H
#define OSSINGLETELESCOPEANALYZER_H

#include <vector>

#include <OSSingleTelescopeIdentification.h>
#include <OSSingleTelescopeCalibration.h>
#include <OSSingleTelescopeGeometry.h>
#include <OSRunInfo.h>

#include <OSSingleTelescopeRootEvent.h>

#include <OSCARShared.h>

class OSSingleTelescopeAnalyzer
{
public:
  OSSingleTelescopeAnalyzer(const char *);
  ~OSSingleTelescopeAnalyzer();
  
  void AnalyzeEvent(OSSingleTelescopeData *);
  
private:
  std::string fName;
  
  OSSingleTelescopeIdentification    *fIdentificator;
  OSSingleTelescopeCalibration       *fCalibrator;
  OSSingleTelescopeGeometry          *fGeometry;
  
  bool fIdentificationLoaded;
  bool fCalibrationLoaded;
  bool fGeometryLoaded;
} ;

#endif