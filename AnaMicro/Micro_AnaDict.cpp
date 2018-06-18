// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Micro_AnaDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
#include "EMU_Track_c.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_EMU_MicroTrack(void *p = 0);
   static void *newArray_EMU_MicroTrack(Long_t size, void *p);
   static void delete_EMU_MicroTrack(void *p);
   static void deleteArray_EMU_MicroTrack(void *p);
   static void destruct_EMU_MicroTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EMU_MicroTrack*)
   {
      ::EMU_MicroTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EMU_MicroTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EMU_MicroTrack", ::EMU_MicroTrack::Class_Version(), "EMU_Track_c.h", 15,
                  typeid(::EMU_MicroTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EMU_MicroTrack::Dictionary, isa_proxy, 4,
                  sizeof(::EMU_MicroTrack) );
      instance.SetNew(&new_EMU_MicroTrack);
      instance.SetNewArray(&newArray_EMU_MicroTrack);
      instance.SetDelete(&delete_EMU_MicroTrack);
      instance.SetDeleteArray(&deleteArray_EMU_MicroTrack);
      instance.SetDestructor(&destruct_EMU_MicroTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EMU_MicroTrack*)
   {
      return GenerateInitInstanceLocal((::EMU_MicroTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EMU_MicroTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EMU_BaseTrack(void *p = 0);
   static void *newArray_EMU_BaseTrack(Long_t size, void *p);
   static void delete_EMU_BaseTrack(void *p);
   static void deleteArray_EMU_BaseTrack(void *p);
   static void destruct_EMU_BaseTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EMU_BaseTrack*)
   {
      ::EMU_BaseTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EMU_BaseTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EMU_BaseTrack", ::EMU_BaseTrack::Class_Version(), "EMU_Track_c.h", 92,
                  typeid(::EMU_BaseTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EMU_BaseTrack::Dictionary, isa_proxy, 4,
                  sizeof(::EMU_BaseTrack) );
      instance.SetNew(&new_EMU_BaseTrack);
      instance.SetNewArray(&newArray_EMU_BaseTrack);
      instance.SetDelete(&delete_EMU_BaseTrack);
      instance.SetDeleteArray(&deleteArray_EMU_BaseTrack);
      instance.SetDestructor(&destruct_EMU_BaseTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EMU_BaseTrack*)
   {
      return GenerateInitInstanceLocal((::EMU_BaseTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EMU_BaseTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EMU_VolumeTrack(void *p = 0);
   static void *newArray_EMU_VolumeTrack(Long_t size, void *p);
   static void delete_EMU_VolumeTrack(void *p);
   static void deleteArray_EMU_VolumeTrack(void *p);
   static void destruct_EMU_VolumeTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EMU_VolumeTrack*)
   {
      ::EMU_VolumeTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EMU_VolumeTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EMU_VolumeTrack", ::EMU_VolumeTrack::Class_Version(), "EMU_Track_c.h", 174,
                  typeid(::EMU_VolumeTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EMU_VolumeTrack::Dictionary, isa_proxy, 4,
                  sizeof(::EMU_VolumeTrack) );
      instance.SetNew(&new_EMU_VolumeTrack);
      instance.SetNewArray(&newArray_EMU_VolumeTrack);
      instance.SetDelete(&delete_EMU_VolumeTrack);
      instance.SetDeleteArray(&deleteArray_EMU_VolumeTrack);
      instance.SetDestructor(&destruct_EMU_VolumeTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EMU_VolumeTrack*)
   {
      return GenerateInitInstanceLocal((::EMU_VolumeTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EMU_VolumeTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EMU_Event(void *p = 0);
   static void *newArray_EMU_Event(Long_t size, void *p);
   static void delete_EMU_Event(void *p);
   static void deleteArray_EMU_Event(void *p);
   static void destruct_EMU_Event(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EMU_Event*)
   {
      ::EMU_Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EMU_Event >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EMU_Event", ::EMU_Event::Class_Version(), "EMU_Track_c.h", 251,
                  typeid(::EMU_Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EMU_Event::Dictionary, isa_proxy, 4,
                  sizeof(::EMU_Event) );
      instance.SetNew(&new_EMU_Event);
      instance.SetNewArray(&newArray_EMU_Event);
      instance.SetDelete(&delete_EMU_Event);
      instance.SetDeleteArray(&deleteArray_EMU_Event);
      instance.SetDestructor(&destruct_EMU_Event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EMU_Event*)
   {
      return GenerateInitInstanceLocal((::EMU_Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EMU_Event*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr EMU_MicroTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EMU_MicroTrack::Class_Name()
{
   return "EMU_MicroTrack";
}

//______________________________________________________________________________
const char *EMU_MicroTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_MicroTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EMU_MicroTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_MicroTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EMU_MicroTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_MicroTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EMU_MicroTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_MicroTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EMU_BaseTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EMU_BaseTrack::Class_Name()
{
   return "EMU_BaseTrack";
}

//______________________________________________________________________________
const char *EMU_BaseTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_BaseTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EMU_BaseTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_BaseTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EMU_BaseTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_BaseTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EMU_BaseTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_BaseTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EMU_VolumeTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EMU_VolumeTrack::Class_Name()
{
   return "EMU_VolumeTrack";
}

//______________________________________________________________________________
const char *EMU_VolumeTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_VolumeTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EMU_VolumeTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_VolumeTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EMU_VolumeTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_VolumeTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EMU_VolumeTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_VolumeTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EMU_Event::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EMU_Event::Class_Name()
{
   return "EMU_Event";
}

//______________________________________________________________________________
const char *EMU_Event::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_Event*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EMU_Event::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EMU_Event*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EMU_Event::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_Event*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EMU_Event::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EMU_Event*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void EMU_MicroTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class EMU_MicroTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EMU_MicroTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(EMU_MicroTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EMU_MicroTrack(void *p) {
      return  p ? new(p) ::EMU_MicroTrack : new ::EMU_MicroTrack;
   }
   static void *newArray_EMU_MicroTrack(Long_t nElements, void *p) {
      return p ? new(p) ::EMU_MicroTrack[nElements] : new ::EMU_MicroTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_EMU_MicroTrack(void *p) {
      delete ((::EMU_MicroTrack*)p);
   }
   static void deleteArray_EMU_MicroTrack(void *p) {
      delete [] ((::EMU_MicroTrack*)p);
   }
   static void destruct_EMU_MicroTrack(void *p) {
      typedef ::EMU_MicroTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EMU_MicroTrack

//______________________________________________________________________________
void EMU_BaseTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class EMU_BaseTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EMU_BaseTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(EMU_BaseTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EMU_BaseTrack(void *p) {
      return  p ? new(p) ::EMU_BaseTrack : new ::EMU_BaseTrack;
   }
   static void *newArray_EMU_BaseTrack(Long_t nElements, void *p) {
      return p ? new(p) ::EMU_BaseTrack[nElements] : new ::EMU_BaseTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_EMU_BaseTrack(void *p) {
      delete ((::EMU_BaseTrack*)p);
   }
   static void deleteArray_EMU_BaseTrack(void *p) {
      delete [] ((::EMU_BaseTrack*)p);
   }
   static void destruct_EMU_BaseTrack(void *p) {
      typedef ::EMU_BaseTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EMU_BaseTrack

//______________________________________________________________________________
void EMU_VolumeTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class EMU_VolumeTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EMU_VolumeTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(EMU_VolumeTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EMU_VolumeTrack(void *p) {
      return  p ? new(p) ::EMU_VolumeTrack : new ::EMU_VolumeTrack;
   }
   static void *newArray_EMU_VolumeTrack(Long_t nElements, void *p) {
      return p ? new(p) ::EMU_VolumeTrack[nElements] : new ::EMU_VolumeTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_EMU_VolumeTrack(void *p) {
      delete ((::EMU_VolumeTrack*)p);
   }
   static void deleteArray_EMU_VolumeTrack(void *p) {
      delete [] ((::EMU_VolumeTrack*)p);
   }
   static void destruct_EMU_VolumeTrack(void *p) {
      typedef ::EMU_VolumeTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EMU_VolumeTrack

//______________________________________________________________________________
void EMU_Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class EMU_Event.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EMU_Event::Class(),this);
   } else {
      R__b.WriteClassBuffer(EMU_Event::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EMU_Event(void *p) {
      return  p ? new(p) ::EMU_Event : new ::EMU_Event;
   }
   static void *newArray_EMU_Event(Long_t nElements, void *p) {
      return p ? new(p) ::EMU_Event[nElements] : new ::EMU_Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_EMU_Event(void *p) {
      delete ((::EMU_Event*)p);
   }
   static void deleteArray_EMU_Event(void *p) {
      delete [] ((::EMU_Event*)p);
   }
   static void destruct_EMU_Event(void *p) {
      typedef ::EMU_Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EMU_Event

namespace ROOT {
   static TClass *vectorlEEMU_VolumeTrackgR_Dictionary();
   static void vectorlEEMU_VolumeTrackgR_TClassManip(TClass*);
   static void *new_vectorlEEMU_VolumeTrackgR(void *p = 0);
   static void *newArray_vectorlEEMU_VolumeTrackgR(Long_t size, void *p);
   static void delete_vectorlEEMU_VolumeTrackgR(void *p);
   static void deleteArray_vectorlEEMU_VolumeTrackgR(void *p);
   static void destruct_vectorlEEMU_VolumeTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<EMU_VolumeTrack>*)
   {
      vector<EMU_VolumeTrack> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<EMU_VolumeTrack>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<EMU_VolumeTrack>", -2, "vector", 447,
                  typeid(vector<EMU_VolumeTrack>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEEMU_VolumeTrackgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<EMU_VolumeTrack>) );
      instance.SetNew(&new_vectorlEEMU_VolumeTrackgR);
      instance.SetNewArray(&newArray_vectorlEEMU_VolumeTrackgR);
      instance.SetDelete(&delete_vectorlEEMU_VolumeTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlEEMU_VolumeTrackgR);
      instance.SetDestructor(&destruct_vectorlEEMU_VolumeTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<EMU_VolumeTrack> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<EMU_VolumeTrack>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEEMU_VolumeTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<EMU_VolumeTrack>*)0x0)->GetClass();
      vectorlEEMU_VolumeTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEEMU_VolumeTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEEMU_VolumeTrackgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<EMU_VolumeTrack> : new vector<EMU_VolumeTrack>;
   }
   static void *newArray_vectorlEEMU_VolumeTrackgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<EMU_VolumeTrack>[nElements] : new vector<EMU_VolumeTrack>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEEMU_VolumeTrackgR(void *p) {
      delete ((vector<EMU_VolumeTrack>*)p);
   }
   static void deleteArray_vectorlEEMU_VolumeTrackgR(void *p) {
      delete [] ((vector<EMU_VolumeTrack>*)p);
   }
   static void destruct_vectorlEEMU_VolumeTrackgR(void *p) {
      typedef vector<EMU_VolumeTrack> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<EMU_VolumeTrack>

namespace ROOT {
   static TClass *vectorlEEMU_MicroTrackgR_Dictionary();
   static void vectorlEEMU_MicroTrackgR_TClassManip(TClass*);
   static void *new_vectorlEEMU_MicroTrackgR(void *p = 0);
   static void *newArray_vectorlEEMU_MicroTrackgR(Long_t size, void *p);
   static void delete_vectorlEEMU_MicroTrackgR(void *p);
   static void deleteArray_vectorlEEMU_MicroTrackgR(void *p);
   static void destruct_vectorlEEMU_MicroTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<EMU_MicroTrack>*)
   {
      vector<EMU_MicroTrack> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<EMU_MicroTrack>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<EMU_MicroTrack>", -2, "vector", 447,
                  typeid(vector<EMU_MicroTrack>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEEMU_MicroTrackgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<EMU_MicroTrack>) );
      instance.SetNew(&new_vectorlEEMU_MicroTrackgR);
      instance.SetNewArray(&newArray_vectorlEEMU_MicroTrackgR);
      instance.SetDelete(&delete_vectorlEEMU_MicroTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlEEMU_MicroTrackgR);
      instance.SetDestructor(&destruct_vectorlEEMU_MicroTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<EMU_MicroTrack> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<EMU_MicroTrack>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEEMU_MicroTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<EMU_MicroTrack>*)0x0)->GetClass();
      vectorlEEMU_MicroTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEEMU_MicroTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEEMU_MicroTrackgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<EMU_MicroTrack> : new vector<EMU_MicroTrack>;
   }
   static void *newArray_vectorlEEMU_MicroTrackgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<EMU_MicroTrack>[nElements] : new vector<EMU_MicroTrack>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEEMU_MicroTrackgR(void *p) {
      delete ((vector<EMU_MicroTrack>*)p);
   }
   static void deleteArray_vectorlEEMU_MicroTrackgR(void *p) {
      delete [] ((vector<EMU_MicroTrack>*)p);
   }
   static void destruct_vectorlEEMU_MicroTrackgR(void *p) {
      typedef vector<EMU_MicroTrack> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<EMU_MicroTrack>

namespace ROOT {
   static TClass *vectorlEEMU_BaseTrackgR_Dictionary();
   static void vectorlEEMU_BaseTrackgR_TClassManip(TClass*);
   static void *new_vectorlEEMU_BaseTrackgR(void *p = 0);
   static void *newArray_vectorlEEMU_BaseTrackgR(Long_t size, void *p);
   static void delete_vectorlEEMU_BaseTrackgR(void *p);
   static void deleteArray_vectorlEEMU_BaseTrackgR(void *p);
   static void destruct_vectorlEEMU_BaseTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<EMU_BaseTrack>*)
   {
      vector<EMU_BaseTrack> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<EMU_BaseTrack>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<EMU_BaseTrack>", -2, "vector", 447,
                  typeid(vector<EMU_BaseTrack>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEEMU_BaseTrackgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<EMU_BaseTrack>) );
      instance.SetNew(&new_vectorlEEMU_BaseTrackgR);
      instance.SetNewArray(&newArray_vectorlEEMU_BaseTrackgR);
      instance.SetDelete(&delete_vectorlEEMU_BaseTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlEEMU_BaseTrackgR);
      instance.SetDestructor(&destruct_vectorlEEMU_BaseTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<EMU_BaseTrack> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<EMU_BaseTrack>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEEMU_BaseTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<EMU_BaseTrack>*)0x0)->GetClass();
      vectorlEEMU_BaseTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEEMU_BaseTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEEMU_BaseTrackgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<EMU_BaseTrack> : new vector<EMU_BaseTrack>;
   }
   static void *newArray_vectorlEEMU_BaseTrackgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<EMU_BaseTrack>[nElements] : new vector<EMU_BaseTrack>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEEMU_BaseTrackgR(void *p) {
      delete ((vector<EMU_BaseTrack>*)p);
   }
   static void deleteArray_vectorlEEMU_BaseTrackgR(void *p) {
      delete [] ((vector<EMU_BaseTrack>*)p);
   }
   static void destruct_vectorlEEMU_BaseTrackgR(void *p) {
      typedef vector<EMU_BaseTrack> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<EMU_BaseTrack>

namespace {
  void TriggerDictionaryInitialization_Micro_AnaDict_Impl() {
    static const char* headers[] = {
"EMU_Track_c.h",
0
    };
    static const char* includePaths[] = {
"/Applications/root_v6.12.04/include",
"/Users/Giuliana/Desktop/PhD/FOOT/FOOT_Analysis/AnaMicro/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Micro_AnaDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$EMU_Track_c.h")))  EMU_MicroTrack;
class __attribute__((annotate("$clingAutoload$EMU_Track_c.h")))  EMU_BaseTrack;
class __attribute__((annotate("$clingAutoload$EMU_Track_c.h")))  EMU_VolumeTrack;
class __attribute__((annotate("$clingAutoload$EMU_Track_c.h")))  EMU_Event;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Micro_AnaDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "EMU_Track_c.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"EMU_BaseTrack", payloadCode, "@",
"EMU_Event", payloadCode, "@",
"EMU_MicroTrack", payloadCode, "@",
"EMU_VolumeTrack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Micro_AnaDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Micro_AnaDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Micro_AnaDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Micro_AnaDict() {
  TriggerDictionaryInitialization_Micro_AnaDict_Impl();
}
