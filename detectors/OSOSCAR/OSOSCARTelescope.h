#ifndef OSOSCARTELESCOPE_H
#define OSOSCARTELESCOPE_H

#include <TROOT.h>
#include <OSOSCARStrip.h>
#include <OSOSCARPad.h>

#include <OSCARShared.h>

class OSOSCARTelescope
{
public :
  OSOSCARTelescope();
  ~OSOSCARTelescope();
  
  int GetNumStrips() const;
  int GetNumPads() const;
  
  int fmultstrip;
  int fmultpad;
  OSOSCARStrip * fStrips;
  OSOSCARPad * fPads;
  
  void Clear();
  
  void SetStrip(int, int, int);
  void SetPad(int, int, int);
  
private :
  int fNumStrips;
  int fNumPads;
};

#endif