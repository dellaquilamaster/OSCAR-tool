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
  
  //Creation of Data Analyzer
  OSCARAnalyzer * TheAnalyzer = new OSCARAnalyzer();
  
  //Initialization of Data Analyzer
  if(TheAnalyzer->Init()<0) {
    printf("Error: Failed to initialize data analyzer.\n");
    exit(2);
  }
  
  //Creation of Data Reader
  OSCARRawDataReader * TheReader = new OSCARRawDataReader();
  
  //Initialization of Data Reader
  if(TheReader->InitReader()<0) {
    printf("Error: Failed to initialize data reader\n");
    exit(3);
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


  /*
  //Creation of Data Reader
  OscarAnalysisVector DataReader;
  //Initialization of Input Tree
  if(DataReader.InitTree(Form("%s%s.root",file_unpacker_output_path,RunToUnpackName))<0) {
    printf("Error: Failed to open FAIRUNpacker root tree.\n");
    exit(2);
  }
  
  //Pedestal suppression
  //DataReader.EnablePedSuppression();
  //Reader Initialization
  if(!DataReader.Init(parameter_file,pedestal_file,DataChain)) {
    printf("Error: Failed to initialize data reader.\n");
    exit(3);
  }
  
  //Reading Raw data
  DataReader.FillEvtBuffer();
  Events=DataReader.GetEvtBuffer();
  printf("Buffer Filled --> %d events stored\n",Events.size());
  
  //Initialization of the Analyzer
  TRootDefine RootResources;
  if(!RootResources.Open(Form("%s%s.root",file_mapper_output_path,RunToUnpackName))) {
    exit(4);
  }
  OGeometry GeometryModule;
  if(!GeometryModule.Init(geometry_file)){
    exit(4);
  }
  OIdentification IdModule;
  if(!IdModule.Init(dee_file)){
    exit(4);
  }
  OCalibration CalibModule;
  if(!CalibModule.Init(calib_file)){
    exit(4); 
  }
  
  //Construction of the Event Analyzer
  OAnalyzer OscarAnalysis(Events,&RootResources,&GeometryModule,&IdModule,&CalibModule);
  
  //Run Data Analysis
  OscarAnalysis.RunDataAnalysis();
  
  RootResources.Close();
  */
  
