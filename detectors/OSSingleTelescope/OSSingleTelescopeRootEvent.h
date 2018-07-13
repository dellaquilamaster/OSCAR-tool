#ifndef OSSINGLETELESCOPEROOTEVENT_H
#define OSSINGLETELESCOPEROOTEVENT_H

#include <TROOT.h>

#include <OSCARShared.h>

class OSSingleTelescopeData
{
public :  
  Int_t     fEneFirst;
  Int_t     fEneSecond;
  Int_t     fTimeFirst;
  Int_t     fTimeSecond;
  
  Int_t     fEneFirstCal;
  Int_t     fEneSecondCal;

  Double_t  fTheta;        
  Double_t  fPhi;          
  Int_t     fZ;            
  Int_t     fA;            
  Int_t     fIdCode;       
  Bool_t    fPunchThrough; 
  
  OSSingleTelescopeData();
  virtual ~OSSingleTelescopeData();
  
  ClassDef(OSSingleTelescopeData,1);
};

class OSSingleTelescopeRootEvent
{
public :  
  OSSingleTelescopeData fSingleTelescope;
  
  OSSingleTelescopeRootEvent();
  virtual ~OSSingleTelescopeRootEvent();
    
  ClassDef(OSSingleTelescopeRootEvent,1);
};

#endif