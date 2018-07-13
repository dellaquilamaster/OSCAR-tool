#include <OSCARAnalyzer.h>

//____________________________________________________
OSCARAnalyzer::OSCARAnalyzer() :
fFileOut(0),
fOutputTree(0),
fRawData(0),
fRegisteredDetectors(new std::map <std::string, OSDetector *>)
{}

//____________________________________________________
OSCARAnalyzer::~OSCARAnalyzer()
{
  if(fFileOut) delete fFileOut;
  if(fOutputTree) delete fOutputTree;
  
  for(std::map<std::string, OSDetector *>::iterator TheDetector=fRegisteredDetectors->begin(); TheDetector!=fRegisteredDetectors->end(); TheDetector++) {
    delete (*TheDetector).second;
  }
  
  delete fRegisteredDetectors;
}

//____________________________________________________
int OSCARAnalyzer::Init()
{    
  //Initializing Detectors
  if(BuildDetectors()<0) {
    printf("OSCARAnalyzer> Error: Failed to build detectors.\n");
    return -1; 
  }
 
  //Initializing Output Tree
  if(InitRootOutput()<0) {
    printf("OSCARAnalyzer> Error: Failed to create output tree.\n");
    return -2;
  }
  printf("OSCARAnalyzer> Data Analyzer correctly initialized, created file: %s\n", Form("%s%s.root",file_mapper_output_path,run_to_analyze));
  
  return 0;
}

//____________________________________________________
int OSCARAnalyzer::BuildDetectors()
{ 
  //Build Detectors from mapping file
  if(LoadRegisteredDetectors(file_mapping_name)<=0) {
    return -1; 
  }
  
  //Assign Modules to registered detectors from mapping file
  if(LoadRegisteredModules(file_mapping_name)<=0) {
    return -2; 
  }
  
  //Build Detector mapping
  for(std::map<std::string, OSDetector *>::iterator TheDetector=fRegisteredDetectors->begin(); TheDetector!=fRegisteredDetectors->end(); TheDetector++) {
    std::string DetectorType((*TheDetector).second->GetType());
    if(DetectorType.compare("OSCAR")==0) {
      OSDetectorMap * new_map = new OSOSCARMap((*TheDetector).second->GetName(), (*TheDetector).second->GetNumDetectors());
      new_map->LoadMapping(file_mapping_name);
      (*TheDetector).second->SetMapping(new_map);
    } else if(DetectorType.compare("SingleTelescope")==0) {
      OSDetectorMap * new_map = new OSSingleTelescopeMap((*TheDetector).second->GetName());
      new_map->LoadMapping(file_mapping_name);
      (*TheDetector).second->SetMapping(new_map);      
    } else if(DetectorType.compare("SingleDetector")==0) {
//       OSDetectorMap * new_map = new OSSingleDetectorMap((*TheDetector).second->GetName());
//       new_map->LoadMapping(file_mapping_name);
//       (*TheDetector).second->SetMapping(new_map);
    }
  }
  
  return 0;
}

//________________________________________________
int OSCARAnalyzer::LoadRegisteredDetectors(const char * file_name)
{
  std::ifstream FileIn(file_name);

  if(!FileIn.is_open()) {
    return -1;
  }

  int NDetectorsDefined=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));
    
    
    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("define ")!=std::string::npos) {      
      NDetectorsDefined+=ParseDefineLine(LineReadCommentLess.c_str());
    }
  }
  FileIn.close();

  return NDetectorsDefined;
}

//________________________________________________
int OSCARAnalyzer::LoadRegisteredModules(const char * file_name)
{
  std::ifstream FileIn(file_name);
  
  if(!FileIn.is_open()) {
    return -1;
  }

  int NModulesAssigned=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("assign ")!=std::string::npos) {      
      NModulesAssigned+=ParseAssignLine(LineReadCommentLess.c_str());
    }
  }
  FileIn.close();

  return NModulesAssigned;
}

//________________________________________________
int OSCARAnalyzer::ParseDefineLine(const char * line_to_parse)
{
  int NDetectorsAdded=0;

  std::string LineReadCommentLess(line_to_parse);
  if(LineReadCommentLess.find("detector ")!=std::string::npos) {
    LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("detector ")+9));
    std::istringstream LineStream(LineReadCommentLess);
    std::string DetectorType;
    std::string DetectorName;
    LineStream>>DetectorType>>DetectorName;
    DetectorName.assign(DetectorName.substr(DetectorName.find("\"")+1, DetectorName.find_last_of("\"")-(DetectorName.find("\"")+1)));
    
    if(DetectorType.compare("OSCAR")==0) {
      int NumTelescopes;
      LineStream>>NumTelescopes;      
      OSDetector * new_detector = new OSOSCAR(DetectorName.c_str(),NumTelescopes);
      (*fRegisteredDetectors)[DetectorName]=new_detector;
      NDetectorsAdded++;
    } else if(DetectorType.compare("SingleTelescope")==0) {
      OSDetector * new_detector = new OSSingleTelescope(DetectorName.c_str());
      (*fRegisteredDetectors)[DetectorName]=new_detector;
      NDetectorsAdded++;
    } else if(DetectorType.compare("SingleDetector")==0) {
//       OSDetector * new_detector = new OSSingleDetector(DetectorName.c_str());
//       (*fRegisteredDetectors)[DetectorName]=new_detector;
      NDetectorsAdded++;
    }
  }

  return NDetectorsAdded;
}

//________________________________________________
int OSCARAnalyzer::ParseAssignLine(const char * line_to_parse)
{
  int NModulesAdded=0;

  std::string LineReadCommentLess(line_to_parse);
  if(LineReadCommentLess.find("module ")!=std::string::npos) {
    LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("module ")+7));
    std::istringstream LineStream(LineReadCommentLess);
    std::string DetectorName;
    LineStream>>DetectorName;
    int ModuleNumber;
    while(LineStream>>ModuleNumber) { 
      (*fRegisteredDetectors)[DetectorName]->AssignModule(ModuleNumber,fRawData[ModuleNumber-1]); //WARNING: the vector fRawData starts from 0 while ModuleNumber starts from 1
      NModulesAdded++;
    }
  }

  return NModulesAdded;
}

//____________________________________________________
int OSCARAnalyzer::InitRootOutput()
{
  //Initializing Output File
  fFileOut = new TFile(Form("%s%s.root",file_mapper_output_path,run_to_analyze),"RECREATE");
  if(fFileOut->IsZombie()) {
    return -1;
  }
  fFileOut->SetCompressionLevel(1);
  //Initializing Output Tree
  fOutputTree = new TTree(experiment_name,experiment_title);
  fOutputTree->SetAutoSave(50000000);
  
  //Build individual detector branches
  for(std::map<std::string, OSDetector *>::iterator TheDetector=fRegisteredDetectors->begin(); TheDetector!=fRegisteredDetectors->end(); TheDetector++) {
    (*TheDetector).second->InitTTreeBranch(fOutputTree);
  }

  return 0;
}

//____________________________________________________
void OSCARAnalyzer::RegisterElectronics(Int_t ** TheData)
{
  fRawData=TheData;
}

//____________________________________________________
void OSCARAnalyzer::MapDetectors()
{
  for(std::map<std::string, OSDetector *>::iterator TheDetector=fRegisteredDetectors->begin(); TheDetector!=fRegisteredDetectors->end(); TheDetector++) {
    (*TheDetector).second->BuildEvent();
    (*TheDetector).second->FillMappedData();
  }
}

//____________________________________________________
void OSCARAnalyzer::FillMappedEvent()
{
  //Fill output tree
  fOutputTree->Fill();
}

//____________________________________________________
void OSCARAnalyzer::EndAnalysis()
{
  //Save output tree to file
  fOutputTree->AutoSave();
  
  //Close file
  fFileOut->Close();  
}