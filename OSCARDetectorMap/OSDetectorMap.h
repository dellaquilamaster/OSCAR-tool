#ifndef OSDETECTORMAP_H
#define OSDETECTORMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

class OSDetectorMap
{
public :
  OSDetectorMap(const char *);
  virtual ~OSDetectorMap();

  virtual void Clear();                              //!Clear mapping

  int LoadMapping(const char *);                     //!Loads detector mapping. Calls individual ParseAssignLine and ParseMapLine of the specific detector mappings
  virtual int ParseMapLine(const char *);            //!Implemented in specific detector mappings

protected :
  std::string fName;
};

#endif