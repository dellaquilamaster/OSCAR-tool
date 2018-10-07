#include <OSSingleTelescopeCalibration.h>

//________________________________________________
OSSingleTelescopeCalibration::OSSingleTelescopeCalibration(const char * det_name) :
fName(det_name),
fCalibrationLoaded(false)
{}

//________________________________________________
OSSingleTelescopeCalibration::~OSSingleTelescopeCalibration()
{}

//________________________________________________
int OSSingleTelescopeCalibration::LoadCalibration(const char * file_name)
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
    std::string NameStage;
    double intercept;
    double slope;
    double thickness;

    LineStream >> NameDet >> intercept >> slope >> thickness;
        
    NameStage.assign(NameDet.substr(NameDet.find_last_of("_")+1));
    NameDet.assign(NameDet.substr(0,NameDet.find_last_of("_")));

    if(fName.compare(NameDet)!=0) continue;
    
    if(NameStage.compare("DE")==0) {
      fInterceptFirst=intercept;
      fSlopeFirst=slope;
    } else if(NameStage.compare("E")==0) {
      fInterceptSecond=intercept;
      fSlopeSecond=slope;
    }

    NRead++;
  }

  fCalibrationLoaded=true;
  return NRead;  
}

//________________________________________________
double OSSingleTelescopeCalibration::GetEnergyFirst(double ch) const
{
  return fCalibrationLoaded ? fInterceptFirst+fSlopeFirst*ch : -9999; 
}

//________________________________________________
double OSSingleTelescopeCalibration::GetEnergySecond(double ch) const
{
  return fCalibrationLoaded ? fInterceptSecond+fSlopeSecond*ch : -9999; 
}

//________________________________________________
void OSSingleTelescopeCalibration::PerformEventCalibration(OSSingleTelescopeData * theEvent)
{
  if(!fCalibrationLoaded) return;
  
  theEvent->fEneFirstCal=GetEnergyFirst(theEvent->fEneFirst);
  theEvent->fEneSecondCal=GetEnergySecond(theEvent->fEneSecond);
  
  if(theEvent->fIdCode==0 || theEvent->fPunchThrough==false) { //Particle stopped: the energy is simply the sum First+Second
    theEvent->fEnergyCal=theEvent->fEneFirstCal+theEvent->fEneSecondCal;
  } else if (theEvent->fPunchThrough==true) { //Particle in punch-through
    //TO BE IMPLEMENTED
  }
  
  return;
}

//________________________________________________
const char * OSSingleTelescopeCalibration::GetDetectorName() const
{
  return fName.c_str(); 
}