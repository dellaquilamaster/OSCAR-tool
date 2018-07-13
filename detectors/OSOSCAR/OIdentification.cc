#include <stdio.h>
#include <stdlib.h>
#include <TCutG.h>
#include <TFile.h>
#include <string.h>

#include <vector>

#include "TOscarCutG.h"
#include "OIdentification.h"
#include "ParticleType.h"
#include "OscarPhysicalParticle.h"

OIdentification::OIdentification() :
NumPads(16),
NumStrips(16)
{
  PhysParticle=new ParticleType[8];
  IdStructure=new TOscarCutG*[NumStrips]();
  for(int i = 0; i<NumStrips; i++)
  {
    IdStructure[i]=new TOscarCutG[NumPads]; /*allocazione di NumPads puntatori a TOscarCutG per ognuna della NumStrips strip*/
  }
}

OIdentification::~OIdentification()
{
  for (int i=0; i<NumStrips; i++)
  {
    delete [] IdStructure[i];
  }
  delete [] IdStructure;
  delete [] PhysParticle;
}

Int_t OIdentification::Init(const char * cut_file)
{
  TFile *CutFile;
  CutFile = new TFile(cut_file);
  if(CutFile->IsZombie())
  {
    printf("DE_E Identification>> Error while opening %s file\n",cut_file); 
    return 0;
  }
  else 
  {
    printf("DE_E Identification>> Opened ROOT file %s\n",cut_file);
  }
  
  /* Possibili tipi di particelle identificabili*/
  PhysParticle[0].Z=1;
  PhysParticle[0].A=1;
  PhysParticle[0].mass_uma=1.007825;
  PhysParticle[1].Z=1;
  PhysParticle[1].A=2;
  PhysParticle[1].mass_uma=2.014101;
  PhysParticle[2].Z=1;
  PhysParticle[2].A=3;
  PhysParticle[2].mass_uma=3.016049;
  PhysParticle[3].Z=2;
  PhysParticle[3].A=3;
  PhysParticle[3].mass_uma=3.016029;
  PhysParticle[4].Z=2;
  PhysParticle[4].A=4;
  PhysParticle[4].mass_uma=4.002603;
  PhysParticle[5].Z=3;
  PhysParticle[5].A=6;
  PhysParticle[5].mass_uma=6.018885;
  PhysParticle[6].Z=3;
  PhysParticle[6].A=7;
  PhysParticle[6].mass_uma=7.016003;
  PhysParticle[7].Z=4;
  PhysParticle[7].A=7;
  PhysParticle[7].mass_uma=7.016928;  
  /*********************************************/
  
  /*Inizializzazione della struttura identificativa IdStructure*/
  char nome_cut_S[30];
  char nome_cut_P[30];
  for(int num_strip = 1; num_strip<=NumStrips; num_strip++)
  {
    for(int num_pad=1; num_pad<=NumPads; num_pad++)
    {
      if( (num_pad-1)%4 == (num_strip-1)/4 ) /*se è così strip e pad individuano un incrocio fisico*/
      { 
        for(int i=0; i<8; i++) /*ciclo su tutti i tipi di particelle identificabili*/
        {
          sprintf(nome_cut_S,"de%02d_e%02d_%d_%d_S",num_strip,num_pad,PhysParticle[i].Z, PhysParticle[i].A);
          sprintf(nome_cut_P,"de%02d_e%02d_%d_%d_P",num_strip,num_pad,PhysParticle[i].Z, PhysParticle[i].A);
          /*estrazione dei cut grafici dal file*/
          IdStructure[num_strip-1][num_pad-1].IdCut_S[i]=(TCutG*)CutFile->Get(nome_cut_S); /*il -1 è usato per far partire da 0 gli array*/
          IdStructure[num_strip-1][num_pad-1].IdCut_P[i]=(TCutG*)CutFile->Get(nome_cut_P);
        }
      }
    }
  }
  CutFile->Close();
  /*************************************************************/
  
  return 1;
}

void OIdentification::PerformEventIdentification(std::vector<OscarPhysicalParticle> *Particle)
{
  Int_t mult_phys=(*Particle).size();
  Int_t num_pad;
  Int_t num_strip;
  Int_t DE;
  Int_t Eres;
  bool  identified;
  int   type_part;
  
  for(int num_part=0; num_part<mult_phys; num_part++)
  {    
    num_strip=(*Particle)[num_part].numstrip -1; /*facciamo -1 così da partire da 0*/
    num_pad  =(*Particle)[num_part].numpad -1; /*facciamo -1 così da partire da 0*/
    DE       =(*Particle)[num_part].DE;
    Eres     =(*Particle)[num_part].Eres;
    identified=0;
    
    for(type_part=0; type_part<8; type_part++)
    {
      if(IdStructure[num_strip][num_pad].IdCut_S[type_part]!=0 && IdStructure[num_strip][num_pad].IdCut_S[type_part]->IsInside(Eres,DE)) 
      {
        identified=1; /*particella identificata*/
        (*Particle)[num_part].stopped=1; /*la particella è stoppata nel 300 micron*/
        break;
      }
      else if(IdStructure[num_strip][num_pad].IdCut_P[type_part]!=0 && IdStructure[num_strip][num_pad].IdCut_P[type_part]->IsInside(Eres,DE))
      {
        identified=1; /*particella identificata*/
        (*Particle)[num_part].stopped=0; /*la particella non è stoppata nel 300 micron*/
        break; 
      }
    }
    if(identified)
    {
      (*Particle)[num_part].Z=PhysParticle[type_part].Z; 
      (*Particle)[num_part].A=PhysParticle[type_part].A; 
      (*Particle)[num_part].mass_uma=PhysParticle[type_part].mass_uma;
    }
    (*Particle)[num_part].identified=identified;
  }
  
  return;
}