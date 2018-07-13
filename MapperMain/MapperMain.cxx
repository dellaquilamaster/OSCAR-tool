/************************************************************************************************************
 * OSCAR-tool -> OSCARMapper
 * 
 * v1.0
 * 12/07/2018
 * Created by Daniele Dell'Aquila (dellaquila.daniele@gmail.com)
 * 
 * This program is a new version of the previous OSCARUNPACKER which has been included in a more complex and 
 * versatile analysis tool to handle OSCAR experiments: OSCAR-tool.
 * 
 * USAGE: OSCARMapper.exe --run=num_run
 * 
 * 
 * **********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <TTree.h>
#include <TH2.h>
#include <TFile.h>

#include <OSCARRawDataReader.h>
#include <OSCARAnalyzer.h>

// #include <TRootEvent.h>
// #include <OAnalyzer.h>
// #include <OCalibration.h>
// #include <OGeometry.h>

#include <MapperPassArgument.h>
#include <OSCARLogo.h>
#include <OSCARShared.h>

int main (int argc, char** argv)
{
  PrintOSCARUnpackerLogo();
  
  //Retrieving run to unpack
  const char * RunToUnpackName = RetrieveRunName(argc,argv);
  //TEMPORARY
  run_to_analyze=RunToUnpackName;
  if(RunToUnpackName==0) {
    printf("Error: Invalid run number or path.\n");
    exit(1);
  }
  
  //Creation of Data Reader
  OSCARRawDataReader * TheReader = new OSCARRawDataReader();
  
  //Initialization of Data Reader
  if(TheReader->InitReader()<0) {
    printf("Error: Failed to initialize data reader\n");
    exit(3);
  }
  
  //Creation of Data Analyzer
  OSCARAnalyzer * TheAnalyzer = new OSCARAnalyzer();
  
  //Register Input Data to the Analyzer
  TheAnalyzer->RegisterElectronics(TheReader->GetData());
  
  //Initialization of Data Analyzer
  if(TheAnalyzer->Init()<0) {
    printf("Error: Failed to initialize data analyzer.\n");
    exit(2);
  }
    
  //Registering Data Analyzer
  TheReader->SetAnalyzer(TheAnalyzer);
  
  printf("\nBeginning of the analysis\n");
  //Main Loop on the events
  TheReader->ProcessRawTree();
  
  //Print of Analysis Summary
  TheReader->PrintSummary();
  
  //End of the Analysis
  TheReader->EndProcess();
    
  return 0;
}
