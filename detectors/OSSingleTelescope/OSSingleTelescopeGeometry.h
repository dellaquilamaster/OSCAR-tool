#ifndef OSSINGLETELESCOPEGEOMETRY
#define OSSINGLETELESCOPEGEOMETRY

#include <fstream>
#include <sstream>
#include <string>
#include <Rtypes.h>
#include <TROOT.h>

class OSSingleTelescopeGeometry
{
public :
  OSSingleTelescopeGeometry(const char *);
  ~OSSingleTelescopeGeometry();
  
  int Init(const char *);
  double GetTheta() const;
  double GetPhi() const;
  
private :
  bool fGeometryLoaded;
  std::string fName;
  double fTheta;
  double fPhi;
};

#endif