#ifndef OSOSCARMAP_H
#define OSOSCARMAP_H

#include <string>

#include <OSDetectorMap.h>

#include <OSCARShared.h>

class OSOSCARMap : public OSDetectorMap
{
public:
  OSOSCARMap(const char *, int);
  ~OSOSCARMap();

  int ParseMapLine(const char *) override;
  void Clear() override;

  int GetStripEnergyModule(int num_tel, int num_det) const {return fStripEnergyModule[num_tel][num_det-1];}
  int GetStripEnergyChannel(int num_tel, int num_det) const {return fStripEnergyChannel[num_tel][num_det-1];}
  int GetStripTimeModule(int num_tel, int num_det) const {return fStripTimeModule[num_tel][num_det-1];}
  int GetStripTimeChannel(int num_tel, int num_det) const {return fStripTimeChannel[num_tel][num_det-1];}
  int GetPadEnergyModule(int num_tel, int num_det) const {return fPadEnergyModule[num_tel][num_det-1];}
  int GetPadEnergyChannel(int num_tel, int num_det) const {return fPadEnergyChannel[num_tel][num_det-1];}
  int GetPadTimeModule(int num_tel, int num_det) const {return fPadTimeModule[num_tel][num_det-1];}
  int GetPadTimeChannel(int num_tel, int num_det) const {return fPadTimeChannel[num_tel][num_det-1];}
  
private:
  int fNumTelescopes;
  int **fStripEnergyModule;
  int **fStripEnergyChannel;
  int **fStripTimeModule;
  int **fStripTimeChannel;
  int **fPadEnergyModule;
  int **fPadEnergyChannel;
  int **fPadTimeModule;
  int **fPadTimeChannel;
};

#endif