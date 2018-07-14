/************************************************************************************************************
 * OSCAR-tool -> OSCARUnpacker
 * 
 * v1.0
 * 11/07/2018
 * Created by Daniele Dell'Aquila (dellaquila.daniele@gmail.com)
 * 
 * This program is a new version of the previous FAIRUNPACKER which has been included in a more complex and 
 * versatile analysis tool to handle OSCAR experiments: OSCAR-tool.
 * 
 * USAGE: FAIRUnpacker.exe --run=num_run
 * 
 * 
 * **********************************************************************************************************/

/************************************************************************************************************
 * 
 * FFFFFFF   AAAAA   III  RRRRRRR  UU   UU  NN     NN  PPPPPPP   AAAAA   CCCCCC  KK    KK  EEEEEEE  RRRRRRR
 * FF       AA   AA  III  RR   RR  UU   UU  NNNN   NN  PP   PP  AA   AA  CC      KK   KK   EE       RR   RR
 * FF       AA   AA  III  RRRRRRR  UU   UU  NN NN  NN  PP   PP  AA   AA  CC      KK KK     EE       RRRRRRR
 * FFFFFFF  AAAAAAA  III  RRRR     UU   UU  NN  NN NN  PPPPPP   AAAAAAA  CC      KKKK      EEEEEEE  RRRR   
 * FF       AA   AA  III  RR RR    UU   UU  NN   NNNN  PP       AA   AA  CC      KK  KK    EE       RR RR  
 * FF       AA   AA  III  RR  RR   UU   UU  NN    NNN  PP       AA   AA  CC      KK   KK   EE       RR  RR 
 * FF       AA   AA  III  RR   RR  UUUUUUU  NN     NN  PP       AA   AA  CCCCCC  KK    KK  EEEEEEE  RR   RR
 *
 * v. 1.0
 * 17/01/2016
 * v. 2.0
 * 11/10/2018 -> the program has been modified and included in OSCAR-tool.
 * 
 * CREATOR: DANIELE DELL'AQUILA
 *          dellaquila@na.infn.it
 * 
 * Convert FAIR data into a ROOT file.
 * 
 * 
 ************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <TTree.h>
#include <TFile.h>
#include <string.h>

#include <mask.h>
#include <configurator.h>
#include <FAIRRootWriter.h>
#include <EventBuffer.h>
#include <Monitor.h>
#include <UnpackerPassArgument.h>
#include <OSRunInfo.h>

#include <OSCARLogo.h>
#include <OSCARShared.h>

int main (int argc, char** argv)
{
  PrintOSCARUnpackerLogo();
  
  /*variabili utili***********************************************************************************/
  int  file_code[1000]; /*array che contiene i codici dei files aperti per la lettura binaria*/
  /***************************************************************************************************/
  
  //Retrieving run to unpack
  const char * RunToUnpackName = RetrieveRunName(argc,argv);
  if(RunToUnpackName==0) {
    printf("Error: Invalid run number or path.\n");
    exit(1);
  }
  
  //Configuring Experimental Run
  gRunInfo = new OSRunInfo();
  if(gRunInfo->LoadRunConfiguration(RunToUnpackName,"config/OSCAR.conf")<=0) {
    printf("Error: Failed to retrieve run configuration\n");
    exit(-1);
  }
    
  //Create event manager
  gEventManager = new EventBuffer();
  
  //Creation of a buffer vector
  gBufferVector = new std::vector<unsigned int>;
  gStartEvent = new std::vector<unsigned int>;
    
  /*get configuration*/
  gLayout = new configurator(gRunInfo->GetDAQConfigFileName());
  
  /*costruzione della struttura del tree*/
  FAIRRootWriter * RootTools = new FAIRRootWriter();
  RootTools->DefineTree(gLayout, Form("%s%s.root",gRunInfo->GetFAIRUnpackerDataPath(),gRunInfo->GetRunNumber()));
  
  /*Costruzione del monitor eventi*/
  Monitor EvtMonitor;
  
  printf("Unpacking run %s\n",gRunInfo->GetRunNumber());
  /*Inizializzazione del monitor*/
  EvtMonitor.Init();
  //Loop on each dat file
  for(int curr_file=0; ; curr_file++)
  {
    /*apertura file*/  
    const char * file_data_name=Form("%s%s/%s_%06d.dat",gRunInfo->GetRawDataPath(),gRunInfo->GetRunNumber(),gRunInfo->GetRunNumber(),curr_file+1);
    if ((file_code[curr_file]=open(file_data_name,O_RDONLY))==-1) break;
    printf("Unpacking file %s\n",file_data_name);      
    
    /*Inizializzazione del buffer di eventi*/
    gEventManager->InitBuffer(file_code[curr_file]);
    
    /*Riempimento del buffer*/
    unsigned int NumEvents = gEventManager->FillBuffer();
    
    /*loop su tutti gli eventi*/
    for(unsigned int EvtCounter = 0; EvtCounter<NumEvents; EvtCounter++)
    {
      if(EvtMonitor.EndOfEvent(RootTools->ReadEvent(EvtCounter, gLayout))==4)
        break;
    }
  } //end of the main loop
  EvtMonitor.EndOfRun();
  
  /*scrittura del tree su file*/
  RootTools->WriteTree();
  
  return 0; 
}