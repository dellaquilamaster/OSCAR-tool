#ifndef OIDENTIFICATION_H
#define OIDENTIFICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <TCutG.h>
#include <vector>

#include "TOscarCutG.h"
#include "TRootEvent.h"
#include "ParticleType.h"
#include "OscarPhysicalParticle.h"

class OIdentification
{
public:
  OIdentification();
  ~OIdentification();
  
  Int_t Init (const char * cut_file);
  void  PerformEventIdentification(std::vector<OscarPhysicalParticle> *Particle);
  
private:
  TOscarCutG **  IdStructure; /*matrice di TOscarCutG, ognuna di tali strutture contiene un particolare incrocio di strip e pad*/
  ParticleType * PhysParticle;
  Int_t          NumPads;
  Int_t          NumStrips;
} ;

#endif
