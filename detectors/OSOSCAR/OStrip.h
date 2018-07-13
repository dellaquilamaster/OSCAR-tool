#ifndef OSTRIP_H
#define OSTRIP_H

#include <Rtypes.h>
#include <vector>

class OStrip
{
public:
  Int_t mfront;
  std::vector<Int_t> numfront;
  std::vector<Int_t> efront; 
  
  OStrip() :
  mfront(0)
  {}
  ~OStrip()
  {}
  
} ;

#endif