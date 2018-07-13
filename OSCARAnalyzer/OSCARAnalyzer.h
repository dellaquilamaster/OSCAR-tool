#ifndef OSCARANALYZER_H
#define OSCARANALYZER_H

#include <TTree.h>
#include <TFile.h>
#include <string>
#include <map>

#include <OSDetector.h>
#include <OSOSCAR.h>
#include <OSSingleTelescope.h>
#include <OSDetectorMap.h>
#include <OSSingleTelescopeMap.h>
#include <OSOSCARMap.h>

#include <OSCARShared.h>

class OSCARAnalyzer
{
public :
  OSCARAnalyzer();
  ~OSCARAnalyzer();
  
  int Init();            //!Initializes the class and calls BuildDetectors. Returns -1 if failed to load detectors from mapping files, returns -2 if failed to open file.
  int BuildDetectors();  //!Builds detectors from mapping file. Returns -1 if failed to open file.
  int InitRootOutput();  //!Initializes Root output file and branches calling individual detectors OSDetector::InitTreeBranch() methods. Returns -1 if failed to open file.
  void RegisterElectronics(Int_t **); //!Register raw data modules
  
  int LoadRegisteredDetectors(const char *);
  int LoadRegisteredModules(const char *);
  int ParseDefineLine(const char *);
  int ParseAssignLine(const char *);
  
  void MapDetectors();      //!Map and analyze an event
  void FillMappedEvent();   //!Fill analized event on tree
  void EndAnalysis();       //!Closes output tree and end the analysis process  
  
  
private :
  TFile * fFileOut;
  TTree * fOutputTree;
  Int_t ** fRawData;        //!Raw data from modules
  
  std::map <std::string, OSDetector *> *fRegisteredDetectors; //!Registered detectors
  

};

#endif