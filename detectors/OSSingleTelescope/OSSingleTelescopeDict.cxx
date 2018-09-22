// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME OSSingleTelescopeDict

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
#include "OSSingleTelescope.h"
#include "OSSingleTelescopeRootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_OSSingleTelescopeData(void *p = 0);
   static void *newArray_OSSingleTelescopeData(Long_t size, void *p);
   static void delete_OSSingleTelescopeData(void *p);
   static void deleteArray_OSSingleTelescopeData(void *p);
   static void destruct_OSSingleTelescopeData(void *p);
   static void streamer_OSSingleTelescopeData(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OSSingleTelescopeData*)
   {
      ::OSSingleTelescopeData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OSSingleTelescopeData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OSSingleTelescopeData", ::OSSingleTelescopeData::Class_Version(), "OSSingleTelescopeRootEvent.h", 8,
                  typeid(::OSSingleTelescopeData), DefineBehavior(ptr, ptr),
                  &::OSSingleTelescopeData::Dictionary, isa_proxy, 16,
                  sizeof(::OSSingleTelescopeData) );
      instance.SetNew(&new_OSSingleTelescopeData);
      instance.SetNewArray(&newArray_OSSingleTelescopeData);
      instance.SetDelete(&delete_OSSingleTelescopeData);
      instance.SetDeleteArray(&deleteArray_OSSingleTelescopeData);
      instance.SetDestructor(&destruct_OSSingleTelescopeData);
      instance.SetStreamerFunc(&streamer_OSSingleTelescopeData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OSSingleTelescopeData*)
   {
      return GenerateInitInstanceLocal((::OSSingleTelescopeData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::OSSingleTelescopeData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_OSSingleTelescopeRootEvent(void *p = 0);
   static void *newArray_OSSingleTelescopeRootEvent(Long_t size, void *p);
   static void delete_OSSingleTelescopeRootEvent(void *p);
   static void deleteArray_OSSingleTelescopeRootEvent(void *p);
   static void destruct_OSSingleTelescopeRootEvent(void *p);
   static void streamer_OSSingleTelescopeRootEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OSSingleTelescopeRootEvent*)
   {
      ::OSSingleTelescopeRootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OSSingleTelescopeRootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OSSingleTelescopeRootEvent", ::OSSingleTelescopeRootEvent::Class_Version(), "OSSingleTelescopeRootEvent.h", 32,
                  typeid(::OSSingleTelescopeRootEvent), DefineBehavior(ptr, ptr),
                  &::OSSingleTelescopeRootEvent::Dictionary, isa_proxy, 16,
                  sizeof(::OSSingleTelescopeRootEvent) );
      instance.SetNew(&new_OSSingleTelescopeRootEvent);
      instance.SetNewArray(&newArray_OSSingleTelescopeRootEvent);
      instance.SetDelete(&delete_OSSingleTelescopeRootEvent);
      instance.SetDeleteArray(&deleteArray_OSSingleTelescopeRootEvent);
      instance.SetDestructor(&destruct_OSSingleTelescopeRootEvent);
      instance.SetStreamerFunc(&streamer_OSSingleTelescopeRootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OSSingleTelescopeRootEvent*)
   {
      return GenerateInitInstanceLocal((::OSSingleTelescopeRootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::OSSingleTelescopeRootEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr OSSingleTelescopeData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OSSingleTelescopeData::Class_Name()
{
   return "OSSingleTelescopeData";
}

//______________________________________________________________________________
const char *OSSingleTelescopeData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OSSingleTelescopeData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OSSingleTelescopeData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OSSingleTelescopeData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr OSSingleTelescopeRootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OSSingleTelescopeRootEvent::Class_Name()
{
   return "OSSingleTelescopeRootEvent";
}

//______________________________________________________________________________
const char *OSSingleTelescopeRootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeRootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OSSingleTelescopeRootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeRootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OSSingleTelescopeRootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeRootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OSSingleTelescopeRootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OSSingleTelescopeRootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void OSSingleTelescopeData::Streamer(TBuffer &R__b)
{
   // Stream an object of class OSSingleTelescopeData.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b >> fEneFirst;
      R__b >> fEneSecond;
      R__b >> fTimeFirst;
      R__b >> fTimeSecond;
      R__b >> fEneFirstCal;
      R__b >> fEneSecondCal;
      R__b >> fTheta;
      R__b >> fPhi;
      R__b >> fZ;
      R__b >> fA;
      R__b >> fIdCode;
      R__b >> fPunchThrough;
      R__b.CheckByteCount(R__s, R__c, OSSingleTelescopeData::IsA());
   } else {
      R__c = R__b.WriteVersion(OSSingleTelescopeData::IsA(), kTRUE);
      R__b << fEneFirst;
      R__b << fEneSecond;
      R__b << fTimeFirst;
      R__b << fTimeSecond;
      R__b << fEneFirstCal;
      R__b << fEneSecondCal;
      R__b << fTheta;
      R__b << fPhi;
      R__b << fZ;
      R__b << fA;
      R__b << fIdCode;
      R__b << fPunchThrough;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OSSingleTelescopeData(void *p) {
      return  p ? new(p) ::OSSingleTelescopeData : new ::OSSingleTelescopeData;
   }
   static void *newArray_OSSingleTelescopeData(Long_t nElements, void *p) {
      return p ? new(p) ::OSSingleTelescopeData[nElements] : new ::OSSingleTelescopeData[nElements];
   }
   // Wrapper around operator delete
   static void delete_OSSingleTelescopeData(void *p) {
      delete ((::OSSingleTelescopeData*)p);
   }
   static void deleteArray_OSSingleTelescopeData(void *p) {
      delete [] ((::OSSingleTelescopeData*)p);
   }
   static void destruct_OSSingleTelescopeData(void *p) {
      typedef ::OSSingleTelescopeData current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_OSSingleTelescopeData(TBuffer &buf, void *obj) {
      ((::OSSingleTelescopeData*)obj)->::OSSingleTelescopeData::Streamer(buf);
   }
} // end of namespace ROOT for class ::OSSingleTelescopeData

//______________________________________________________________________________
void OSSingleTelescopeRootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class OSSingleTelescopeRootEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      fSingleTelescope.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, OSSingleTelescopeRootEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(OSSingleTelescopeRootEvent::IsA(), kTRUE);
      fSingleTelescope.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OSSingleTelescopeRootEvent(void *p) {
      return  p ? new(p) ::OSSingleTelescopeRootEvent : new ::OSSingleTelescopeRootEvent;
   }
   static void *newArray_OSSingleTelescopeRootEvent(Long_t nElements, void *p) {
      return p ? new(p) ::OSSingleTelescopeRootEvent[nElements] : new ::OSSingleTelescopeRootEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_OSSingleTelescopeRootEvent(void *p) {
      delete ((::OSSingleTelescopeRootEvent*)p);
   }
   static void deleteArray_OSSingleTelescopeRootEvent(void *p) {
      delete [] ((::OSSingleTelescopeRootEvent*)p);
   }
   static void destruct_OSSingleTelescopeRootEvent(void *p) {
      typedef ::OSSingleTelescopeRootEvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_OSSingleTelescopeRootEvent(TBuffer &buf, void *obj) {
      ((::OSSingleTelescopeRootEvent*)obj)->::OSSingleTelescopeRootEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::OSSingleTelescopeRootEvent

namespace {
  void TriggerDictionaryInitialization_OSSingleTelescopeDict_Impl() {
    static const char* headers[] = {
"OSSingleTelescope.h",
"OSSingleTelescopeRootEvent.h",
0
    };
    static const char* includePaths[] = {
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/detectors/OSDetector",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/detectors/OSSingleTelescope",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/OSCARDetectorMap",
"/home/daniele/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/shared",
"/cern/root-6.04.00/build/include",
"/media/Windows/Dropbox/Daniele-Ivano/Documenti_Utili/OSCAR-tool/detectors/OSSingleTelescope/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$OSSingleTelescope.h")))  OSSingleTelescopeData;
class __attribute__((annotate("$clingAutoload$OSSingleTelescope.h")))  OSSingleTelescopeRootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "OSSingleTelescope.h"
#include "OSSingleTelescopeRootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"OSSingleTelescopeData", payloadCode, "@",
"OSSingleTelescopeRootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("OSSingleTelescopeDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_OSSingleTelescopeDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_OSSingleTelescopeDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_OSSingleTelescopeDict() {
  TriggerDictionaryInitialization_OSSingleTelescopeDict_Impl();
}
