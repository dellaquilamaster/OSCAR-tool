#include <FAIRRootWriter.h>

FAIRRootWriter::FAIRRootWriter()
{}

FAIRRootWriter::~FAIRRootWriter()
{}

void FAIRRootWriter::DefineTree(configurator * pConfig, const char * file_name)
{
  ModsNumber = pConfig->get_number_modules();
  pChannelsNumber = new unsigned int [ModsNumber];
  ppData=new unsigned int *[ModsNumber];
  for(unsigned int i=0; i<ModsNumber; i++)
  {
    ppData[i]=new unsigned int[pChannelsNumber[i]=pConfig->get_number_channels(i)]();
  }
  /*opening output file*/
  pfout = new TFile(file_name,"RECREATE");
  pfout->SetCompressionLevel(1);
  /*creation of branches*/
  pTreeOut=new TTree(gRunInfo->GetExperimentName(),gRunInfo->GetExperimentTitle());
  pTreeOut->SetAutoSave(50000000);
  for(unsigned int i=0; i<ModsNumber; i++)
  {
    pTreeOut->Branch(Form("m%02d",i+1), ppData[i], Form("m%02d[%d]/I",i+1,pChannelsNumber[i]));
  }
}

void FAIRRootWriter::ClearTTreeBuffer()
{
  for(unsigned int i=0; i<ModsNumber; i++)
  {
    for(unsigned int j=0; j<pChannelsNumber[i]; j++)
    {
      ppData[i][j]=0;
    }
  }
  return;
}

int FAIRRootWriter::ReadEvent(unsigned int EventNumber, configurator * pConfig)
{
  int ExitCode;
  unsigned int NumMod;
  unsigned int NumWords;
  unsigned int StartingEvent=(*gStartEvent)[EventNumber];
  unsigned int EndingEvent=(*gStartEvent)[EventNumber+1]-1;
  
  /* controllo evento */
  ExitCode=gEventManager->TestEventConsistency(EventNumber);
  switch (ExitCode)
  {
    case 1:
    case 2:
    case 3:
      return ExitCode;
      break;
    case 4:
      return ExitCode; /*File corrotto --> devo rigettare il resto del file con codice 4*/
      break;
  }
  
  /* riempimento del tree */
  for(unsigned int j, iglob=StartingEvent; iglob<EndingEvent ; iglob++) /*questo ciclo è su tutte le footer word dell'evento*/
  {
    /*j è un indice che uso soltanto per ciclare fino alla footer word*/
    j=iglob;
    for(NumWords=0; ((*gBufferVector)[j]&FTNMask)==0 ;NumWords++, j++)
    {}
    NumMod=((*gBufferVector)[j]&VSNMask) - 1; /*estraggo il numero di modulo dalla footerword (-1 per partire da 0)*/
    /*ciclo su tutto il modulo per NumWords volte a partire da iglob*/
    for(unsigned int i_module=0; i_module<NumWords; i_module++)
    {
      ppData[NumMod][pMask(NumMod)->DWN((*gBufferVector)[iglob])]=pMask(NumMod)->Data((*gBufferVector)[iglob]);
      iglob++;
    }
    /*qui iglob identifica una footerword*/
  }
  
  /*scrittura dati su tree*/
  pTreeOut->Fill();
  /*azzeramento della matrice di dati*/
  ClearTTreeBuffer();

  return ExitCode;
}

int FAIRRootWriter::WriteTree()
{
  pTreeOut->AutoSave();
  
  pfout->Close();
  
  return 0;
}