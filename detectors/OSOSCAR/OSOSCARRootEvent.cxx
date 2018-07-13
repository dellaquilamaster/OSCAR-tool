#include <OSOSCARRootEvent.h>

//________________________________________________
OSOSCARData::OSOSCARData(int num_tels) :
fmulti(0)
{
  fnumtel=      new  Int_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fnumstrip=    new  Int_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fnumpad=      new  Int_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fEneStrip=    new  Int_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fTimeStrip=   new  Int_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fEnePad=      new  Int_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fTimePad=     new  Int_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];

  fEneStripCal = new  Double_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fEnePadCal   = new  Double_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];

  fTheta       = new  Double_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fPhi         = new  Double_t [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fZ           = new  Int_t    [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fA           = new  Int_t    [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fIdCode      = new  Int_t    [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
  fPunchThrough =   new  Bool_t   [num_tels*NUM_MAX_PARTICLES_PER_OSCAR];
}

//________________________________________________
OSOSCARData::OSOSCARData() :
fmulti(0)
{
  fnumtel=      new  Int_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fnumstrip=    new  Int_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fnumpad=      new  Int_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fEneStrip=    new  Int_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fTimeStrip=   new  Int_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fEnePad=      new  Int_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fTimePad=     new  Int_t [1*NUM_MAX_PARTICLES_PER_OSCAR];

  fEneStripCal = new  Double_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fEnePadCal   = new  Double_t [1*NUM_MAX_PARTICLES_PER_OSCAR];

  fTheta=           new  Double_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fPhi=             new  Double_t [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fZ=               new  Int_t    [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fA=               new  Int_t    [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fIdCode=          new  Int_t    [1*NUM_MAX_PARTICLES_PER_OSCAR];
  fPunchThrough =   new  Bool_t   [1*NUM_MAX_PARTICLES_PER_OSCAR];
}

//________________________________________________
OSOSCARData::~OSOSCARData()
{
  delete []  fnumtel;      
  delete []  fnumstrip;    
  delete []  fnumpad;      
  delete []  fEneStrip;    
  delete []  fTimeStrip;   
  delete []  fEnePad;      
  delete []  fTimePad;     

  delete []  fEneStripCal; 
  delete []  fEnePadCal;   

  delete []  fTheta;       
  delete []  fPhi;         
  delete []  fZ;           
  delete []  fA;           
  delete []  fIdCode;      
  delete []  fPunchThrough;
}

//________________________________________________
OSOSCARRootEvent::OSOSCARRootEvent()
{}

//________________________________________________
OSOSCARRootEvent::~OSOSCARRootEvent()
{}

