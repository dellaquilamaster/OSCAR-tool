#ifndef OIDENTIFICATION_H
#define OIDENTIFICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <TCutG.h>
#include <TFile.h>
#include <string.h>
#include <vector>

#include <TOscarCutG.h>
#include <OSOSCARParticleType.h>
#include <OSOSCARPhysicalParticle.h>

class OSOSCARIdentification
{
public:
  OSOSCARIdentification(const char *, int);
  ~OSOSCARIdentification();
  
  Int_t Init (const char * cut_file);
  void  PerformEventIdentification(std::vector<OSOSCARPhysicalParticle> *Particle);
  
private:
  std::string fName;
  int fNumTelescopes;
  int fNumStrips;
  int fNumPads;
  TOscarCutG *** IdStructure; /*matrice di TOscarCutG, ognuna di tali strutture contiene un particolare incrocio di strip e pad*/
  OSOSCARParticleType * PhysParticle;
} ;

#endif
