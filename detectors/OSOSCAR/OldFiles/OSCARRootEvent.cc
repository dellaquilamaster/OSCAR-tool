#include <iostream>

#include "TRootEvent.h"


TRootDefine::TRootDefine() :
physevt(0),
evttree(0),
frootW(0)
{}

TRootDefine::~TRootDefine()
{
  if(physevt)
    delete physevt;
  if(frootW)
    delete frootW;
}

int TRootDefine::Open(const char *filename)
{
  frootW = new TFile(filename,"RECREATE");
  if(frootW->IsZombie())
  {
    printf("TFile>> Error while opening %s file\n",filename);
    return 0;
  }
  else
  {
    printf("TFile>> File %s opened\n",filename);
  }
  
  frootW->SetCompressionLevel(1);
  physevt = new TRootEvent();
  evttree = new TTree("h1","OSCARUNPACKER Tree");
  evttree->SetAutoSave(50000000);
  
  /*make classes splittable*/
  TRootEvent::Class()->SetCanSplit(1);
  TOscarEvent::Class()->SetCanSplit(1);
  /*************************/
  
  evttree->Branch("event", &physevt, 32000, 2);
  
  return 1;
}

void TRootDefine::Close()
{ 
  if(frootW)
  {
    frootW->cd();
    frootW->WriteTObject(evttree,"h1");
    std::cout<<"RootTree>> closing ROOT file"<<std::endl;
    frootW->Close();
  }
}

