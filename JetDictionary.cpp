// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME JetDictionary
#define R__NO_DEPRECATION

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

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "jetdict.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR_Dictionary();
   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR_TClassManip(TClass*);
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p = 0);
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(Long_t size, void *p);
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p);
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p);
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>*)
   {
      ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>));
      static ::ROOT::TGenericClassInfo 
         instance("fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>", "SharedPtr.hh", 121,
                  typeid(::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR_Dictionary, isa_proxy, 4,
                  sizeof(::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>) );
      instance.SetNew(&new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR);
      instance.SetNewArray(&newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR);
      instance.SetDelete(&delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR);
      instance.SetDeleteArray(&deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR);
      instance.SetDestructor(&destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>*)
   {
      return GenerateInitInstanceLocal((::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>*)0x0)->GetClass();
      fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR_TClassManip(theClass);
   return theClass;
   }

   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr_Dictionary();
   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr_TClassManip(TClass*);
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p = 0);
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(Long_t size, void *p);
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p);
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p);
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr*)
   {
      ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr));
      static ::ROOT::TGenericClassInfo 
         instance("fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr", "SharedPtr.hh", 299,
                  typeid(::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr_Dictionary, isa_proxy, 4,
                  sizeof(::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr) );
      instance.SetNew(&new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr);
      instance.SetNewArray(&newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr);
      instance.SetDelete(&delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr);
      instance.SetDeleteArray(&deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr);
      instance.SetDestructor(&destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr*)
   {
      return GenerateInitInstanceLocal((::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr*)0x0)->GetClass();
      fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr_TClassManip(theClass);
   return theClass;
   }

   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR_Dictionary();
   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR_TClassManip(TClass*);
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p = 0);
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(Long_t size, void *p);
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p);
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p);
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>*)
   {
      ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>));
      static ::ROOT::TGenericClassInfo 
         instance("fastjet::SharedPtr<fastjet::PseudoJetStructureBase>", "SharedPtr.hh", 121,
                  typeid(::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR_Dictionary, isa_proxy, 4,
                  sizeof(::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>) );
      instance.SetNew(&new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR);
      instance.SetNewArray(&newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR);
      instance.SetDelete(&delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR);
      instance.SetDeleteArray(&deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR);
      instance.SetDestructor(&destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>*)
   {
      return GenerateInitInstanceLocal((::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>*)0x0)->GetClass();
      fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR_TClassManip(theClass);
   return theClass;
   }

   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr_Dictionary();
   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr_TClassManip(TClass*);
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p = 0);
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(Long_t size, void *p);
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p);
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p);
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr*)
   {
      ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr));
      static ::ROOT::TGenericClassInfo 
         instance("fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr", "SharedPtr.hh", 299,
                  typeid(::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr_Dictionary, isa_proxy, 4,
                  sizeof(::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr) );
      instance.SetNew(&new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr);
      instance.SetNewArray(&newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr);
      instance.SetDelete(&delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr);
      instance.SetDeleteArray(&deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr);
      instance.SetDestructor(&destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr*)
   {
      return GenerateInitInstanceLocal((::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr*)0x0)->GetClass();
      fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr_TClassManip(theClass);
   return theClass;
   }

   static void fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *fastjetcLcLPseudoJetStructureBase_Dictionary();
   static void fastjetcLcLPseudoJetStructureBase_TClassManip(TClass*);
   static void *new_fastjetcLcLPseudoJetStructureBase(void *p = 0);
   static void *newArray_fastjetcLcLPseudoJetStructureBase(Long_t size, void *p);
   static void delete_fastjetcLcLPseudoJetStructureBase(void *p);
   static void deleteArray_fastjetcLcLPseudoJetStructureBase(void *p);
   static void destruct_fastjetcLcLPseudoJetStructureBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastjet::PseudoJetStructureBase*)
   {
      ::fastjet::PseudoJetStructureBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::fastjet::PseudoJetStructureBase));
      static ::ROOT::TGenericClassInfo 
         instance("fastjet::PseudoJetStructureBase", "PseudoJetStructureBase.hh", 59,
                  typeid(::fastjet::PseudoJetStructureBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &fastjetcLcLPseudoJetStructureBase_Dictionary, isa_proxy, 4,
                  sizeof(::fastjet::PseudoJetStructureBase) );
      instance.SetNew(&new_fastjetcLcLPseudoJetStructureBase);
      instance.SetNewArray(&newArray_fastjetcLcLPseudoJetStructureBase);
      instance.SetDelete(&delete_fastjetcLcLPseudoJetStructureBase);
      instance.SetDeleteArray(&deleteArray_fastjetcLcLPseudoJetStructureBase);
      instance.SetDestructor(&destruct_fastjetcLcLPseudoJetStructureBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastjet::PseudoJetStructureBase*)
   {
      return GenerateInitInstanceLocal((::fastjet::PseudoJetStructureBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastjet::PseudoJetStructureBase*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *fastjetcLcLPseudoJetStructureBase_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::fastjet::PseudoJetStructureBase*)0x0)->GetClass();
      fastjetcLcLPseudoJetStructureBase_TClassManip(theClass);
   return theClass;
   }

   static void fastjetcLcLPseudoJetStructureBase_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *fastjetcLcLPseudoJet_Dictionary();
   static void fastjetcLcLPseudoJet_TClassManip(TClass*);
   static void *new_fastjetcLcLPseudoJet(void *p = 0);
   static void *newArray_fastjetcLcLPseudoJet(Long_t size, void *p);
   static void delete_fastjetcLcLPseudoJet(void *p);
   static void deleteArray_fastjetcLcLPseudoJet(void *p);
   static void destruct_fastjetcLcLPseudoJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastjet::PseudoJet*)
   {
      ::fastjet::PseudoJet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::fastjet::PseudoJet));
      static ::ROOT::TGenericClassInfo 
         instance("fastjet::PseudoJet", "PseudoJet.hh", 67,
                  typeid(::fastjet::PseudoJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &fastjetcLcLPseudoJet_Dictionary, isa_proxy, 4,
                  sizeof(::fastjet::PseudoJet) );
      instance.SetNew(&new_fastjetcLcLPseudoJet);
      instance.SetNewArray(&newArray_fastjetcLcLPseudoJet);
      instance.SetDelete(&delete_fastjetcLcLPseudoJet);
      instance.SetDeleteArray(&deleteArray_fastjetcLcLPseudoJet);
      instance.SetDestructor(&destruct_fastjetcLcLPseudoJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastjet::PseudoJet*)
   {
      return GenerateInitInstanceLocal((::fastjet::PseudoJet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastjet::PseudoJet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *fastjetcLcLPseudoJet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::fastjet::PseudoJet*)0x0)->GetClass();
      fastjetcLcLPseudoJet_TClassManip(theClass);
   return theClass;
   }

   static void fastjetcLcLPseudoJet_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *fastjetcLcLPseudoJetcLcLUserInfoBase_Dictionary();
   static void fastjetcLcLPseudoJetcLcLUserInfoBase_TClassManip(TClass*);
   static void *new_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p = 0);
   static void *newArray_fastjetcLcLPseudoJetcLcLUserInfoBase(Long_t size, void *p);
   static void delete_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p);
   static void deleteArray_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p);
   static void destruct_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastjet::PseudoJet::UserInfoBase*)
   {
      ::fastjet::PseudoJet::UserInfoBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::fastjet::PseudoJet::UserInfoBase));
      static ::ROOT::TGenericClassInfo 
         instance("fastjet::PseudoJet::UserInfoBase", "PseudoJet.hh", 377,
                  typeid(::fastjet::PseudoJet::UserInfoBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &fastjetcLcLPseudoJetcLcLUserInfoBase_Dictionary, isa_proxy, 4,
                  sizeof(::fastjet::PseudoJet::UserInfoBase) );
      instance.SetNew(&new_fastjetcLcLPseudoJetcLcLUserInfoBase);
      instance.SetNewArray(&newArray_fastjetcLcLPseudoJetcLcLUserInfoBase);
      instance.SetDelete(&delete_fastjetcLcLPseudoJetcLcLUserInfoBase);
      instance.SetDeleteArray(&deleteArray_fastjetcLcLPseudoJetcLcLUserInfoBase);
      instance.SetDestructor(&destruct_fastjetcLcLPseudoJetcLcLUserInfoBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastjet::PseudoJet::UserInfoBase*)
   {
      return GenerateInitInstanceLocal((::fastjet::PseudoJet::UserInfoBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastjet::PseudoJet::UserInfoBase*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *fastjetcLcLPseudoJetcLcLUserInfoBase_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::fastjet::PseudoJet::UserInfoBase*)0x0)->GetClass();
      fastjetcLcLPseudoJetcLcLUserInfoBase_TClassManip(theClass);
   return theClass;
   }

   static void fastjetcLcLPseudoJetcLcLUserInfoBase_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase> : new ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>;
   }
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>[nElements] : new ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p) {
      delete ((::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>*)p);
   }
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p) {
      delete [] ((::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>*)p);
   }
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegR(void *p) {
      typedef ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr : new ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr;
   }
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr[nElements] : new ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p) {
      delete ((::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr*)p);
   }
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p) {
      delete [] ((::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr*)p);
   }
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetcLcLUserInfoBasegRcLcL__SharedCountingPtr(void *p) {
      typedef ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase> : new ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>;
   }
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>[nElements] : new ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p) {
      delete ((::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>*)p);
   }
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p) {
      delete [] ((::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>*)p);
   }
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegR(void *p) {
      typedef ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr : new ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr;
   }
   static void *newArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr[nElements] : new ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p) {
      delete ((::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr*)p);
   }
   static void deleteArray_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p) {
      delete [] ((::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr*)p);
   }
   static void destruct_fastjetcLcLSharedPtrlEfastjetcLcLPseudoJetStructureBasegRcLcL__SharedCountingPtr(void *p) {
      typedef ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastjetcLcLPseudoJetStructureBase(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::PseudoJetStructureBase : new ::fastjet::PseudoJetStructureBase;
   }
   static void *newArray_fastjetcLcLPseudoJetStructureBase(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::PseudoJetStructureBase[nElements] : new ::fastjet::PseudoJetStructureBase[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastjetcLcLPseudoJetStructureBase(void *p) {
      delete ((::fastjet::PseudoJetStructureBase*)p);
   }
   static void deleteArray_fastjetcLcLPseudoJetStructureBase(void *p) {
      delete [] ((::fastjet::PseudoJetStructureBase*)p);
   }
   static void destruct_fastjetcLcLPseudoJetStructureBase(void *p) {
      typedef ::fastjet::PseudoJetStructureBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastjet::PseudoJetStructureBase

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastjetcLcLPseudoJet(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::PseudoJet : new ::fastjet::PseudoJet;
   }
   static void *newArray_fastjetcLcLPseudoJet(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::PseudoJet[nElements] : new ::fastjet::PseudoJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastjetcLcLPseudoJet(void *p) {
      delete ((::fastjet::PseudoJet*)p);
   }
   static void deleteArray_fastjetcLcLPseudoJet(void *p) {
      delete [] ((::fastjet::PseudoJet*)p);
   }
   static void destruct_fastjetcLcLPseudoJet(void *p) {
      typedef ::fastjet::PseudoJet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastjet::PseudoJet

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::PseudoJet::UserInfoBase : new ::fastjet::PseudoJet::UserInfoBase;
   }
   static void *newArray_fastjetcLcLPseudoJetcLcLUserInfoBase(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::fastjet::PseudoJet::UserInfoBase[nElements] : new ::fastjet::PseudoJet::UserInfoBase[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p) {
      delete ((::fastjet::PseudoJet::UserInfoBase*)p);
   }
   static void deleteArray_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p) {
      delete [] ((::fastjet::PseudoJet::UserInfoBase*)p);
   }
   static void destruct_fastjetcLcLPseudoJetcLcLUserInfoBase(void *p) {
      typedef ::fastjet::PseudoJet::UserInfoBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastjet::PseudoJet::UserInfoBase

namespace ROOT {
   static TClass *vectorlEfastjetcLcLPseudoJetgR_Dictionary();
   static void vectorlEfastjetcLcLPseudoJetgR_TClassManip(TClass*);
   static void *new_vectorlEfastjetcLcLPseudoJetgR(void *p = 0);
   static void *newArray_vectorlEfastjetcLcLPseudoJetgR(Long_t size, void *p);
   static void delete_vectorlEfastjetcLcLPseudoJetgR(void *p);
   static void deleteArray_vectorlEfastjetcLcLPseudoJetgR(void *p);
   static void destruct_vectorlEfastjetcLcLPseudoJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<fastjet::PseudoJet>*)
   {
      vector<fastjet::PseudoJet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<fastjet::PseudoJet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<fastjet::PseudoJet>", -2, "vector", 386,
                  typeid(vector<fastjet::PseudoJet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfastjetcLcLPseudoJetgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<fastjet::PseudoJet>) );
      instance.SetNew(&new_vectorlEfastjetcLcLPseudoJetgR);
      instance.SetNewArray(&newArray_vectorlEfastjetcLcLPseudoJetgR);
      instance.SetDelete(&delete_vectorlEfastjetcLcLPseudoJetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfastjetcLcLPseudoJetgR);
      instance.SetDestructor(&destruct_vectorlEfastjetcLcLPseudoJetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<fastjet::PseudoJet> >()));

      ::ROOT::AddClassAlternate("vector<fastjet::PseudoJet>","std::vector<fastjet::PseudoJet, std::allocator<fastjet::PseudoJet> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<fastjet::PseudoJet>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfastjetcLcLPseudoJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<fastjet::PseudoJet>*)0x0)->GetClass();
      vectorlEfastjetcLcLPseudoJetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfastjetcLcLPseudoJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfastjetcLcLPseudoJetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<fastjet::PseudoJet> : new vector<fastjet::PseudoJet>;
   }
   static void *newArray_vectorlEfastjetcLcLPseudoJetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<fastjet::PseudoJet>[nElements] : new vector<fastjet::PseudoJet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfastjetcLcLPseudoJetgR(void *p) {
      delete ((vector<fastjet::PseudoJet>*)p);
   }
   static void deleteArray_vectorlEfastjetcLcLPseudoJetgR(void *p) {
      delete [] ((vector<fastjet::PseudoJet>*)p);
   }
   static void destruct_vectorlEfastjetcLcLPseudoJetgR(void *p) {
      typedef vector<fastjet::PseudoJet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<fastjet::PseudoJet>

namespace {
  void TriggerDictionaryInitialization_JetDictionary_Impl() {
    static const char* headers[] = {
"jetdict.h",
0
    };
    static const char* includePaths[] = {
"/home/pasquale/fastjet/include/fastjet",
"/home/pasquale/fastjet/include",
"/home/pasquale/root/include/root",
"/home/pasquale/Trial/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "JetDictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace fastjet{class __attribute__((annotate("$clingAutoload$PseudoJet.hh")))  __attribute__((annotate("$clingAutoload$jetdict.h")))  PseudoJet;}
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
namespace fastjet{class __attribute__((annotate("$clingAutoload$fastjet/PseudoJetStructureBase.hh")))  __attribute__((annotate("$clingAutoload$jetdict.h")))  PseudoJetStructureBase;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "JetDictionary dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "jetdict.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"fastjet::PseudoJet", payloadCode, "@",
"fastjet::PseudoJet::UserInfoBase", payloadCode, "@",
"fastjet::PseudoJetStructureBase", payloadCode, "@",
"fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>", payloadCode, "@",
"fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr", payloadCode, "@",
"fastjet::SharedPtr<fastjet::PseudoJetStructureBase>", payloadCode, "@",
"fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("JetDictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_JetDictionary_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_JetDictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_JetDictionary() {
  TriggerDictionaryInitialization_JetDictionary_Impl();
}
