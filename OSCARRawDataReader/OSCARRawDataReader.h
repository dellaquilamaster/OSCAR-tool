#ifndef OSCARRAWDATAREADER_H
#define OSCARRAWDATAREADER_H

#include <iostream>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>

#include <OSCARAnalyzer.h>

#include <configurator.h>

class OSCARRawDataReader
{
public :
  OSCARRawDataReader();
  ~OSCARRawDataReader();
  
  int InitReader();                       //!Called after mapper and input tree are set to initialize input tree branches. Returns -1 if failed to create TTreeReader. -2 failed to retrieve Root input file(s)
  int InitRootInput();                    //!Initialize ROOT TTree and TFile for input, returns the number of files retrieved
  void SetAnalyzer(OSCARAnalyzer *);      //!Called at the beginning of the unpacking process to set the Analyzer
  void ProcessRawTree();                  //!Executes event-by-event OSCARAnalyzer::MapDetectors() and OSCARAnalyzer::FillMappedEvent()
  void EndProcess();                      //!Called at the end of the mapping process. It calls OSCARAnalyzer::EndAnalysis()
  void PrintSummary() const;              //!Print Mapping summary
  
private :
  configurator * fFAIRDAQConfiguration;   //!TEMPORARY. Configuration of FAIR DAQ
  TChain * fInputTree;                    //!Tree with RAW data
  OSCARAnalyzer * fAnalyzer;              //!OSCARAnalyzer
  Long64_t fNumEvents;                    //!Number of events in the input tree
  
  Int_t ** fData;                         //!Data to read
  
  void PrintPercentage(Long64_t jentry, Long64_t nentries) const;
  
};

#endif