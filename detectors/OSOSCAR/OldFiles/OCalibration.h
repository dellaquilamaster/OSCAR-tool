#ifndef OCALIBRATION_H
#define OCALIBRATION_H

#include <fstream>
#include <vector>
#include <Rtypes.h>

#include "OscarPhysicalParticle.h"

class OCalibration
{
public:
  OCalibration();
  ~OCalibration();
  
  int Init(const char * file_calib);
  void PerformEventCalibration(std::vector<OscarPhysicalParticle> *Particle);
  
private:
  Double_t * a_coeff_strip;
  Double_t * b_coeff_strip;
  Double_t * a_coeff_pad;
  Double_t * b_coeff_pad;
  Double_t * thickness_strip;
  Double_t * thickness_pad;
  Int_t      NumStrips;
  Int_t      NumPads;
    
} ;

#endif