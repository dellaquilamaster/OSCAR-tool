#ifndef OGEOMETRY_H
#define OGEOMETRY_H

#include <fstream>
#include <sstream>
#include <Rtypes.h>
#include <TROOT.h>


class OSOSCARGeometry
{
public:
  OSOSCARGeometry(const char *, int);
  ~OSOSCARGeometry();
  
  int Init(const char *); /*restituisce il numero di pixel trovati se tutto ok oppure 0 se errore nell'apertura del file*/
  Double_t GetThetaStripPad(int n_tel, int n_strip, int n_pad);
  Double_t GetPhiStripPad(int n_tel, int n_strip, int n_pad);
  
private:
  std::string fName;
  int fNumTelescopes;
  int fNumStrips;
  int fNumPads;
  double *** ThetaTab;
  double *** PhiTab;
};

#endif