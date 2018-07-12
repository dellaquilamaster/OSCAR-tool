#ifndef EVENTBUFFER_
#define EVENTBUFFER_

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

#include <configurator.h>
#include <FAIRRootWriter.h>
#include <mask.h>

#include <OSCARDef.h>

class EventBuffer
{
public:
  EventBuffer();
  ~EventBuffer();
  
  unsigned int InitBuffer(int);
  /*
   * 0 = nessun errore
   * 1 = errore di parità -> rigettare l'evento
   * 2 = errore! numero words lette non corrisponde a footword -> rigettare l'evento
   * 3 = errore di crescenza -> rigettare l'evento
   * 4 = errore di sincronizzazione moduli -> rigettare la parte di file rimanente 
   */
  unsigned int   FillBuffer();
  int   TestEventConsistency(unsigned int);
  void  Clear(); /*clear the buffer*/
  
private:
  unsigned int   FileLength;
  unsigned char *FileBuffer;
  
} ;

#endif