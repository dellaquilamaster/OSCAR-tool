#include <OSOSCARTelescope.h>

//________________________________________________
OSOSCARTelescope::OSOSCARTelescope() :
fmultstrip(0),
fmultpad(0),
fStrips(new OSOSCARStrip[NUM_STRIPS_OSCAR]),
fPads(new OSOSCARPad[NUM_PADS_OSCAR]),
fNumStrips(NUM_STRIPS_OSCAR),
fNumPads(NUM_PADS_OSCAR)
{}

//________________________________________________
OSOSCARTelescope::~OSOSCARTelescope()
{
  delete [] fStrips;
  delete [] fPads;
}

//________________________________________________
int OSOSCARTelescope::GetNumStrips() const
{
  return fNumStrips;
}

//________________________________________________
int OSOSCARTelescope::GetNumPads() const
{
  return fNumPads;
}

//________________________________________________
void OSOSCARTelescope::Clear()
{
  fmultstrip=0;
  fmultpad=0;
}

//________________________________________________
void OSOSCARTelescope::SetStrip(int num_strip, Int_t energy, Int_t time)
{
  fStrips[fmultstrip].efront=energy; 
  fStrips[fmultstrip].timefront=time; 
  fStrips[fmultstrip].numstrip=num_strip;
  fmultstrip++;
}

//________________________________________________
void OSOSCARTelescope::SetPad(int num_pad, Int_t energy, Int_t time)
{
  fPads[fmultpad].epad=energy;
  fPads[fmultpad].timepad=time;
  fPads[fmultpad].numpad=num_pad;
  fmultpad++;  
}