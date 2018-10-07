#include <OSSingleTelescopeGeometry.h>

//________________________________________________
OSSingleTelescopeGeometry::OSSingleTelescopeGeometry(const char * det_name) :
fGeometryLoaded(false),
fName(det_name)
{}

//________________________________________________
OSSingleTelescopeGeometry::~OSSingleTelescopeGeometry()
{}

//________________________________________________
int OSSingleTelescopeGeometry::Init(const char * file_name)
{
   std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    std::string NameDet;
    double theta;
    double phi;

    LineStream >> NameDet >> theta >> phi;
    
    if(fName.compare(NameDet)!=0) continue;
    
    fTheta=theta;
    fPhi=phi;

    NRead++;
  }

  fGeometryLoaded=true;
  return NRead;  
}

//________________________________________________
double OSSingleTelescopeGeometry::GetTheta() const 
{
  return fTheta; 
}

//________________________________________________
double OSSingleTelescopeGeometry::GetPhi() const 
{
  return fPhi; 
}
