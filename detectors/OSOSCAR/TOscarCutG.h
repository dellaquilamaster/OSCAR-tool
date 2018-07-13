#ifndef TOSCARCUTG_H
#define TOSCARCUTG_H

#include <stdlib.h>
#include <TCutG.h>

typedef struct TOscarCutG_
{
  TCutG * IdCut_S[8];
  TCutG * IdCut_P[8];
  /* IdCut_S[0] : Z=1 A=1 stopping
   * IdCut_S[1] : Z=1 A=2 stopping
   * IdCut_S[2] : Z=1 A=3 stopping
   * IdCut_S[3] : Z=2 A=3 stopping
   * IdCut_S[4] : Z=2 A=4 stopping
   * IdCut_S[5] : Z=3 A=6 stopping
   * IdCut_S[6] : Z=3 A=7 stopping
   * IdCut_S[7] : Z=4 A=7 stopping
  */
  
} TOscarCutG;

#endif