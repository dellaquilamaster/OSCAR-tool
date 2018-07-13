#ifndef OANALYZER_H
#define OANALYZER_H

#include <vector>

#include "TRootEvent.h"
#include "EventoBruto.h"
#include "OTracks.h"
#include "OIdentification.h"
#include "OCalibration.h"
#include "OGeometry.h"
#include "OscarPhysicalParticle.h"

class OAnalyzer
{
public:
  OAnalyzer(std::vector<EventoBruto>& Buffer, TRootDefine * ManageEvent, OGeometry * GeomModule, OIdentification* IdModule, OCalibration* CalibModule);
  ~OAnalyzer() {}
  
  void RunDataAnalysis();
  void AnalyzeEvent(Int_t num_evt);
  
private:
  OTracks                  FindTracks(Int_t num_evt);
  void                     FillParticleTracks(OTracks IdTracks, Int_t num_evt);  
  std::vector<EventoBruto> EvtBuffer;
  std::vector<OscarPhysicalParticle> Particle;
  TRootDefine              *OscarEvt;
  TRootEvent               *PhysicalEvent;
  Int_t                    num_good_events;
  OIdentification          *OscarIdentificator;
  OCalibration             *OscarCalibrator;
  OGeometry                *OscarGeometry;
  
} ;

#endif