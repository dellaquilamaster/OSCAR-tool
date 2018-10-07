#include <OSSingleTelescopeIdentification.h>
  
//________________________________________________
OSSingleTelescopeIdentification::OSSingleTelescopeIdentification(const char * det_name) :
fName(det_name)
{}

//________________________________________________
OSSingleTelescopeIdentification::~OSSingleTelescopeIdentification()
{
  if(fIdentificationLoaded) {
    fFileInput->Close();
    delete fFileInput;
  }
}

//________________________________________________
void OSSingleTelescopeIdentification::Clear()
{
  if(fIdentificationLoaded) {
    fFileInput->Close();
    delete fFileInput;
    fIDCut.clear();
    fIdentificationLoaded=false;
  }
}

//________________________________________________
int OSSingleTelescopeIdentification::Init(const char * cut_file)
{
  TFile *CutFile;
  CutFile = new TFile(cut_file);
  if(CutFile->IsZombie()){
    return -1;
  }
  
  TIter NextObj(CutFile->GetListOfKeys());
  
  int NCuts=0;
  
  while (TKey * key = (TKey*)(NextObj())) 
  {
    if(!(gROOT->GetClass(key->GetClassName())->InheritsFrom("TCutG"))) continue;
    
    TCutG * theCut = (TCutG*)key->ReadObj();
    
    if(theCut==0) continue;
    
    std::string CutName (theCut->GetName());
    if(CutName.find(fName)==0) {
      int Z=std::stoi(CutName.substr(CutName.find("_Z")+2,2));
      int A=std::stoi(CutName.substr(CutName.find("_A")+2,2));
      bool punch_through;
      if(CutName.at(CutName.length()-1) == 'S') {
        punch_through=false;
      } else {
        punch_through=true; 
      }
      OSSingleTelescopeIDStructure newIdentification;
      newIdentification.Z=Z;
      newIdentification.A=A;
      newIdentification.IsPunchThrough=punch_through;
      newIdentification.TheCut=theCut;
      
      fIDCut.push_back(newIdentification);
      NCuts++;
    }
  }
  
  return NCuts;
}

//________________________________________________
void OSSingleTelescopeIdentification::PerformEventIdentification(OSSingleTelescopeData * TheEvent)
{
  for(unsigned int i=0; i<fIDCut.size(); i++) {
    if(fIDCut[i].TheCut->IsInside(TheEvent->fEneSecond, TheEvent->fEneFirst)) {
      TheEvent->fZ=fIDCut[i].Z;
      TheEvent->fA=fIDCut[i].A;
      TheEvent->fPunchThrough=fIDCut[i].IsPunchThrough;
      TheEvent->fIdCode=1;
      return;
    }
  }
}

            