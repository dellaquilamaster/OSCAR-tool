#include <OSOSCAR.h>

//________________________________________________
OSOSCAR::OSOSCAR(const char * name, int num_detectors) : OSDetector(name, num_detectors),
fevt(new OSOSCARRootEvent())
{}

//________________________________________________
OSOSCAR::~OSOSCAR()
{
  delete fevt;
}

//________________________________________________
void OSOSCAR::Clear()
{
  return;
}

//________________________________________________
void OSOSCAR::InitTTreeBranch(TTree * TheTree)
{
  TheTree->Branch(Form("%s.",GetName()),"OSOSCARData",&(fevt->fOSCAR),32768,2);
}

//________________________________________________
void OSOSCAR::BuildEvent()
{
  return;
}

//________________________________________________
void OSOSCAR::FillMappedData()
{
  return;
}