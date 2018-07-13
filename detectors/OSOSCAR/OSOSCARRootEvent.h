#ifndef OSOSCARROOTEVENT_H
#define OSOSCARROOTEVENT_H

#include <TROOT.h>

#include <OSCARShared.h>

class OSOSCARData
{
public :  
  Int_t    fmulti;
  Int_t    *fnumtel;       //[fmulti]
  Int_t    *fnumstrip;     //[fmulti]
  Int_t    *fnumpad;       //[fmulti]
  Int_t    *fEneStrip;     //[fmulti]
  Int_t    *fTimeStrip;    //[fmulti]
  Int_t    *fEnePad;       //[fmulti]
  Int_t    *fTimePad;      //[fmulti]

  Double_t *fEneStripCal;      //[fmulti]
  Double_t *fEnePadCal;        //[fmulti]

  Double_t *fTheta;            //[fmulti]
  Double_t *fPhi;              //[fmulti]
  Int_t    *fZ;                //[fmulti]
  Int_t    *fA;                //[fmulti]
  Int_t    *fIdCode;           //[fmulti]
  Bool_t   *fPunchThrough;     //[fmulti]
  
  OSOSCARData(int);
  OSOSCARData();
  virtual ~OSOSCARData();
  
  ClassDef(OSOSCARData,1);
};

class OSOSCARRootEvent
{
public :  
  OSOSCARData fOSCAR;
  
  OSOSCARRootEvent(int);
  OSOSCARRootEvent();
  virtual ~OSOSCARRootEvent();
    
  ClassDef(OSOSCARRootEvent,1);
};

#endif