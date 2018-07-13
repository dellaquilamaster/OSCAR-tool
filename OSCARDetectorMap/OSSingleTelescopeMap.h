#ifndef OSSINGLETELESCOPEMAP_H
#define OSSINGLETELESCOPEMAP_H

#include <string>

#include <OSDetectorMap.h>

#include <OSCARShared.h>

class OSSingleTelescopeMap : public OSDetectorMap
{
public:
  OSSingleTelescopeMap(const char *);
  ~OSSingleTelescopeMap();

  int ParseMapLine(const char *) override;
  void Clear() override;

  int GetEnergyFirstModule() const {return fEnergyFirstModule;}
  int GetEnergyFirstChannel() const {return fEnergyFirstChannel;}
  int GetTimeFirstModule() const {return fTimeFirstModule;}
  int GetTimeFirstChannel() const {return fTimeFirstChannel;}
  int GetEnergySecondModule() const {return fEnergySecondModule;}
  int GetEnergySecondChannel() const {return fEnergySecondChannel;}
  int GetTimeSecondModule() const {return fTimeSecondModule;}
  int GetTimeSecondChannel() const {return fTimeSecondChannel;}
  
private:
  int fEnergyFirstModule;
  int fEnergyFirstChannel;
  int fTimeFirstModule;
  int fTimeFirstChannel;
  int fEnergySecondModule;
  int fEnergySecondChannel;
  int fTimeSecondModule;
  int fTimeSecondChannel;

};

#endif