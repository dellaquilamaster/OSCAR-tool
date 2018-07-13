#ifndef OGEOMETRY_H
#define OGEOMETRY_H

#include <fstream>
#include <Rtypes.h>


#include "OGeometry.h"

class OGeometry
{
public:
  OGeometry();
  ~OGeometry();
  
  int Init(const char *); /*restituisce il numero di pixel trovati se tutto ok oppure 0 se errore nell'apertura del file*/
  Double_t GetThetaStripPad(Int_t n_strip, Int_t n_pad);
  Double_t GetPhiStripPad(Int_t n_strip, Int_t n_pad);
  
private:
  Double_t ** ThetaTab;
  Double_t ** PhiTab;
  Int_t N_strips;
  Int_t N_pads;
};

#endif