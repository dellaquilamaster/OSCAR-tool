#include <vector>
#include <TTree.h>

#include "EventoBruto.h"
#include "TRootEvent.h"
#include "OAnalyzer.h"
#include "OTracks.h"
#include "OIdentification.h"
#include "OCalibration.h"
#include "OscarPhysicalParticle.h"

OAnalyzer::OAnalyzer(std::vector<EventoBruto>& Buffer, TRootDefine * ManageEvent, OGeometry * GeomModule, OIdentification * IdModule, OCalibration * CalibModule) :
EvtBuffer(Buffer),
OscarEvt(ManageEvent),
PhysicalEvent(ManageEvent->GetEvt()),
num_good_events(0),
OscarIdentificator(IdModule),
OscarCalibrator(CalibModule),
OscarGeometry(GeomModule)
{}

void OAnalyzer::RunDataAnalysis()
{
  int NumEvents = EvtBuffer.size();
  /*ciclo su tutti gli eventi e riempimento del tree*/
  for(int curr_event=0; curr_event<NumEvents; curr_event++)
  {
    AnalyzeEvent(curr_event);
  }
  /**************************************************/
  
  return;
}

/*analisi dell'evento**********************************************************************************************/
void OAnalyzer::AnalyzeEvent(Int_t num_evt)
{
  /*definisco la struttura dati dove storare le tracce riconosciute*/
  OTracks IdTracks;
  /*****************************************************************/
  
  /*determino le tracce fisiche*************************************/
  IdTracks=FindTracks(num_evt);
  
  if(IdTracks.good_part==-1) /*presente ambiguità  nel tracciamento --> rigettare l'evento*/
  {  
    return;
  }
  /*****************************************************************/
  
  /*setto le variabili d'evento*************************************/
  PhysicalEvent->num_evt=num_good_events; /*settiamo il numero d'evento*/
  PhysicalEvent->mult_phys=IdTracks.good_part; /*setto la molteplicità  pari al numero di tracce buone*/
  (PhysicalEvent->OscarTel).mult_phys=IdTracks.good_part; /*per adesso la molteplicità è la stessa che sull'unico telescopio OSCAR*/
  num_good_events++; /*incremento il contatore di eventi buoni*/
  /*****************************************************************/
  
  /*Riempio il vettore con le particelle effettivamente tracciate (fisiche) prendendole dal buffer opportunamente*/
  FillParticleTracks(IdTracks, num_evt);
  
  /*Modulo di identificazione DE_E*/
  OscarIdentificator->PerformEventIdentification(&Particle);
  
  /*Modulo di calibrazione*/
  OscarCalibrator->PerformEventCalibration(&Particle);
  
  /*Riempio l'evento*/
  for(int i=0; i<(PhysicalEvent->OscarTel).mult_phys; i++)
  {
    (PhysicalEvent->OscarTel).A[i]         = Particle[i].A;
    (PhysicalEvent->OscarTel).Z[i]         = Particle[i].Z;
    (PhysicalEvent->OscarTel).mass_uma[i]  = Particle[i].mass_uma;
    (PhysicalEvent->OscarTel).destrip[i]   = Particle[i].DE;
    (PhysicalEvent->OscarTel).eres[i]      = Particle[i].Eres;
    (PhysicalEvent->OscarTel).destripMeV[i]= Particle[i].DE_MeV;
    (PhysicalEvent->OscarTel).eresMeV[i]   = Particle[i].Eres_MeV;
    (PhysicalEvent->OscarTel).energy[i]    = Particle[i].energy;
    (PhysicalEvent->OscarTel).numstrip[i]  = Particle[i].numstrip;
    (PhysicalEvent->OscarTel).numpad[i]    = Particle[i].numpad;
    (PhysicalEvent->OscarTel).theta[i]     = Particle[i].theta;
    (PhysicalEvent->OscarTel).phi[i]       = Particle[i].phi;    
  }
  /***********************************************************************/
  
  /*riempimento del tree con l'evento identificato e calibrato*/
  (OscarEvt->GetTree())->Fill();
  
  /*pulizia del vettore di particelle*/
  Particle.clear();
  
  return;
}
/******************************************************************************************************************/

/* Implemento qui due funzioni che servono al metodo FindTracks rispettivamente per inserire in 
 * array i gruppi del detector colpiti in primo e secondo stadio e poi per trovarne le corrispondenze*/
bool InsertGroup(Int_t *array, Int_t new_element, Int_t index) /*restituisce il numero di elementi inseriti*/
{
  if(index==0)
  {
    array[index]=new_element;
    return 1;
  }
  Int_t curr_index=index-1;
  for(int i=0; i<curr_index; i++)
  {
    if(new_element==array[i]) return 0; /*in questo caso questo gruppo ha già risposto e l'evento va buttato*/
  }
  array[index]=new_element;
  return 1; /*tutto ok*/
}

Int_t FindCorrispondence(Int_t element, Int_t * array, Int_t array_size) /*restituisce l'indice dell'array per il quale è stata trovata la corrispondenza; restituisce -1 se la corrispondenza non Ã¨ trovata*/
{
  for(int i=0; i<array_size; i++)
  {
    if(element==array[i]) return i; 
  }
  return -1; /*corrispondenza non trovata --> rigettare l'evento*/
}

OTracks OAnalyzer::FindTracks(Int_t num_evt)
{
  OTracks ParticlesTrack;
  ParticlesTrack.good_part=0; /*inizializzo a 0 il numero di tracce buone*/
  Int_t PadGroups[4];  /*array contenente i gruppi del rivelatore a cui ogni particella dell'evento appartiene*/
  Int_t StripGroups[4];
  Int_t MultPad=(EvtBuffer[num_evt].PadDetector).mpad;
  Int_t MultStrip=(EvtBuffer[num_evt].StripDetector).mfront;
    
  if( MultPad==MultStrip && MultPad<=4 ) /*massimo 4 particelle, eguali molteplicità  sui due stadi*/
  {
    bool evt_good=1;
    
    for(int i=0; i<MultPad; i++) /*ciclo di riempimento array dei gruppi*/
    {
      if(InsertGroup(PadGroups,(((EvtBuffer[num_evt]).PadDetector).numpad[i]-1)%4,i)==0) evt_good=0;
      if(InsertGroup(StripGroups,(((EvtBuffer[num_evt]).StripDetector).numfront[i]-1)/4,i)==0) evt_good=0;
    }
    for(int indexcorr, i=0; i<MultPad; i++) /*ciclo di ricerca delle corrispondenze tra gruppi*/
    {
      indexcorr=FindCorrispondence(PadGroups[i],StripGroups,MultStrip);
      if(indexcorr<0)
      {
        evt_good=0;
        break;
      }
      ParticlesTrack.good_part++;
      ParticlesTrack.IndexPad[i]=i;
      ParticlesTrack.IndexStrip[i]=indexcorr;
      /*l'i-esimo pad che ha risposto à in corrispondenza della strip indexcorr-esima che ha risposto*/
    }
    
    if(evt_good==1) /*in questo caso l'evento è buono*/
    {
      return ParticlesTrack;
    }
  }
  
  /*se sono qui non è vero l'if precedente e l'evento è da buttare*/
  ParticlesTrack.good_part=-1;
  return ParticlesTrack;
}

void OAnalyzer::FillParticleTracks(OTracks ParticlesTrack, Int_t num_evt)
{
  OscarPhysicalParticle new_particle;
  Int_t EventMultiplicity=ParticlesTrack.good_part;
  for(int i=0; i<EventMultiplicity; i++) /*ciclo su tutta la molteplicità d'evento*/
  {
    /*inizializzo a -1 le variabili di identificazione e calibrazione*/
    new_particle.A=-1;
    new_particle.Z=-1;
    new_particle.mass_uma=-1;
    new_particle.energy  =-1;
    new_particle.DE_MeV  =-1;
    new_particle.Eres_MeV=-1;
    /*****************************************************************/
    new_particle.DE       =((EvtBuffer[num_evt]).StripDetector).efront[ParticlesTrack.IndexStrip[i]]; /*inserisco nell'evento fisico alla posizione ciò che il buffer propone all'evento num_evt relativamente alla strip in indice IdTracks.IndexStrip*/
    new_particle.Eres     =((EvtBuffer[num_evt]).PadDetector).epad[ParticlesTrack.IndexPad[i]];
    new_particle.numstrip =((EvtBuffer[num_evt]).StripDetector).numfront[ParticlesTrack.IndexStrip[i]];
    new_particle.numpad   =((EvtBuffer[num_evt]).PadDetector).numpad[ParticlesTrack.IndexPad[i]];
    new_particle.theta    =OscarGeometry->GetThetaStripPad(new_particle.numstrip-1,new_particle.numpad-1); /*-1 per cominciare a contare da 0*/
    new_particle.phi      =OscarGeometry->GetPhiStripPad(new_particle.numstrip-1,new_particle.numpad-1);
    
    Particle.push_back(new_particle); /*salvo la particella nel vettore delle particelle fisiche*/
  }
}