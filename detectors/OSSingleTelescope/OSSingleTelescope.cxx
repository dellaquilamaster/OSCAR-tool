#include <OSSingleTelescope.h>

#define dModuleEneFirst() ((OSSingleTelescopeMap*)fDetectorMap)->GetEnergyFirstModule()
#define dModuleEneSecond() ((OSSingleTelescopeMap*)fDetectorMap)->GetEnergySecondModule()
#define dModuleTimeFirst() ((OSSingleTelescopeMap*)fDetectorMap)->GetTimeFirstModule()
#define dModuleTimeSecond() ((OSSingleTelescopeMap*)fDetectorMap)->GetTimeSecondModule()
#define dChannelEneFirst() ((OSSingleTelescopeMap*)fDetectorMap)->GetEnergyFirstChannel()
#define dChannelEneSecond() ((OSSingleTelescopeMap*)fDetectorMap)->GetEnergySecondChannel()
#define dChannelTimeFirst() ((OSSingleTelescopeMap*)fDetectorMap)->GetTimeFirstChannel()
#define dChannelTimeSecond() ((OSSingleTelescopeMap*)fDetectorMap)->GetTimeSecondChannel()

//________________________________________________
OSSingleTelescope::OSSingleTelescope(const char * name) : OSDetector(name),
fevt(new OSSingleTelescopeRootEvent())
{
  fType.assign("SingleTelescope");  
}

//________________________________________________
OSSingleTelescope::~OSSingleTelescope()
{
  delete fevt;
}

//________________________________________________
void OSSingleTelescope::Clear()
{
  return;
}

//________________________________________________
void OSSingleTelescope::InitTTreeBranch(TTree * TheTree)
{
  OSSingleTelescopeData::Class()->SetCanSplit(1);
  TheTree->Branch(Form("%s.",GetName()),"OSSingleTelescopeData",&(fevt->fSingleTelescope),32768,2);
}

//________________________________________________
void OSSingleTelescope::BuildEvent()
{
  return;
}

//________________________________________________
void OSSingleTelescope::FillMappedData()
{
  (fevt->fSingleTelescope).fEneFirst=(dModuleEneFirst()>=0) ? ((*fModuleData)[dModuleEneFirst()])[dChannelEneFirst()] : -9999;
  (fevt->fSingleTelescope).fEneSecond=(dModuleEneSecond()>=0) ? ((*fModuleData)[dModuleEneSecond()])[dChannelEneSecond()] : -9999;
  (fevt->fSingleTelescope).fTimeFirst=(dModuleTimeFirst()>=0) ? ((*fModuleData)[dModuleTimeFirst()])[dChannelTimeFirst()] : -9999;
  (fevt->fSingleTelescope).fTimeSecond=(dModuleTimeFirst()>=0) ? ((*fModuleData)[dModuleTimeFirst()])[dChannelTimeFirst()] : -9999;
  
  
}