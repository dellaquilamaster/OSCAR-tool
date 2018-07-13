#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "OGeometry.h"

OGeometry::OGeometry () :
N_strips(16),
N_pads(16)
{
  ThetaTab=(Double_t **)new Double_t*[N_strips];
  PhiTab=(Double_t **)new Double_t*[N_strips];
  for(int i=0; i<N_strips; i++)
  {
    ThetaTab[i]=(Double_t *)new Double_t[N_pads](); 
    PhiTab[i]=(Double_t *)new Double_t[N_pads](); 
  }
}

OGeometry::~OGeometry()
{
  for(int i=0; i<N_strips; i++)
  {
    delete [] ThetaTab[i];
    delete [] PhiTab[i];    
  }
  delete [] ThetaTab;
  delete [] PhiTab;
}

int OGeometry::Init(const char * nome_geom_file)
{
  int n_reads=0;
  std::fstream geometry_file (nome_geom_file,std::ios::in);
  if(!geometry_file.is_open())
  {
    return 0;
  }  
  for( int i=0 ; i<N_strips; i++) /*ciclo sulle strips*/
  {
    for( int j=0; j<N_pads; j++) /*ciclo sui pads*/
    {
      if(j%4 != i/4) continue; /*incrocio non fisico --> saltare*/
      
      if(geometry_file>>ThetaTab[i][j]>>PhiTab[i][j])
      {
        n_reads++; 
      }
    }
  }
  geometry_file.close();
  printf("Geometry>> Read %d lines from %s file\n", n_reads,nome_geom_file);
  return n_reads;
}

Double_t OGeometry::GetThetaStripPad(Int_t n_strip, Int_t n_pads)
{
  return ThetaTab[n_strip][n_pads]; 
}

Double_t OGeometry::GetPhiStripPad(Int_t n_strip, Int_t n_pads)
{
  return PhiTab[n_strip][n_pads]; 
}