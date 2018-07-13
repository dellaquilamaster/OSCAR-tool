#ifndef OSANALYZER_H
#define OSANALYZER_H

#include <vector>

#include <OSOSCARTracks.h>
#include <OSOSCARIdentification.h>
#include <OSOSCARCalibration.h>
#include <OSOSCARGeometry.h>
#include <OSOSCARPhysicalParticle.h>
#include <OSOSCARTelescope.h>

#include <OSCARShared.h>

class OSOSCARAnalyzer
{
public:
  OSOSCARAnalyzer(int);
  ~OSOSCARAnalyzer();
  
  std::vector<OSOSCARPhysicalParticle> * AnalyzeEvent(OSOSCARTelescope **);
  
private:
  int fNumTelescopes;
  
  OSOSCARTracks            FindTracks(OSOSCARTelescope *);
  void                     FillParticleTracks(OSOSCARTracks *, OSOSCARTelescope *, int); 
  
  std::vector<OSOSCARPhysicalParticle> * fParticle;
  OSOSCARIdentification    *fOscarIdentificator;
  OSOSCARCalibration       *fOscarCalibrator;
  OSOSCARGeometry          *fOscarGeometry;
  
  bool fIdentificationLoaded;
  bool fCalibrationLoaded;
  bool fGeometryLoaded;
} ;

#endif