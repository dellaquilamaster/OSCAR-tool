#ifndef TROOTEVENT_H
#define TROOTEVENT_H

#include <TTree.h>
#include <TFile.h>

class TOscarEvent
{
public:
  Int_t mult_phys;
  Int_t *Z; //[mult_phys]
  Int_t *A; //[mult_phys]
  Double_t *mass_uma; //[mult_phys]
  Int_t *destrip; //[mult_phys]
  Int_t *eres; //[mult_phys]
  Double_t *destripMeV; //[mult_phys]
  Double_t *eresMeV; //[mult_phys]
  Int_t *numstrip; //[mult_phys]
  Int_t *numpad; //[mult_phys]
  Double_t *theta; //[mult_phys]
  Double_t *phi; //[mult_phys]
  Double_t *energy; //[mult_phys]
  
  TOscarEvent()
  {
    Z         =new Int_t[4]; 
    A         =new Int_t[4]; 
    mass_uma  =new Double_t[4];
    destrip   =new Int_t[4]; 
    eres      =new Int_t[4]; 
    destripMeV=new Double_t[4]; 
    eresMeV   =new Double_t[4]; 
    numstrip  =new Int_t[4]; 
    numpad    =new Int_t[4]; 
    theta     =new Double_t[4]; 
    phi       =new Double_t[4]; 
    energy    =new Double_t[4]; 
  }
  ~TOscarEvent()
  {
    delete [] Z         ; 
    delete [] A         ; 
    delete [] mass_uma  ; 
    delete [] destrip   ; 
    delete [] eres      ; 
    delete [] destripMeV; 
    delete [] eresMeV   ; 
    delete [] numstrip  ; 
    delete [] numpad    ; 
    delete [] theta     ; 
    delete [] phi       ; 
    delete [] energy    ; 
  }
  
  ClassDef(TOscarEvent,1);
};

class TRootEvent
{
private:
  
public:
  Int_t       num_evt;
  Int_t       mult_phys;
  TOscarEvent OscarTel;
  
  TRootEvent() :
  mult_phys(0)
  {}
  ~TRootEvent() {}
  ClassDef(TRootEvent,2);
};

class TRootDefine
{
public:
  TRootDefine();
  ~TRootDefine();
  
  int  Open(const char *filename);
  void Close();
  TTree      *GetTree() {return evttree;}
  TRootEvent *GetEvt()  {return physevt;}
  
private:
  TRootEvent *physevt;
  TTree      *evttree;
  TFile      *frootW;
  
};

#endif