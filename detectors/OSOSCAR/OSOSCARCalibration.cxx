#include <OSOSCARCalibration.h>

OSOSCARCalibration::OSOSCARCalibration() :
NumStrips(16),
NumPads(16)
{
  a_coeff_strip =new Double_t[NumStrips];
  b_coeff_strip =new Double_t[NumStrips];
  a_coeff_pad   =new Double_t[NumPads];
  b_coeff_pad   =new Double_t[NumPads];
  thickness_strip=new Double_t[NumStrips];
  thickness_pad  =new Double_t[NumPads];
}

OSOSCARCalibration::~OSOSCARCalibration()
{
  delete [] a_coeff_strip; 
  delete [] b_coeff_strip; 
  delete [] a_coeff_pad;   
  delete [] b_coeff_pad;   
  delete [] thickness_strip;
  delete [] thickness_pad;  
}

int OSOSCARCalibration::Init(const char * file_calib)
{ 
  std::fstream file_calibrations(file_calib,std::ios::in);
  if(!file_calibrations.is_open()) {
    printf("OSCAR Calibrations> Error: Failed to open calibration file\n");
    return 0;
  }
    
  Int_t    pid;
  Double_t a_coeff;
  Double_t b_coeff;
  Double_t thickness;
  int i=0;
  
  /*lettura del file di calibrazioni**************************************************************************/
  for(i=0;file_calibrations>>pid>>a_coeff>>b_coeff>>thickness;i++)
  {
    if(pid/100 == 1)
    {
      a_coeff_strip [pid%100-1] =a_coeff;  /*-1 si usa per partire da 0 con la numerazione delle strip e pad*/
      b_coeff_strip [pid%100-1] =b_coeff;  /*-1 si usa per partire da 0 con la numerazione delle strip e pad*/
      thickness_strip[pid%100-1] =thickness; /*-1 si usa per partire da 0 con la numerazione delle strip e pad*/
    }
    else if(pid/100 == 2)
    {
      a_coeff_pad [pid%100-1] =a_coeff;  /*-1 si usa per partire da 0 con la numerazione delle strip e pad*/
      b_coeff_pad [pid%100-1] =b_coeff;  /*-1 si usa per partire da 0 con la numerazione delle strip e pad*/   
      thickness_pad[pid%100-1] =thickness; /*-1 si usa per partire da 0 con la numerazione delle strip e pad*/
    }
  }
  /***********************************************************************************************************/
  
  return 1;
}

Double_t GetIncEnergyAlpha(Double_t  DeltaE)
{
  return 306.73194764 - 72.86497866*DeltaE+ 8.87165151*pow(DeltaE,2) - 0.61645860*pow(DeltaE,3) + 0.02483404 *pow(DeltaE,4) - 0.00053874 *pow(DeltaE,5) + 0.00000487*pow(DeltaE,6);
}

void OSOSCARCalibration::PerformEventCalibration(std::vector<OSOSCARPhysicalParticle> *Particle)
{
  Int_t mult_phys=(*Particle).size();
  Int_t num_pad;
  Int_t num_strip;
  Int_t DE;
  Int_t Eres;
  
  for(int num_part=0; num_part<mult_phys; num_part++)
  {
    num_strip=(*Particle)[num_part].numstrip -1; /*facciamo -1 così da partire da 0*/
    num_pad  =(*Particle)[num_part].numpad -1; /*facciamo -1 così da partire da 0*/
    DE       =(*Particle)[num_part].DE;
    Eres     =(*Particle)[num_part].Eres;
    Double_t Energy;
    
    if(!(*Particle)[num_part].identified) continue;
    
    (*Particle)[num_part].DE_MeV  =b_coeff_strip[num_strip]+a_coeff_strip[num_strip]*DE;
    (*Particle)[num_part].Eres_MeV=b_coeff_pad[num_pad]  +a_coeff_pad[num_pad]*Eres;
    
    if((*Particle)[num_part].stopped) /*particella stoppata nel 300 micron*/
    {
      Energy=(*Particle)[num_part].DE_MeV+(*Particle)[num_part].Eres_MeV;
    }
    else
    {
      Energy=GetIncEnergyAlpha((*Particle)[num_part].DE_MeV+(*Particle)[num_part].Eres_MeV);
    }
    (*Particle)[num_part].energy=Energy;
  }
  
  return;
}