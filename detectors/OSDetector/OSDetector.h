#ifndef OSDETECTOR_H
#define OSDETECTOR_H

#include <TTree.h>
#include <OSDetectorMap.h>
#include <map>

class OSDetector
{
public :
  OSDetector(const char *,int num_detectors=0);   //!Constructor
  virtual ~OSDetector();                          //!Destructor
  
  virtual void Clear();                           //!Clear detector data to -9999

  void AssignModule(Int_t, Int_t *);              //!Assign a module to the detector
  void SetMapping(OSDetectorMap *);               //!SetDetector Mapping

  const char * GetName() const;                   //!Returns detector name
  const char * GetType() const;                   //!Returns detector type
  int GetNumDetectors() const;                    //!Get number of individual detection objects (telescopes, bars, sectors, ...)

  virtual void InitTTreeBranch(TTree *);          //!Individually implemented in specific detector classes
  virtual void BuildEvent();                      //!Individually implemented in specific detector classes
  virtual void FillMappedData();                  //!Individually implemented in specific detector classes
  
protected :
  std::string fName;                              //!Detector Name
  std::string fType;                              //!Detector Type
  int fNumDetectors;                              //!Number of individual detection objects (telescopes, bars, sectors, ...)
  OSDetectorMap * fDetectorMap;                   //!Detector Map
  
  std::map<Int_t, Int_t*> *fModuleData;           //!Module Data recorded for the detector
  
};

#endif