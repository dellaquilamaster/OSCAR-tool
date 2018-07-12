#include <EventBuffer.h>

unsigned int Byte2Word(unsigned char *parola)
{
  unsigned int Converted=0;
  Converted=(parola[0]<<24);
  Converted=Converted | (parola[1]<<16);
  Converted=Converted | (parola[2]<<8);
  Converted=Converted | (parola[3]);
  return Converted;
}

/*restituisce 0 se word pari, 1 viceversa*/
int TestParity(unsigned int WordToCheck)
{
  int sum=0;
  
  for(int i=0; i<32; i++)
  {
    sum+=WordToCheck&1;
    WordToCheck>>=1;
  }
  
  return sum%2;  
}

EventBuffer::EventBuffer() :
FileLength(0)
{}

EventBuffer::~EventBuffer()
{}

/* questa funzione legge tutto il file inizializzando il buffer di eventi
 restituisce il numero di words nel file eccetto l'header*/
unsigned int EventBuffer::InitBuffer (int file_id)
{
  /*clear previous buffer*/
  Clear();
  
  unsigned char ReadBuffer[4];
  
  lseek(file_id,1*4,SEEK_SET); /*mi sposto in avanti di una word per leggere il numero di words del file*/
  /*leggo il numero di word nel file*/
  read(file_id,ReadBuffer,4);  
  
  FileLength=Byte2Word(ReadBuffer)-16; /*escludiamo le 16 words iniziali di debugging*/
  
  FileBuffer=new unsigned char[FileLength*4]; /*buffer in cui inserire tutto il file letto*/
  
  lseek(file_id,16*4,SEEK_SET); /*mi sposto fino all'inizio del primo evento del file saltando l'header*/
  read(file_id,FileBuffer,FileLength*4);  /*lettura dell'intero file sul buffer*/
  
  /*chiusura file*/
  close(file_id);
  
  return FileLength;
}

/*questa funzione riempie un buffer usabile da FAIRRootWriter con tutti gli eventi*/
unsigned int EventBuffer::FillBuffer()
{
  unsigned int TempWord=0;
  unsigned int BufferLength=0;
  unsigned int NumEvents=0;
  
  gStartEvent->push_back(0); /*il primo evento comincia alla word 0*/
  
  for(unsigned int i=0; i<FileLength ; i++)
  {
    TempWord=Byte2Word(FileBuffer+(4*i));
    gBufferVector->push_back(TempWord); /*inserisco in buffer*/
    BufferLength++; /*incremento indicatore lunghezza buffer*/
    if(TempWord==0xFFFFFFFF)
    {
      gStartEvent->push_back(i+1);
      NumEvents++;
    }
  }
    
  return NumEvents;
}

int EventBuffer::TestEventConsistency(unsigned int evt_number)
{
  unsigned int NumWords;
  unsigned int NumMod;
  unsigned int StartingEvent=(*gStartEvent)[evt_number];
  unsigned int EndingEvent=(*gStartEvent)[evt_number+1]-1;

  for(unsigned int j, iglob=StartingEvent; iglob<EndingEvent ; iglob++)
  {
    /*j è un indice che uso soltanto per ciclare fino alla footer word*/
    j=iglob;
    for(NumWords=0; ((*gBufferVector)[j]&FTNMask)==0 ;NumWords++, j++)
    {
      if(!TestParity((*gBufferVector)[j])) return 1; /*test parità fallito*/
      }
    NumMod=((*gBufferVector)[j]&VSNMask) - 1; /*estraggo il numero di modulo dalla footerword (-1 per partire da 0)*/
    if(NumWords!=(((*gBufferVector)[j]&VDWMask)>>VDWOff)) return 2; /* errore numero words non corrisponde alla footnote*/
    /*ciclo su tutto il modulo per (NumWords-1) volte a partire da iglob per verificare la crescenza*/
    for(unsigned int i_module=1; i_module<NumWords; i_module++)
    {      
      if(pMask(NumMod)->DWN((*gBufferVector)[iglob+1]) <= pMask(NumMod)->DWN((*gBufferVector)[iglob]))
        return 3; /*errore di crescenza*/
      iglob++;
    }
    iglob++; /*salto l'ultimo word dell'evento perché il ciclo precedente si chiude al penultimo che viene confrontato con il successivo*/
    /*qui iglob identifica una footerword*/
  }
  return 0;
}

void EventBuffer::Clear()
{
  if(FileBuffer!=(unsigned char *)NULL)
    delete[] FileBuffer;
  FileLength=0;
  gStartEvent->clear();
  gBufferVector->clear();
  return;
}