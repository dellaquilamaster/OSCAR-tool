#ifndef OSCARPHYSICALPARTICLE_H
#define OSCARPHYSICALPARTICLE_H

#include <Rtypes.h>

typedef struct OscarPhysicalParticle_
{
  Int_t A;
  Int_t Z;
  Double_t mass_uma;
  Int_t DE;
  Int_t Eres;
  Double_t DE_MeV;
  Double_t Eres_MeV;
  Double_t energy;
  Int_t numstrip;
  Int_t numpad;
  Double_t theta;
  Double_t phi;
  bool  identified;
  bool  stopped;
  
} OscarPhysicalParticle;

#endif