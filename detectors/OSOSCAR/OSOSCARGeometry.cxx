#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include <OSOSCARGeometry.h>

OSOSCARGeometry::OSOSCARGeometry (const char * det_name, int num_telescopes) :
fName(det_name),
fNumTelescopes(num_telescopes),
fNumStrips(16),
fNumPads(16),
ThetaTab(new double **[fNumTelescopes]),
PhiTab(new double **[fNumTelescopes])
{
  for(int i=0; i<fNumTelescopes; i++) {
    ThetaTab[i]=(Double_t **)new Double_t*[fNumStrips];
    PhiTab[i]=(Double_t **)new Double_t*[fNumStrips];
    for(int j=0; j<fNumStrips; j++)
    {
      ThetaTab[i][j]=(Double_t *)new Double_t[fNumPads](); 
      PhiTab[i][j]=(Double_t *)new Double_t[fNumPads](); 
    }
  }
}

OSOSCARGeometry::~OSOSCARGeometry()
{
  for(int i=0; i<fNumTelescopes; i++) {
    for(int j=0; j<fNumStrips; j++) {
      delete [] ThetaTab[i][j]; 
      delete [] PhiTab[i][j]; 
    }
    delete [] ThetaTab[i];
    delete [] PhiTab[i];
  }
  delete [] ThetaTab;
  delete [] PhiTab;
}

int OSOSCARGeometry::Init(const char * nome_geom_file)
{  
  std::ifstream FileIn(nome_geom_file);

  if(!FileIn.is_open()) {
    printf("OSCAR Geometry> Error: Failed to open geometry file %s\n", nome_geom_file);
    return -1;
  }  
  
  int NRead=0;
  
  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;
    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;
    
    std::istringstream LineStream(LineReadCommentLess);
    
    std::string Det;
    double theta;
    double phi;
    int num_strip;
    int num_pad;
    
    LineStream>>Det>>num_strip>>num_pad>>theta>>phi;
    
    if(Det.find(Form("%s_",fName.c_str()))!=0) continue; //not this OSCAR cluster
    
    int NumTel=std::stoi(Det.substr(Det.find("TEL_")+4,2));
    
    ThetaTab[NumTel][num_strip-1][num_pad-1]=theta;
    PhiTab[NumTel][num_strip-1][num_pad-1]=phi;
    
    NRead++;
  }
  
  FileIn.close();
  return NRead;
}

Double_t OSOSCARGeometry::GetThetaStripPad(int n_tel, int n_strip, int n_pads)
{
  return ThetaTab[n_tel][n_strip-1][n_pads-1]; 
}

Double_t OSOSCARGeometry::GetPhiStripPad(int n_tel, int n_strip, int n_pads)
{
  return PhiTab[n_tel][n_strip-1][n_pads-1]; 
}