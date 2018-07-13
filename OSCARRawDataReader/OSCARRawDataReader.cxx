#include <OSCARRawDataReader.h>

//____________________________________________________
OSCARRawDataReader::OSCARRawDataReader() :
fFAIRDAQConfiguration(new configurator(file_daqconfig_name)),
fInputTree(new TChain(experiment_name)),
fAnalyzer(0),
fNumEvents(0),
fData(new Int_t *[fFAIRDAQConfiguration->get_number_modules()])
{
  for(unsigned int i=0; i<fFAIRDAQConfiguration->get_number_modules(); i++) {
    fData[i] = new Int_t[fFAIRDAQConfiguration->get_number_channels(i)];
  }
}

//____________________________________________________
OSCARRawDataReader::~OSCARRawDataReader()
{
  delete fFAIRDAQConfiguration;
  for(unsigned int i=0; i<fFAIRDAQConfiguration->get_number_modules(); i++) {
    if (fData[i]) delete [] fData[i];
  }
  delete [] fData;
  delete [] fInputTree;
}

//____________________________________________________
int OSCARRawDataReader::InitRootInput()
{
  return fInputTree->Add(Form("%s%s*.root",file_unpacker_output_path,run_to_analyze));
}

//____________________________________________________
void OSCARRawDataReader::SetAnalyzer(OSCARAnalyzer * TheAnalyer)
{
  fAnalyzer=TheAnalyer;
}

//____________________________________________________
Int_t ** OSCARRawDataReader::GetData() const
{
  return fData;
}

//____________________________________________________
int OSCARRawDataReader::InitReader()
{
  //Configuring input tree
  if(InitRootInput()<=0) {
    printf("OSCARRawDataReader> Error: Failed to open input ROOT tree.\n");
    return -2;
  }
  //Setting input tree branches to fData
  for(unsigned int i=0; i<fFAIRDAQConfiguration->get_number_modules(); i++) {
    fInputTree->SetBranchAddress(Form("m%02d",i+1),fData[i]); 
  }
  printf("OSCARRawDataReader> Data Reader correctly initialized.\n");
  
  return 0;
}

//____________________________________________________
void OSCARRawDataReader::ProcessRawTree()
{
  //Loop on the events
  fNumEvents=fInputTree->GetEntries();
  
  for(Long64_t jentry=0; jentry<fNumEvents; jentry++)
  {
    if((jentry%10000)==0) {
      PrintPercentage(jentry,fNumEvents);
    }
    
    //Loading present raw event
    fInputTree->GetEntry(jentry);
    
    //Map event
    fAnalyzer->MapDetectors();
    
    //Fill mapped data
    fAnalyzer->FillMappedEvent();
  }
}

//____________________________________________________
void OSCARRawDataReader::PrintSummary() const
{
  printf("\n\n-- Analysis Summary --\n");
  printf("Events Unpacked: %llu\n", fNumEvents);
  printf("Good bye!\n\n");
}

//____________________________________________________
void OSCARRawDataReader::EndProcess()
{
  //End of the analysis
  fAnalyzer->EndAnalysis();
}

void OSCARRawDataReader::PrintPercentage(Long64_t jentry, Long64_t nentries) const
{
  std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5) << (100*double(jentry)/nentries) << " %";
  std::cout << "   [";
  int printindex=0;
  for(; printindex<int(100*double(jentry)/nentries); printindex+=5) std::cout << "=";
  for(; printindex<100; printindex+=5) std::cout << " ";
  std::cout << "]\r"; std::cout.flush();
}