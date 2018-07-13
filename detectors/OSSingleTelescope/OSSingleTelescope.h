#ifndef OSSINGLETELESCOPE_H
#define OSSINGLETELESCOPE_H

#include <TTree.h>
#include <OSDetector.h>
#include <OSSingleTelescopeRootEvent.h>
#include <OSSingleTelescopeMap.h>

#include <OSCARShared.h>

class OSSingleTelescope : public OSDetector
{
public :
  OSSingleTelescope(const char *);                       //!Constructor
  ~OSSingleTelescope();                                  //!Destructor

  void Clear() override;                                 //!Clear. Not used in the current implementation.

  void InitTTreeBranch(TTree *) override;                //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                            //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                        //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  OSSingleTelescopeRootEvent * fevt;                     //!RootEvent type of the detector

};

#endif