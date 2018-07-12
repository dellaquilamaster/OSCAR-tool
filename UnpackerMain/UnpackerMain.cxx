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
 * USAGE: OSCARUnpacker --run=start_run-end_run --run=run1,run2,run3,... -exclude=bad_run1,bad_run2,...
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

#include <OSCARLogo.h>
#include <OSCARShared.h>

int main (int argc, char** argv)
{
  PrintOSCARUnpackerLogo();
  
  /*variabili utili***********************************************************************************/
  char file_config_name[]="configuration.conf";
  char file_output_name[]="output.root";
  char file_data_name[100];
  char run_name[100];
  int  numero_runs=argc-1;
  int  file_code[1000]; /*array che contiene i codici dei files aperti per la lettura binaria*/
  /***************************************************************************************************/
  
  //Create event manager
  gEventManager = new EventBuffer();
  
  //Creation of a buffer vector
  gBufferVector = new std::vector<unsigned int>;
  gStartEvent = new std::vector<unsigned int>;;
  
  /*get configuration*/
  gLayout = new configurator(file_config_name);
  
  /*costruzione della struttura del tree*/
  FAIRRootWriter * RootTools = new FAIRRootWriter();
  RootTools->DefineTree(gLayout, file_output_name);
  
  /*Costruzione del monitor eventi*/
  Monitor EvtMonitor;
  
  /*ciclo esterno su tutte le cartelle di run*********************************************************/
  for(int curr_run=0; curr_run<numero_runs; curr_run++)
  {
    strncpy(run_name,strrchr(argv[curr_run+1],'/')+1,13);
    /*ciclo principale di lettura su tutti i files del run*/
    printf("Unpacking run %s\n",run_name);
    /*Inizializzazione del monitor*/
    EvtMonitor.Init();
    for(int curr_file=0; ; curr_file++)
    {
      /*apertura file*/
      sprintf(file_data_name,"%s/%s_%06d.dat",argv[curr_run+1],run_name,curr_file+1);
            
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
    }
    printf("Run %s completed.\n", run_name);
    EvtMonitor.EndOfRun();
  }
  /*fine del ciclo principale*************************************************************************/
  
  /*scrittura del tree su file*/
  RootTools->WriteTree();
  
  return 0; 
}