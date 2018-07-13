#include <OSOSCARAnalyzer.h>

//________________________________________________
OSOSCARAnalyzer::OSOSCARAnalyzer(int num_telescopes) :
fNumTelescopes(num_telescopes),
fParticle(new std::vector<OSOSCARPhysicalParticle>),
fOscarIdentificator(new OSOSCARIdentification()),
fOscarCalibrator(new OSOSCARCalibration()),
fOscarGeometry(new OSOSCARGeometry()),
fIdentificationLoaded(false),
fCalibrationLoaded(false),
fGeometryLoaded(false)
{
  //TEMPORARY, Calibration Loading
  if(file_oscargeometry_name[0]!='\0' && fOscarGeometry->Init(file_oscargeometry_name)>0) {
    fGeometryLoaded=true;
  }
  if(file_oscarcalibration_name[0]!='\0' && fOscarCalibrator->Init(file_oscarcalibration_name)>0) {
    fCalibrationLoaded=true;
  }
  if(file_oscaridentification_name[0]!='\0' && fOscarIdentificator->Init(file_oscaridentification_name)>0) {
    fIdentificationLoaded=true;
  }
}

//________________________________________________
OSOSCARAnalyzer::~OSOSCARAnalyzer()
{}

//________________________________________________
std::vector<OSOSCARPhysicalParticle> * OSOSCARAnalyzer::AnalyzeEvent(OSOSCARTelescope ** MappedData)
{
  /*pulizia del vettore di particelle*/
  fParticle->clear();
  
  /*definisco la struttura dati dove storare le tracce riconosciute*/
  OSOSCARTracks IdTracks;
  /*****************************************************************/
  
    for(int NumTel=0; NumTel<fNumTelescopes; NumTel++) {
    //Pixelization
    IdTracks=FindTracks(MappedData[NumTel]);
    if(IdTracks.good_part==-1) { //Ambiguity in track recognition  
      continue;
    }
    
    //Riempio il vettore con le particelle effettivamente tracciate (fisiche) prendendole dal buffer opportunamente
    FillParticleTracks(&IdTracks, MappedData[NumTel], NumTel);
    
    //Modulo di identificazione DE_E
    if(fIdentificationLoaded) {
      fOscarIdentificator->PerformEventIdentification(fParticle);
    }
    
    //Modulo di calibrazione
    if(fCalibrationLoaded) {
      fOscarCalibrator->PerformEventCalibration(fParticle);
    }
  }
  
  return fParticle;
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

//________________________________________________
OSOSCARTracks OSOSCARAnalyzer::FindTracks(OSOSCARTelescope * MappedData)
{
  OSOSCARTracks ParticlesTrack;
  ParticlesTrack.good_part=0; /*inizializzo a 0 il numero di tracce buone*/
  Int_t PadGroups[4];  /*array contenente i gruppi del rivelatore a cui ogni particella dell'evento appartiene*/
  Int_t StripGroups[4];
  Int_t MultPad=MappedData->fmultpad;
  Int_t MultStrip=MappedData->fmultstrip;

  if( MultPad==MultStrip && MultPad<=4 ) /*massimo 4 particelle, eguali molteplicità  sui due stadi*/
  {
    bool evt_good=1;
    
    for(int i=0; i<MultPad; i++) /*ciclo di riempimento array dei gruppi*/
    {
      if(InsertGroup(PadGroups,  ((MappedData->fPads[i]).numpad-1)%4, i)==0) evt_good=0;
      if(InsertGroup(StripGroups, ((MappedData->fStrips[i]).numstrip-1)/4, i)==0) evt_good=0;
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

//________________________________________________
void OSOSCARAnalyzer::FillParticleTracks(OSOSCARTracks * ParticlesTrack, OSOSCARTelescope * MappedData, int NumTel)
{
  Int_t EventMultiplicity=ParticlesTrack->good_part;
  for(int i=0; i<EventMultiplicity; i++)
  {
    OSOSCARPhysicalParticle new_particle;
    //Calibration variables
    new_particle.A=-9999;
    new_particle.Z=-9999;
    new_particle.mass_uma=-9999;
    new_particle.energy  =-9999;
    new_particle.DE_MeV  =-9999;
    new_particle.Eres_MeV=-9999;

    new_particle.numtel   =NumTel;
    new_particle.DE       =(MappedData->fStrips[ParticlesTrack->IndexStrip[i]]).efront; //WARNING: inserisco nell'evento fisico alla posizione ciò che il buffer propone all'evento num_evt relativamente alla strip in indice IdTracks.IndexStrip
    new_particle.Eres     =(MappedData->fPads[ParticlesTrack->IndexPad[i]]).epad;
    new_particle.timestrip=(MappedData->fStrips[ParticlesTrack->IndexStrip[i]]).timefront;
    new_particle.timepad  =(MappedData->fPads[ParticlesTrack->IndexPad[i]]).timepad;
    new_particle.numstrip =(MappedData->fStrips[ParticlesTrack->IndexStrip[i]]).numstrip;
    new_particle.numpad   =(MappedData->fPads[ParticlesTrack->IndexPad[i]]).numpad;
    new_particle.theta    =fGeometryLoaded ? fOscarGeometry->GetThetaStripPad(new_particle.numstrip-1,new_particle.numpad-1) : -9999; //-1 per cominciare a contare da 0
    new_particle.phi      =fGeometryLoaded ? fOscarGeometry->GetPhiStripPad(new_particle.numstrip-1,new_particle.numpad-1) : -9999;
    
    fParticle->push_back(new_particle);
  }
}