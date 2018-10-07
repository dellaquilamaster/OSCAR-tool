#ifndef OSSINGLETELESCOPEIDENTIFICATION
#define OSSINGLETELESCOPEIDENTIFICATION

#include <TFile.h>
#include <TKey.h>
#include <TClass.h>
#include <TROOT.h>
#include <TCutG.h>
#include <string>
#include <vector>

#include <OSSingleTelescopeRootEvent.h>

typedef struct _OSSingleTelescopeIDStructure
{
  int Z;
  int A;
  bool IsPunchThrough;
  TCutG * TheCut;
} OSSingleTelescopeIDStructure;

/* OSSingleTelescopeIdentification class
 * 06 October 2018 - Daniele Dell'Aquila
 * 
 * this class handles OSSingleTelescope particle identification with the DE-E method
 * 
 */

class OSSingleTelescopeIdentification
{
public :
  OSSingleTelescopeIdentification(const char *);
  ~OSSingleTelescopeIdentification();
  
  void Clear();
  
  Int_t Init (const char * cut_file);
  void  PerformEventIdentification(OSSingleTelescopeData *);
  
private :
  std::string fName;
  bool fIdentificationLoaded;
  std::vector <OSSingleTelescopeIDStructure> fIDCut;
  TFile * fFileInput;
  
};

#endif