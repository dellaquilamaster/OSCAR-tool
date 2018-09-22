// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME OSOSCARDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "OSOSCARPad.h"
#include "OSOSCAR.h"
#include "OSOSCARStrip.h"
#include "OSOSCARAnalyzer.h"
#include "OSOSCARTelescope.h"
#include "OSOSCARIdentification.h"
#include "OSOSCARCalibration.h"
#include "OSOSCARGeometry.h"
#include "OSOSCARRootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_OSOSCARData(void *p = 0);
   static void *newArray_OSOSCARData(Long_t size, void *p);
   static void delete_OSOSCARData(void *p);
   static void deleteArray_OSOSCARData(void *p);
   static void destruct_OSOSCARData(void *p);
   static void streamer_OSOSCARData(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OSOSCARData*)
   {
      ::OSOSCARData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OSOSCARData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OSOSCARData", ::OSOSCARData::Class_Version(), "OSOSCARRootEvent.h", 8,
                  typeid(::OSOSCARData), DefineBehavior(ptr, ptr),
                  &::OSOSCARData::Dictionary, isa_proxy, 16,
                  sizeof(::OSOSCARData) );
      instance.SetNew(&new_OSOSCARData);
      instance.SetNewArray(&newArray_OSOSCARData);
      instance.SetDelete(&delete_OSOSCARData);
      instance.SetDeleteArray(&deleteArray_OSOSCARData);
      instance.SetDestructor(&destruct_OSOSCARData);
      instance.SetStreamerFunc(&streamer_OSOSCARData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OSOSCARData*)
   {
      return GenerateInitInstanceLocal((::OSOSCARData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::OSOSCARData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_OSOSCARRootEvent(void *p = 0);
   static void *newArray_OSOSCARRootEvent(Long_t size, void *p);
   static void delete_OSOSCARRootEvent(void *p);
   static void deleteArray_OSOSCARRootEvent(void *p);
   static void destruct_OSOSCARRootEvent(void *p);
   static void streamer_OSOSCARRootEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OSOSCARRootEvent*)
   {
      ::OSOSCARRootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OSOSCARRootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OSOSCARRootEvent", ::OSOSCARRootEvent::Class_Version(), "OSOSCARRootEvent.h", 37,
                  typeid(::OSOSCARRootEvent), DefineBehavior(ptr, ptr),
                  &::OSOSCARRootEvent::Dictionary, isa_proxy, 16,
                  sizeof(::OSOSCARRootEvent) );
      instance.SetNew(&new_OSOSCARRootEvent);
      instance.SetNewArray(&newArray_OSOSCARRootEvent);
      instance.SetDelete(&delete_OSOSCARRootEvent);
      instance.SetDeleteArray(&deleteArray_OSOSCARRootEvent);
      instance.SetDestructor(&destruct_OSOSCARRootEvent);
      instance.SetStreamerFunc(&streamer_OSOSCARRootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OSOSCARRootEvent*)
   {
      return GenerateInitInstanceLocal((::OSOSCARRootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::OSOSCARRootEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr OSOSCARData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OSOSCARData::Class_Name()
{
   return "OSOSCARData";
}

//______________________________________________________________________________
const char *OSOSCARData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OSOSCARData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OSOSCARData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OSOSCARData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr OSOSCARRootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OSOSCARRootEvent::Class_Name()
{
   return "OSOSCARRootEvent";
}

//______________________________________________________________________________
const char *OSOSCARRootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARRootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OSOSCARRootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARRootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OSOSCARRootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARRootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OSOSCARRootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSOSCARRootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void OSOSCARData::Streamer(TBuffer &R__b)
{
   // Stream an object of class OSOSCARData.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b >> fmulti;
      delete [] fnumtel;
      fnumtel = new Int_t[fmulti];
      R__b.ReadFastArray(fnumtel,fmulti);
      delete [] fnumstrip;
      fnumstrip = new Int_t[fmulti];
      R__b.ReadFastArray(fnumstrip,fmulti);
      delete [] fnumpad;
      fnumpad = new Int_t[fmulti];
      R__b.ReadFastArray(fnumpad,fmulti);
      delete [] fEneStrip;
      fEneStrip = new Int_t[fmulti];
      R__b.ReadFastArray(fEneStrip,fmulti);
      delete [] fTimeStrip;
      fTimeStrip = new Int_t[fmulti];
      R__b.ReadFastArray(fTimeStrip,fmulti);
      delete [] fEnePad;
      fEnePad = new Int_t[fmulti];
      R__b.ReadFastArray(fEnePad,fmulti);
      delete [] fTimePad;
      fTimePad = new Int_t[fmulti];
      R__b.ReadFastArray(fTimePad,fmulti);
      delete [] fEneStripCal;
      fEneStripCal = new Double_t[fmulti];
      R__b.ReadFastArray(fEneStripCal,fmulti);
      delete [] fEnePadCal;
      fEnePadCal = new Double_t[fmulti];
      R__b.ReadFastArray(fEnePadCal,fmulti);
      delete [] fTheta;
      fTheta = new Double_t[fmulti];
      R__b.ReadFastArray(fTheta,fmulti);
      delete [] fPhi;
      fPhi = new Double_t[fmulti];
      R__b.ReadFastArray(fPhi,fmulti);
      delete [] fZ;
      fZ = new Int_t[fmulti];
      R__b.ReadFastArray(fZ,fmulti);
      delete [] fA;
      fA = new Int_t[fmulti];
      R__b.ReadFastArray(fA,fmulti);
      delete [] fIdCode;
      fIdCode = new Int_t[fmulti];
      R__b.ReadFastArray(fIdCode,fmulti);
      delete [] fPunchThrough;
      fPunchThrough = new Bool_t[fmulti];
      R__b.ReadFastArray(fPunchThrough,fmulti);
      R__b.CheckByteCount(R__s, R__c, OSOSCARData::IsA());
   } else {
      R__c = R__b.WriteVersion(OSOSCARData::IsA(), kTRUE);
      R__b << fmulti;
      R__b.WriteFastArray(fnumtel,fmulti);
      R__b.WriteFastArray(fnumstrip,fmulti);
      R__b.WriteFastArray(fnumpad,fmulti);
      R__b.WriteFastArray(fEneStrip,fmulti);
      R__b.WriteFastArray(fTimeStrip,fmulti);
      R__b.WriteFastArray(fEnePad,fmulti);
      R__b.WriteFastArray(fTimePad,fmulti);
      R__b.WriteFastArray(fEneStripCal,fmulti);
      R__b.WriteFastArray(fEnePadCal,fmulti);
      R__b.WriteFastArray(fTheta,fmulti);
      R__b.WriteFastArray(fPhi,fmulti);
      R__b.WriteFastArray(fZ,fmulti);
      R__b.WriteFastArray(fA,fmulti);
      R__b.WriteFastArray(fIdCode,fmulti);
      R__b.WriteFastArray(fPunchThrough,fmulti);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OSOSCARData(void *p) {
      return  p ? new(p) ::OSOSCARData : new ::OSOSCARData;
   }
   static void *newArray_OSOSCARData(Long_t nElements, void *p) {
      return p ? new(p) ::OSOSCARData[nElements] : new ::OSOSCARData[nElements];
   }
   // Wrapper around operator delete
   static void delete_OSOSCARData(void *p) {
      delete ((::OSOSCARData*)p);
   }
   static void deleteArray_OSOSCARData(void *p) {
      delete [] ((::OSOSCARData*)p);
   }
   static void destruct_OSOSCARData(void *p) {
      typedef ::OSOSCARData current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_OSOSCARData(TBuffer &buf, void *obj) {
      ((::OSOSCARData*)obj)->::OSOSCARData::Streamer(buf);
   }
} // end of namespace ROOT for class ::OSOSCARData

//______________________________________________________________________________
void OSOSCARRootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class OSOSCARRootEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      fOSCAR.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, OSOSCARRootEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(OSOSCARRootEvent::IsA(), kTRUE);
      fOSCAR.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OSOSCARRootEvent(void *p) {
      return  p ? new(p) ::OSOSCARRootEvent : new ::OSOSCARRootEvent;
   }
   static void *newArray_OSOSCARRootEvent(Long_t nElements, void *p) {
      return p ? new(p) ::OSOSCARRootEvent[nElements] : new ::OSOSCARRootEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_OSOSCARRootEvent(void *p) {
      delete ((::OSOSCARRootEvent*)p);
   }
   static void deleteArray_OSOSCARRootEvent(void *p) {
      delete [] ((::OSOSCARRootEvent*)p);
   }
   static void destruct_OSOSCARRootEvent(void *p) {
      typedef ::OSOSCARRootEvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_OSOSCARRootEvent(TBuffer &buf, void *obj) {
      ((::OSOSCARRootEvent*)obj)->::OSOSCARRootEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::OSOSCARRootEvent

namespace {
  void TriggerDictionaryInitialization_OSOSCARDict_Impl() {
    static const char* headers[] = {
"OSOSCARPad.h",
"OSOSCAR.h",
"OSOSCARStrip.h",
"OSOSCARAnalyzer.h",
"OSOSCARTelescope.h",
"OSOSCARIdentification.h",
"OSOSCARCalibration.h",
"OSOSCARGeometry.h",
"OSOSCARRootEvent.h",
0
    };
    static const char* includePaths[] = {
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/detectors/OSDetector",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/detectors/OSOSCAR",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/OSCARDetectorMap",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/OSRunInfo",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/shared",
"/cern/root-6.04.00/build/include",
"/media/Windows/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/detectors/OSOSCAR/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$OSOSCAR.h")))  OSOSCARData;
class __attribute__((annotate("$clingAutoload$OSOSCAR.h")))  OSOSCARRootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "OSOSCARPad.h"
#include "OSOSCAR.h"
#include "OSOSCARStrip.h"
#include "OSOSCARAnalyzer.h"
#include "OSOSCARTelescope.h"
#include "OSOSCARIdentification.h"
#include "OSOSCARCalibration.h"
#include "OSOSCARGeometry.h"
#include "OSOSCARRootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"OSOSCARData", payloadCode, "@",
"OSOSCARRootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("OSOSCARDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_OSOSCARDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_OSOSCARDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_OSOSCARDict() {
  TriggerDictionaryInitialization_OSOSCARDict_Impl();
}
