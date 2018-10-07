#include <OSSingleTelescopeAnalyzer.h>

//________________________________________________
OSSingleTelescopeAnalyzer::OSSingleTelescopeAnalyzer(const char * det_name) :
fName(det_name),
fIdentificator(new OSSingleTelescopeIdentification(fName.c_str())),
fCalibrator(new OSSingleTelescopeCalibration(fName.c_str())),
fGeometry(new OSSingleTelescopeGeometry(fName.c_str())),
fIdentificationLoaded(false),
fCalibrationLoaded(false),
fGeometryLoaded(false)
{
  //TEMPORARY, Calibration Loading
  if(fGeometry->Init(gRunInfo->GetSingleTelescopeGeometryFileName())>0) {
    printf("OSSingleTelescopeAnalyzer> Loaded %s Geometry from file %s\n", fName.c_str(), gRunInfo->GetSingleTelescopeGeometryFileName());
    fGeometryLoaded=true;
  } else {
    printf("OSSingleTelescopeAnalyzer> Failed to open %s Geometry file %s\n", fName.c_str(), gRunInfo->GetSingleTelescopeGeometryFileName()); 
  }
  if(fIdentificator->Init(gRunInfo->GetSingleTelescopeIdentificationFileName())>0) {
    printf("OSSingleTelescopeAnalyzer> Loaded %s Identification from file %s\n", fName.c_str(), gRunInfo->GetSingleTelescopeIdentificationFileName());
    fIdentificationLoaded=true;
  } else {
    printf("OSSingleTelescopeAnalyzer> Failed to open %s Identification file %s\n", fName.c_str(), gRunInfo->GetSingleTelescopeIdentificationFileName()); 
  }
  if(fCalibrator->LoadCalibration(gRunInfo->GetSingleTelescopeCalibrationFileName())>0) {
    printf("OSSingleTelescopeAnalyzer> Loaded %s Calibration from file %s\n", fName.c_str(), gRunInfo->GetSingleTelescopeCalibrationFileName());
    fCalibrationLoaded=true;
  } else {
    printf("OSSingleTelescopeAnalyzer> Failed to open %s Calibration file %s\n", fName.c_str(), gRunInfo->GetSingleTelescopeCalibrationFileName()); 
  }
}

//________________________________________________
OSSingleTelescopeAnalyzer::~OSSingleTelescopeAnalyzer()
{
  delete fIdentificator;
  delete fCalibrator;
  delete fGeometry;
}

//________________________________________________
void OSSingleTelescopeAnalyzer::AnalyzeEvent(OSSingleTelescopeData * theEvent)
{
  if(fIdentificationLoaded) {
    fIdentificator->PerformEventIdentification(theEvent);  
  }
  
  if(fCalibrationLoaded) {
    fCalibrator->PerformEventCalibration(theEvent);
  }
  
  if(fGeometryLoaded) {
    theEvent->fTheta=fGeometry->GetTheta();
    theEvent->fPhi=fGeometry->GetPhi();
  }
  
  return;
}