#include <OSDetector.h>

//____________________________________________________
OSDetector::OSDetector(const char * name, int num_detectors) :
fName(name),
fNumDetectors(num_detectors),
fDetectorMap(0),
fModuleData(new std::map<Int_t, Int_t*>)
{}

//____________________________________________________
OSDetector::~OSDetector()
{
  delete fModuleData;
}

//____________________________________________________
void OSDetector::Clear()
{
  return;
}

//____________________________________________________
void OSDetector::AssignModule(Int_t module_num, Int_t * module_data)
{
  (*fModuleData)[module_num]=module_data;
}

//____________________________________________________
void OSDetector::SetMapping(OSDetectorMap * TheMapping)
{
  fDetectorMap=TheMapping;
}

//____________________________________________________
const char * OSDetector::GetName() const
{
  return fName.c_str();
}

//____________________________________________________
const char * OSDetector::GetType() const
{
  return fType.c_str();
}

//____________________________________________________
int OSDetector::GetNumDetectors() const
{
  return fNumDetectors;
}

//____________________________________________________
void OSDetector::InitTTreeBranch(TTree *)
{
  return;
}

//____________________________________________________
void OSDetector::BuildEvent()
{
  return;
}

//____________________________________________________
void OSDetector::FillMappedData()
{
  return;
}