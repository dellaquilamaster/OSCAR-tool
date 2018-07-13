#ifndef OPAD_H
#define OPAD_H

#include <Rtypes.h>
#include <vector>

class OPad
{
public:
  Int_t mpad;
  std::vector<Int_t> numpad; 
  std::vector<Int_t> epad; 
  
  OPad() :
  mpad(0)
  {}
  ~OPad()
  {}
  
} ;

#endif