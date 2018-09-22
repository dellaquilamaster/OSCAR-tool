#include <OSOSCAR.h>

#define dStripEnergyModule(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetStripEnergyModule(num_tel,num_det) 
#define dStripEnergyChannel(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetStripEnergyChannel(num_tel,num_det) 
#define dPadEnergyModule(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetPadEnergyModule(num_tel,num_det) 
#define dPadEnergyChannel(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetPadEnergyChannel(num_tel,num_det) 
#define dStripTimeModule(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetStripTimeModule(num_tel,num_det) 
#define dStripTimeChannel(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetStripTimeChannel(num_tel,num_det) 
#define dPadTimeModule(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetPadTimeModule(num_tel,num_det) 
#define dPadTimeChannel(num_tel, num_det) ((OSOSCARMap*)fDetectorMap)->GetPadTimeChannel(num_tel,num_det) 

//________________________________________________
OSOSCAR::OSOSCAR(const char * name, int num_detectors) : OSDetector(name, num_detectors),
fOSCARMapped(new OSOSCARTelescope*[fNumDetectors]),
fevt(new OSOSCARRootEvent(fNumDetectors)),
fTheAnalyzer(new OSOSCARAnalyzer(name, fNumDetectors))
{
  fType.assign("OSCAR");
  for(int i=0; i<fNumDetectors; i++) {
    fOSCARMapped[i]= new OSOSCARTelescope(); 
  }
}

//________________________________________________
OSOSCAR::~OSOSCAR()
{
  for(int i=0; i<fNumDetectors; i++) {
    delete fOSCARMapped[i]; 
  }
  delete [] fOSCARMapped;
  delete fevt;
  delete fTheAnalyzer;
}

//________________________________________________
void OSOSCAR::Clear()
{
  return;
}

//________________________________________________
void OSOSCAR::InitTTreeBranch(TTree * TheTree)
{
  OSOSCARData::Class()->SetCanSplit(1);
  TheTree->Branch(Form("%s.",GetName()),"OSOSCARData",&(fevt->fOSCAR),32768,2);
}

//________________________________________________
void OSOSCAR::BuildEvent()
{  
  //Creation of Raw Event
  for(int i=0; i<fNumDetectors; i++) {
    fOSCARMapped[i]->Clear();
       
  
    for(int j=0; j<NUM_STRIPS_OSCAR; j++) {
      Int_t StripEnergy=(dStripEnergyModule(i,j+1)>=0) ? (*fModuleData)[dStripEnergyModule(i,j+1)][dStripEnergyChannel(i,j+1)] : -9999;
      Int_t StripTime=(dStripTimeModule(i,j+1)>=0) ? (*fModuleData)[dStripTimeModule(i,j+1)][dStripTimeChannel(i,j+1)] : -9999;
            
      if(StripEnergy>100) {
        fOSCARMapped[i]->SetStrip(j+1,StripEnergy, StripTime);
      }
    }
    for(int j=0; j<NUM_PADS_OSCAR; j++) {
      Int_t PadEnergy=(dPadEnergyModule(i,j+1)>=0) ? (*fModuleData)[dPadEnergyModule(i,j+1)][dPadEnergyChannel(i,j+1)] : -9999;
      Int_t PadTime=(dPadTimeModule(i,j+1)>=0) ? (*fModuleData)[dPadTimeModule(i,j+1)][dPadTimeChannel(i,j+1)] : -9999;
            
      if(PadEnergy>100) {
        fOSCARMapped[i]->SetPad(j+1,PadEnergy, PadTime);
      }
    }
    
  }

  //Detector Analysis
  fParticle=fTheAnalyzer->AnalyzeEvent(fOSCARMapped);
}

//________________________________________________
void OSOSCAR::FillMappedData()
{
  (fevt->fOSCAR).fmulti=0;
  for(unsigned int i=0; i<fParticle->size(); i++)
  {
    (fevt->fOSCAR).fnumtel[(fevt->fOSCAR).fmulti]=(*fParticle)[i].numtel;
    (fevt->fOSCAR).fnumstrip[(fevt->fOSCAR).fmulti]=(*fParticle)[i].numstrip;
    (fevt->fOSCAR).fnumpad[(fevt->fOSCAR).fmulti]=(*fParticle)[i].numpad;
    (fevt->fOSCAR).fEneStrip[(fevt->fOSCAR).fmulti]=(*fParticle)[i].DE;
    (fevt->fOSCAR).fTimeStrip[(fevt->fOSCAR).fmulti]=(*fParticle)[i].timestrip;
    (fevt->fOSCAR).fEnePad[(fevt->fOSCAR).fmulti]=(*fParticle)[i].Eres;
    (fevt->fOSCAR).fTimePad[(fevt->fOSCAR).fmulti]=(*fParticle)[i].timepad;
    (fevt->fOSCAR).fEneStripCal[(fevt->fOSCAR).fmulti]=(*fParticle)[i].DE_MeV;
    (fevt->fOSCAR).fEnePadCal[(fevt->fOSCAR).fmulti]=(*fParticle)[i].Eres_MeV;
    (fevt->fOSCAR).fTheta[(fevt->fOSCAR).fmulti]=(*fParticle)[i].theta;
    (fevt->fOSCAR).fPhi[(fevt->fOSCAR).fmulti]=(*fParticle)[i].phi;
    (fevt->fOSCAR).fZ[(fevt->fOSCAR).fmulti]=(*fParticle)[i].Z;
    (fevt->fOSCAR).fA[(fevt->fOSCAR).fmulti]=(*fParticle)[i].A;
    (fevt->fOSCAR).fIdCode[(fevt->fOSCAR).fmulti]=(*fParticle)[i].identified;
    (fevt->fOSCAR).fPunchThrough[(fevt->fOSCAR).fmulti]=(*fParticle)[i].stopped;
    (fevt->fOSCAR).fmulti++;   
  }
}