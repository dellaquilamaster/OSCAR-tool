#ifndef ROOTEVENT_H
#define ROOTEVENT_H

#include <TTree.h>
#include <TFile.h>

#include <stdlib.h>
#include <string.h>
#include <vector>

#include <EventBuffer.h>
#include <configurator.h>
#include <mask.h>
#include <OSRunInfo.h>

#include <OSCARDef.h>
#include <OSCARShared.h>

class FAIRRootWriter
{
public:
  FAIRRootWriter();
  ~FAIRRootWriter();
  
  void DefineTree(configurator *, const char * file_name);
  void ClearTTreeBuffer();
  int  ReadEvent(unsigned int, configurator*);
  int  WriteTree();
  
private:
  TTree         *pTreeOut;
  TFile         *pfout;
  unsigned int **ppData;
  unsigned int   ModsNumber;
  unsigned int  *pChannelsNumber;
  
} ;


#endif