#ifndef OCALIBRATION_H
#define OCALIBRATION_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <Rtypes.h>
#include <math.h>
#include <TROOT.h>

#include <OSOSCARPhysicalParticle.h>

class OSOSCARCalibration
{
public:
  OSOSCARCalibration(const char * det_name, int num_telescopes);
  ~OSOSCARCalibration();
  
  int Init(const char * file_calib);
  void PerformEventCalibration(std::vector<OSOSCARPhysicalParticle> *Particle);
  
private:
  std::string fName;
  int fNumTelescopes;
  int fNumStrips;
  int fNumPads;
  double **fStripIntercept;
  double **fStripSlope;
  double **fPadIntercept;
  double **fPadSlope;
  double **fStripThickness;
  double **fPadThickness;    
} ;

#endif