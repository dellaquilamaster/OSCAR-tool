#ifndef OSOSCARTRACKS_H
#define OSOSCARTRACKS_H

#include <Rtypes.h>

typedef struct OSOSCARTracks_
{
  Int_t good_part;
  Int_t IndexStrip[4];
  Int_t IndexPad[4];
} OSOSCARTracks;

#endif