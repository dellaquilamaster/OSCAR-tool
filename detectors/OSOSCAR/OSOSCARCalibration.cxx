#include <OSOSCARCalibration.h>

OSOSCARCalibration::OSOSCARCalibration(const char * det_name, int num_telescopes) :
fName(det_name),
fNumTelescopes(num_telescopes),
fNumStrips(16),
fNumPads(16),
fStripIntercept(new double*[fNumTelescopes]),
fStripSlope(new double*[fNumTelescopes]),
fPadIntercept(new double*[fNumTelescopes]),
fPadSlope(new double*[fNumTelescopes]),
fStripThickness(new double*[fNumTelescopes]),
fPadThickness(new double*[fNumTelescopes])
{
  for(int i=0; i<fNumStrips; i++) {
    fStripIntercept[i]=(new double[fNumStrips]);
    fStripSlope[i]=(new double[fNumStrips]);
    fStripThickness[i]=(new double[fNumStrips]);
  }
  for(int i=0; i<fNumPads; i++) {
    fPadIntercept[i]=(new double[fNumPads]);
    fPadSlope[i]=(new double[fNumPads]);
    fPadThickness[i]=(new double[fNumPads]);
  }
}

OSOSCARCalibration::~OSOSCARCalibration()
{
  for(int i=0; i<fNumStrips; i++) {
    delete [] fStripIntercept[i];
    delete [] fStripSlope[i];
    delete [] fStripThickness[i];
  }
  for(int i=0; i<fNumPads; i++) {
    delete [] fPadIntercept[i];
    delete [] fPadSlope[i];
    delete [] fPadThickness[i];
  }
}

int OSOSCARCalibration::Init(const char * file_calib)
{
  std::ifstream FileIn(file_calib);

  if(!FileIn.is_open()) {
    printf("OSCAR Calibrations> Error: Failed to open calibration file %s\n", file_calib);
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
    
    std::istringstream LineStream(LineRead);
    
    std::string Det;
    double b_coeff;
    double a_coeff;
    double thickness;
    
    LineStream>>Det>>b_coeff>>a_coeff>>thickness;
    
    if(Det.find(Form("%s_",fName.c_str()))!=0) continue; //not this OSCAR cluster
    
    int NumTel=std::stoi(Det.substr(Det.find("TEL_")+4,2));
    
    if(Det.find("PAD_")!=std::string::npos) {
      int NumDet = std::stoi(Det.substr(Det.find("PAD_")+4));
      fStripSlope[NumTel][NumDet-1]=a_coeff;
      fStripIntercept[NumTel][NumDet-1]=b_coeff;
      fStripThickness[NumTel][NumDet-1]=thickness;
      NRead++;
    } else if (Det.find("STRIP_")!=std::string::npos) {
      int NumDet = std::stoi(Det.substr(Det.find("STRIP_")+6));
      fPadSlope[NumTel][NumDet-1]=a_coeff;
      fPadIntercept[NumTel][NumDet-1]=b_coeff;
      fPadThickness[NumTel][NumDet-1]=thickness;
      NRead++;
    }
  }
  
  return NRead;
}

void OSOSCARCalibration::PerformEventCalibration(std::vector<OSOSCARPhysicalParticle> *Particle)
{
  Int_t mult_phys=(*Particle).size();
  Int_t num_pad;
  Int_t num_strip;
  Int_t DE;
  Int_t Eres;
  Int_t num_tel;
  
  for(int num_part=0; num_part<mult_phys; num_part++)
  {
    num_tel  =(*Particle)[num_part].numtel;
    num_strip=(*Particle)[num_part].numstrip -1; /*facciamo -1 così da partire da 0*/
    num_pad  =(*Particle)[num_part].numpad -1; /*facciamo -1 così da partire da 0*/
    DE       =(*Particle)[num_part].DE;
    Eres     =(*Particle)[num_part].Eres;
    Double_t Energy=-9999;
    
    (*Particle)[num_part].DE_MeV  =fStripIntercept[num_tel][num_strip]+fStripSlope[num_tel][num_strip]*DE;
    (*Particle)[num_part].Eres_MeV=fPadIntercept[num_tel][num_pad]  +fPadSlope[num_tel][num_pad]*Eres;
    
    if(!(*Particle)[num_part].identified || (*Particle)[num_part].stopped) /*particella stoppata nel 300 micron oppure non identificata*/
    {
      Energy=(*Particle)[num_part].DE_MeV+(*Particle)[num_part].Eres_MeV;
    }
    else if (!(*Particle)[num_part].stopped)
    {
      //Per ora non implementato
    }
    (*Particle)[num_part].energy=Energy;
  }
  
  return;
}