#ifndef OSCARPHYSICALPARTICLE_H
#define OSCARPHYSICALPARTICLE_H

#include <Rtypes.h>

typedef struct OSOSCARPhysicalParticle_
{
  Int_t numtel;
  Int_t A;
  Int_t Z;
  Double_t mass_uma;
  Int_t DE;
  Int_t Eres;
  Int_t timestrip;
  Int_t timepad;
  Double_t DE_MeV;
  Double_t Eres_MeV;
  Double_t energy;
  Int_t numstrip;
  Int_t numpad;
  Double_t theta;
  Double_t phi;
  bool  identified;
  bool  stopped;
  
} OSOSCARPhysicalParticle;

#endif