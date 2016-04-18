//
// File generated by /net/home/lzana/root/bin/rootcint at Mon Dec  1 11:07:18 2008

// Do NOT change. Changes will be lost next time file is generated
//

#include "RConfig.h"
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "fidc_cut_allDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TStreamerInfo.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TCollectionProxy.h"
#include "TIsAProxy.h"
// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void TFidCut_ShowMembers(void *obj, TMemberInspector &R__insp, char *R__parent);
   static void TFidCut_Dictionary();
   static void delete_TFidCut(void *p);
   static void deleteArray_TFidCut(void *p);
   static void destruct_TFidCut(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFidCut*)
   {
      ::TFidCut *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TFidCut),0);
      static ::ROOT::TGenericClassInfo 
         instance("TFidCut", "./fidc_cut_all.h", 27,
                  typeid(::TFidCut), DefineBehavior(ptr, ptr),
                  0, &TFidCut_Dictionary, isa_proxy, 0,
                  sizeof(::TFidCut) );
      instance.SetDelete(&delete_TFidCut);
      instance.SetDeleteArray(&deleteArray_TFidCut);
      instance.SetDestructor(&destruct_TFidCut);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFidCut*)
   {
      return GenerateInitInstanceLocal((::TFidCut*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TFidCut*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void TFidCut_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const ::TFidCut*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TFidCut(void *p) {
      delete ((::TFidCut*)p);
   }
   static void deleteArray_TFidCut(void *p) {
      delete [] ((::TFidCut*)p);
   }
   static void destruct_TFidCut(void *p) {
      typedef ::TFidCut current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFidCut

/********************************************************
* dicts/Linux64RHEL4/fidc_cut_allDict.cc
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

extern "C" void G__cpp_reset_tagtablefidc_cut_allDict();

extern "C" void G__set_cpp_environmentfidc_cut_allDict() {
  G__add_compiledheader("TROOT.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("fidc_cut_all.h");
  G__cpp_reset_tagtablefidc_cut_allDict();
}
#include <new>
extern "C" int G__cpp_dllrevfidc_cut_allDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* TFidCut */
static int G__fidc_cut_allDict_757_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TFidCut* p = NULL;
   long gvp = G__getgvp();
   //m: 2
   if ((gvp == G__PVOID) || (gvp == 0)) {
     p = new TFidCut((Char_t*) G__int(libp->para[0]), (Int_t) G__int(libp->para[1]));
   } else {
     p = new((void*) gvp) TFidCut((Char_t*) G__int(libp->para[0]), (Int_t) G__int(libp->para[1]));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   result7->type = 'u';
   result7->tagnum = G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__fidc_cut_allDict_757_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TFidCut*) G__getstructoffset())->CheckCut(*((TVector3*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__fidc_cut_allDict_757_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TFidCut*) G__getstructoffset())->CheckCutPim(*((TVector3*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__fidc_cut_allDict_757_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   TFidCut* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new TFidCut(*(TFidCut*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   result7->type = 'u';
   result7->tagnum = G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef TFidCut G__TTFidCut;
static int G__fidc_cut_allDict_757_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   long gvp = G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 0
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == G__PVOID) {
       delete[] (TFidCut*) soff;
     } else {
       G__setgvp(G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((TFidCut*) (soff+(sizeof(TFidCut)*i)))->~G__TTFidCut();
       }
       G__setgvp(gvp);
     }
   } else {
     if (gvp == G__PVOID) {
       delete (TFidCut*) soff;
     } else {
       G__setgvp(G__PVOID);
       ((TFidCut*) (soff))->~G__TTFidCut();
       G__setgvp(gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__fidc_cut_allDict_757_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TFidCut* dest = (TFidCut*) G__getstructoffset();
   *dest = *(TFidCut*) libp->para[0].ref;
   const TFidCut& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* TFidCut */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncfidc_cut_allDict {
 public:
  G__Sizep2memfuncfidc_cut_allDict() {p=&G__Sizep2memfuncfidc_cut_allDict::sizep2memfunc;}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncfidc_cut_allDict::*p)();
};

size_t G__get_sizep2memfuncfidc_cut_allDict()
{
  G__Sizep2memfuncfidc_cut_allDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritancefidc_cut_allDict() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetablefidc_cut_allDict() {

   /* Setting up typedef entry */
   G__search_typename2("Char_t",99,-1,0,-1);
   G__setnewtype(-1,"Signed Character 1 byte (char)",0);
   G__search_typename2("Int_t",105,-1,0,-1);
   G__setnewtype(-1,"Signed integer 4 bytes (int)",0);
   G__search_typename2("vector<TStreamerInfo*>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<UInt_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TString>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStringcOallocatorlETStringgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStringcOallocatorlETStringgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStringcOallocatorlETStringgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("multimap<void*,Version_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_multimaplEvoidmUcOshortcOlesslEvoidmUgRcOallocatorlEpairlEvoidmUsPconstcOshortgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("multimap<void*,short>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_multimaplEvoidmUcOshortcOlesslEvoidmUgRcOallocatorlEpairlEvoidmUsPconstcOshortgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("multimap<void*,short,less<void*>>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_multimaplEvoidmUcOshortcOlesslEvoidmUgRcOallocatorlEpairlEvoidmUsPconstcOshortgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixT<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTRow_const<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTRow_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTColumn_const<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTColumn_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTDiag_const<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTDiag_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTFlat_const<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTFlat_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSub_const<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSub_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseRow_const<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseRow_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseDiag_const<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseDiag_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTRow<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTRowlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTColumn<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTColumnlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTDiag<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTDiaglEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTFlat<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTFlatlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSub<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSublEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseRow<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseRowlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseDiag<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseDiaglEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TElementActionT<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TElementActionTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TElementPosActionT<Float_t>",117,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TElementPosActionTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* TFidCut */
static void G__setup_memvarTFidCut(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut));
   { TFidCut *p; p=(TFidCut*)0x1000; if (p) { }
   G__memvar_setup((void*)NULL,117,0,0,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TString),-1,-1,4,"fInFile=",0,(char*)NULL);
   G__memvar_setup((void*)NULL,85,0,0,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TF1),-1,-1,4,"fcfun[7][2][4]=",0,(char*)NULL);
   G__memvar_setup((void*)NULL,85,0,0,G__get_linked_tagnum(&G__fidc_cut_allDictLN_TF1),-1,-1,4,"fcfidc_fun[2]=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarfidc_cut_allDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncTFidCut(void) {
   /* TFidCut */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut));
   G__memfunc_setup("TFidCut",659,G__fidc_cut_allDict_757_0_1, 105, G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut), -1, 0, 2, 1, 1, 0, 
"C - 'Char_t' 0 - FileName i - 'Int_t' 0 - part", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("CheckCut",778,G__fidc_cut_allDict_757_0_2, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "u 'TVector3' - 0 - Vector", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("CheckCutPim",1072,G__fidc_cut_allDict_757_0_3, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "u 'TVector3' - 0 - Vector", (char*)NULL, (void*) NULL, 0);
   // automatic copy constructor
   G__memfunc_setup("TFidCut", 659, G__fidc_cut_allDict_757_0_4, (int) ('i'), G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut), -1, 0, 1, 1, 1, 0, "u 'TFidCut' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~TFidCut", 785, G__fidc_cut_allDict_757_0_5, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 0);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__fidc_cut_allDict_757_0_6, (int) ('u'), G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut), -1, 1, 1, 1, 1, 0, "u 'TFidCut' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncfidc_cut_allDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {
}

static void G__cpp_setup_global3() {
}

static void G__cpp_setup_global4() {
}

static void G__cpp_setup_global5() {
}

static void G__cpp_setup_global6() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalfidc_cut_allDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
  G__cpp_setup_global3();
  G__cpp_setup_global4();
  G__cpp_setup_global5();
  G__cpp_setup_global6();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {
}

static void G__cpp_setup_func14() {
}

static void G__cpp_setup_func15() {
}

static void G__cpp_setup_func16() {
}

static void G__cpp_setup_func17() {
}

static void G__cpp_setup_func18() {
}

static void G__cpp_setup_func19() {
}

static void G__cpp_setup_func20() {
}

static void G__cpp_setup_func21() {
}

static void G__cpp_setup_func22() {
}

static void G__cpp_setup_func23() {
}

static void G__cpp_setup_func24() {
}

static void G__cpp_setup_func25() {
}

static void G__cpp_setup_func26() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcfidc_cut_allDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
  G__cpp_setup_func14();
  G__cpp_setup_func15();
  G__cpp_setup_func16();
  G__cpp_setup_func17();
  G__cpp_setup_func18();
  G__cpp_setup_func19();
  G__cpp_setup_func20();
  G__cpp_setup_func21();
  G__cpp_setup_func22();
  G__cpp_setup_func23();
  G__cpp_setup_func24();
  G__cpp_setup_func25();
  G__cpp_setup_func26();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__fidc_cut_allDictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR = { "vector<unsigned int,allocator<unsigned int> >" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_vectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgR = { "vector<TStreamerInfo*,allocator<TStreamerInfo*> >" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TStreamerInfo*,allocator<TStreamerInfo*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TString = { "TString" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_vectorlETStringcOallocatorlETStringgRsPgR = { "vector<TString,allocator<TString> >" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TString,allocator<TString> >::iterator>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_multimaplEvoidmUcOshortcOlesslEvoidmUgRcOallocatorlEpairlEvoidmUsPconstcOshortgRsPgRsPgR = { "multimap<void*,short,less<void*>,allocator<pair<void* const,short> > >" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TElementActionTlEfloatgR = { "TElementActionT<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TElementPosActionTlEfloatgR = { "TElementPosActionT<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTlEfloatgR = { "TMatrixT<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTRow_constlEfloatgR = { "TMatrixTRow_const<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTRowlEfloatgR = { "TMatrixTRow<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTDiag_constlEfloatgR = { "TMatrixTDiag_const<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTColumn_constlEfloatgR = { "TMatrixTColumn_const<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTFlat_constlEfloatgR = { "TMatrixTFlat_const<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTSub_constlEfloatgR = { "TMatrixTSub_const<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTSparseRow_constlEfloatgR = { "TMatrixTSparseRow_const<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTSparseDiag_constlEfloatgR = { "TMatrixTSparseDiag_const<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTColumnlEfloatgR = { "TMatrixTColumn<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTDiaglEfloatgR = { "TMatrixTDiag<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTFlatlEfloatgR = { "TMatrixTFlat<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTSublEfloatgR = { "TMatrixTSub<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTSparseRowlEfloatgR = { "TMatrixTSparseRow<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TMatrixTSparseDiaglEfloatgR = { "TMatrixTSparseDiag<float>" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TVector3 = { "TVector3" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TF1 = { "TF1" , 99 , -1 };
G__linked_taginfo G__fidc_cut_allDictLN_TFidCut = { "TFidCut" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtablefidc_cut_allDict() {
  G__fidc_cut_allDictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_vectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TString.tagnum = -1 ;
  G__fidc_cut_allDictLN_vectorlETStringcOallocatorlETStringgRsPgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_multimaplEvoidmUcOshortcOlesslEvoidmUgRcOallocatorlEpairlEvoidmUsPconstcOshortgRsPgRsPgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TElementActionTlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TElementPosActionTlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTRow_constlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTRowlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTDiag_constlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTColumn_constlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTFlat_constlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTSub_constlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTSparseRow_constlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTSparseDiag_constlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTColumnlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTDiaglEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTFlatlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTSublEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTSparseRowlEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TMatrixTSparseDiaglEfloatgR.tagnum = -1 ;
  G__fidc_cut_allDictLN_TVector3.tagnum = -1 ;
  G__fidc_cut_allDictLN_TF1.tagnum = -1 ;
  G__fidc_cut_allDictLN_TFidCut.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtablefidc_cut_allDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStreamerInfomUcOallocatorlETStreamerInfomUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TString);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_vectorlETStringcOallocatorlETStringgRsPgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_multimaplEvoidmUcOshortcOlesslEvoidmUgRcOallocatorlEpairlEvoidmUsPconstcOshortgRsPgRsPgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTBaselEdoublegR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TElementActionTlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TElementPosActionTlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTRow_constlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTRowlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTDiag_constlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTColumn_constlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTFlat_constlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSub_constlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseRow_constlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseDiag_constlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTColumnlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTDiaglEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTFlatlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSublEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseRowlEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TMatrixTSparseDiaglEfloatgR);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TVector3);
   G__get_linked_tagnum(&G__fidc_cut_allDictLN_TF1);
   G__tagtable_setup(G__get_linked_tagnum(&G__fidc_cut_allDictLN_TFidCut),sizeof(TFidCut),-1,32768,(char*)NULL,G__setup_memvarTFidCut,G__setup_memfuncTFidCut);
}
extern "C" void G__cpp_setupfidc_cut_allDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupfidc_cut_allDict()");
  G__set_cpp_environmentfidc_cut_allDict();
  G__cpp_setup_tagtablefidc_cut_allDict();

  G__cpp_setup_inheritancefidc_cut_allDict();

  G__cpp_setup_typetablefidc_cut_allDict();

  G__cpp_setup_memvarfidc_cut_allDict();

  G__cpp_setup_memfuncfidc_cut_allDict();
  G__cpp_setup_globalfidc_cut_allDict();
  G__cpp_setup_funcfidc_cut_allDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncfidc_cut_allDict();
  return;
}
class G__cpp_setup_initfidc_cut_allDict {
  public:
    G__cpp_setup_initfidc_cut_allDict() { G__add_setup_func("fidc_cut_allDict",(G__incsetup)(&G__cpp_setupfidc_cut_allDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initfidc_cut_allDict() { G__remove_setup_func("fidc_cut_allDict"); }
};
G__cpp_setup_initfidc_cut_allDict G__cpp_setup_initializerfidc_cut_allDict;

