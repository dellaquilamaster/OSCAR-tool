#ifndef OSSINGLETELESCOPECALIBRATION_H
#define OSSINGLETELESCOPECALIBRATION_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <Rtypes.h>
#include <math.h>
#include <TROOT.h>

#include <OSSingleTelescopeRootEvent.h>

class OSSingleTelescopeCalibration
{
public :
  OSSingleTelescopeCalibration(const char *);
  ~OSSingleTelescopeCalibration();
  
  int LoadCalibration(const char *);
  
  void PerformEventCalibration(OSSingleTelescopeData *);
  
  double GetEnergyFirst(double ch) const;
  double GetEnergySecond(double ch) const;
  
  const char * GetDetectorName() const;
  
private :
  std::string fName;
  bool fCalibrationLoaded;
  double fInterceptFirst;
  double fSlopeFirst;
  double fInterceptSecond;
  double fSlopeSecond;
  
};

#endif