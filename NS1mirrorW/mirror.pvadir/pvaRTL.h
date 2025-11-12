#ifndef _CGEN_RTL_H_
#define _CGEN_RTL_H_

#ifndef _CGEN_GMD_H_
#define _CGEN_GMD_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef WIN32
#include <dlfcn.h>
#endif
#include <stdarg.h>

#include <inttypes.h>

#if defined(__SUN32__) || defined(__SUN64__) || defined(__X86SUN32__) || defined(__X86SUN64__)
#include <ieeefp.h>
#endif
#endif

#undef BUFSIZ
#define BUFSIZ 8096

#ifdef WIN32
#include <float.h>
#define snprintf _snprintf
#define finite _finite
#endif

static int __pvaLevel2Index__ = -1;
static int __pvaLevel2Open__  = 0;
static int *__pvaflag_fastIndexOpen;
static int *__pvanumFast;
static int localCallFast_ = -1;
static int localCallFastID_[4096] = {0};
static double *_flocalCall[4096]  = {0};
static int __pvaEvalDone__ = 1;

#if defined(SunOS_5_64) || defined(suse64) || defined(amd64) || defined(linux64) || defined(__AMD64__) || defined(__LINUX64__) || defined(__SUN64__) || defined(__SUSE64__) || defined(__X86SUN64__)
typedef signed long int pINT64_t;
#else
typedef signed long long int pINT64_t;
#endif
#define V_(p)         (p)
#define V2_(p,n)      ((p)-(n))
#define _pvaMin_(a,b)   ((a)<=(b)?(a):(b))
#define _pvaMax_(a,b)   ((a)>=(b)?(a):(b))
#define pvaSqrt(b)      sqrt(b)
#define pvaInverseSqrt(b) ((b) > 0.0 ? 1.0/sqrt(b) : ((b) < 0.0 ? 0.0 : 1000.0))
#define _pvaDoingIdtIc() (_abstime() <= 0.0)
#define _pvaPower_(a,b) pvaRTLexp((b)*pvaRTLlog(a), 200.0, 7.225973768126e+86)
#define _pva2int_(a)  ((a) >= 0.0 ? (int)((a)+0.5) : (int)((a)-0.5))
#define _pvaSign_(a)  ((a) > 0.0 ? 1.0 : ((a) < 0.0 ? -1.0 : 0.0))
#define OPTION_I(l,r) lhs_i = l; rhs_i = r; \
                      if (lhs_i > rhs_i) { tmp_i = rhs_i; rhs_i = lhs_i; lhs_i = tmp_i; }

#define OPTION_D(l,r) lhs_d = l; rhs_d = r; \
                      if (lhs_d > rhs_d) { tmp_d = rhs_d; rhs_d = lhs_d; lhs_d = tmp_d; }

#define KOVERQ        0.861734e-04
#define __temperature() (*_gmd->__temperature__ - _gmd->__dtemperature__)
#define __pvaDiff__(x) ((x) > 1e+32 ? 1e+32 : ((x) < -1e+32 ? -1e+32 : (x)))
#define vt()          ((*_gmd->__temperature__) * KOVERQ)
#define vt_(temp)     ((temp) * KOVERQ)

#define pvaDdx(x)     (x)

#define Q_TERM        0
#define I_TERM        1
#define TERM_SIZE     2
#define INDEX_SIZE    BUFSIZ /* it will be changed. */

#define DIWOFFSET_Q_  (_gmd->_sim_->pVAtermCount)
#define DIWOFFSET_dQ_ (DIWOFFSET_Q_  + _gmd->_sim_->pVAsize_[Q_TERM])
#define DIWOFFSET_I_  (DIWOFFSET_dQ_ + _gmd->_sim_->pVAderivSize_[Q_TERM])
#define DIWOFFSET_dI_ (DIWOFFSET_I_  + _gmd->_sim_->pVAsize_[I_TERM])

#define OVERRIDDEN_BY_DEFPARAM   1
#define OVERRIDDEN_BY_INST       1

// Used only for Finesim|Primesim to get thread-id from evalProbe
#define PUT_THID(eval,thid) (eval | ((thid + 1) << 2))
#define GET_THID(eval)      (eval > 0x03) ? ((eval >> 2) - 1) : 0
#define GET_PROBE(eval)     (eval & 0x03)

typedef struct term_tbl {
  char *              name;
  char *              diwName;
  int                 is_bus;
  int                 idx;
  int                 portConnected;
  int                 portDir;
  int                 is_port;
} TermTbl_t;

typedef struct term_offset {
  int                 p;
  int                 n;
  int                 derID;
  int                 isUsed;
} TermOffset_t;

typedef struct diw_tbl {
  int                 p;
  int                 n;
  char *              bname;
  int                 derivSize;
  int                 derivStart;
  TermOffset_t *      derivOffset;
  int                 derivSizeTbl;
  int                 filename;
  int                 lineno;
} DiwTbl_t;

typedef struct pvaNoiseRow_t {
  int                 termCount;
  int                 noiseID;
  int                *terms;
  int                *offsets;
} pvaNoiseRow;

typedef struct pvaNoiseMap_t {
  int                 noiseCount;
  pvaNoiseRow        *nsRow;
} pvaNoiseMap;

typedef struct pvaNoiseMerge_t {
  int                 mergeCnt;
  int                *targets;
  int                *sources;
} pvaNoiseMerge;

/*
 * PVA_GMD_REDUCTION
 */
typedef void * (*gmdGetMemType)(void *, int);

typedef struct gmd_hf_noise_t {
  int    (*pvaNStype) (void *_gmd, int noiseID);
  char*  (*pvaNSname) (void *_gmd, int noiseID);
  double (*pvaNSef)   (void *_gmd, int noiseID);
} gmd_hf_noise_t;

typedef struct pvaPortList_t {
struct pvaPortList_t  * next;
  int                   portType;
  int                   start;
  int                   end;
} pvaPortList;
typedef struct gmd_pva_extra_t {
  gmd_hf_noise_t pva_noise;

  int  pva_ports_size;
  int  *pva_ports;
  pvaPortList  *pva_portTop;
  pvaPortList  *pva_portLast;
  int breakHiz;
  int fastSolver;
  int digitalReltol;
  int breakHiz_never;
} gmd_pva_extra_t;

typedef struct gmd_common_t {
  double  _pvaACfreq__;

  void    (*pvaUpdateGmd) (void *gmdReused, void *mem, void **ftable);
  void    (*pvaInstCopyDis)(void *gmd, void *masterDIS, void *copyDIS, pINT64_t new_instID, int new_regionID);
  int     (*pvaSave)(void *gmd, void *dis, FILE *fp);
  int     (*pvaRestore)(void *gmd, void *dis, FILE *fp);
  int     (*pvaSetValue)(void *gmd, void *dis, char *name, int index, double value, int incr_);
  int     (*pvaGetParamAddr) (void *gmdPtr, char *pname, void **addr);
  gmdGetMemType    gmdGetMemFunc;

  void   *mem;
  void   *pvaBypassData;
  int     pvaBypass;
  int     pvaBypassOnOff;
  int     hasSwitchBranch;
  int     hasAnalysisTran;
  int     pvaRefresh;
  int     pvaGmdReduction;
  int     pvaClamp;
  int     pvaHasVwbPort;

  unsigned int flag_vnode : 1;
  unsigned int flag_allCheck : 1;
  unsigned int flag_breakDown : 1;
  unsigned int flag_dioCurrent : 1;
  unsigned int flag_portCurrent : 1;

  unsigned int flag_hasOUTPUT : 1;
  unsigned int flag_hasIO : 1;
  unsigned int flag_hasQuantum : 1;
  unsigned int flag_helpSony : 1;
  unsigned int flag_helpSony2 : 1;

  unsigned int flag_optBytol : 1;
  unsigned int flag_hasPWR : 1;
  unsigned int flag_norton : 1;
  unsigned int flag_laplace : 1;
  unsigned int flag_ptran : 1;
  unsigned int flag_hasTableModel : 1;

  gmd_pva_extra_t  *pvaExtra;
} gmd_common_t;

typedef struct gmd_sim_common_t {
  int   thid_;
  int   pVAtermCount;
  int   pVAdiwSize;
  int  *_pvaSize_;
  int   _pvaTermSize_;

  TermTbl_t *pVAtermTbl;
  DiwTbl_t  *pVAdiwTbl[2];
  int   pVAdiwTblSize[2];
  int   pVAsize_[2];
  int   pVAderivSize_[2];
  void     *hash_diw_[2];
  void     *hash_nodes_;

  int  *_iDX;
  int   _pvaModule_;
  int   _pvaHelpNode_;
  int **__pvaCalls__;
  int **__pvaAllId__;
  void    **__pvaIDX__;
} gmd_sim_common_t;

typedef struct gmd__gen__t {
  void *              vft;  /* gmd_vft_t */

  gmd_common_t *_common_;
  gmd_sim_common_t *_sim_;
} gmd__gen__t;

typedef void pvaFPDestroy (char *inst, void *state, int force);

typedef struct MIstr_t {
  const char *        name; 
  int                 scope;
  const char *        val;
  int                 given;
} MIstr_t;

typedef struct MIint_t {
  const char *        name; 
  int                 scope, val, min, max, given;
} MIint_t;

typedef struct MIreal_t {
  const char *        name; 
  int                 scope;
  double              val, min, max;
  int                 force;
  int                 given;
} MIreal_t;

typedef struct MIra_t {
  const char *        name; 
  int                 scope;
  double              *val;
  unsigned int        force;
  unsigned int        given;
} MIra_t;

typedef struct OPTreal_t {
  int                 type;
  double              lhs;
  double              rhs;
} OPTreal_t;

typedef struct OPTint_t {
  int                 type;
  int                 lhs;
  int                 rhs;
} OPTint_t;

typedef struct pvaLogic_t {
  unsigned int        val;
  unsigned int        extra;
  unsigned int        width;
} pvaLogicType;

typedef struct pvaDisType_t {
  pINT64_t pvaInstID__;
  void * pvaState__;
  void * pvaAccept__;
  int  __noupdate__;
} pvaDisType;

typedef int ** (*pvaGetRTLType) ();
typedef void (*gmdInfoStrType)  (void *);
typedef void (*gmdInfoIntType)  (void *);
typedef void (*gmdInfoRealType) (void *);
typedef void (*gmdInfoRAType) (void *);
typedef int  (*gmdTermCountType) ();
typedef void (*gmdErrorType)    (void);
typedef void (*gmdWarningType)  (void);
typedef void (*gmdEndTextType)  (void);
typedef void (*gmdTextType)     (const char *, ...);
typedef void (*gmdInsNameType)  (char *, int);
typedef void (*gmdWakeUpRegionFunct_t) (int thid, double time_step, double time_min);

#define pvaPower(a,b) ((a)>0.0 ? _pvaPower_(a,b) : pvaPower_(a,b))
#define pvaMax(a,b)   _pvaMax_(a,b)
#define pvaMin(a,b)   _pvaMin_(a,b)

typedef void (*pvaErrValogFunc_t)  (char *, int, char *, ...);
pvaErrValogFunc_t pvaErrValog;
gmdErrorType   gmdErrorFunc;
gmdWarningType gmdWarningFunc;
gmdTextType    gmdTextFunc;
gmdEndTextType gmdEndTextFunc;

typedef int (*pvaLRMFOpenFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, char *fname, char *inst, char *type);
typedef void (*pvaLRMFCloseFunc_t) (int thid, int fileID, double time, int srcfile, int lineno);
typedef void (*pvaLRMFlushFunc_t) (int thid, int srcfile, int lineno, int fileID);
typedef int (*pvaLRMFeofFunc_t) (int thid, int srcfile, int lineno, int fileID);
typedef int (*pvaLRMFseekFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fileID, pINT64_t offset, int operation);
typedef pINT64_t (*pvaLRMFtellFunc_t) (int thid, int srcfile, int lineno, int fileID);
typedef int (*pvaLRMrewindFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fileID);
typedef int (*pvaLRMFGetsFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, char * str, int fp);
typedef int (*pvaLRMFScanfFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp, int numfmt, char *fname, ...);
typedef void (*pvaLRMFErrorFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp,char * fname, ...);
typedef void (*pvaLRMFWarningFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp,char * fname, ...);
typedef void (*pvaLRMFPrintFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp,char * fname, ...);
typedef void (*pvaLRMFPrintfFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp,char * fname, ...);
typedef void (*pvaFStrobeFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp,char * fname, ...);
typedef void (*pvaFMonitorFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int exprID, int fp,char * fname, ...);
typedef void (*pvaFDisplayFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp,char * fname, ...);
typedef void (*pvaLRMFWriteFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp, char * fname, ...);
typedef void (*pvaFDebugFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, int fp,char * fname, ...);
typedef void (*pvaSprintfFunc_t) (char *buf, int len, char *name);
typedef void (*pvaLRMFatalFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, double time, int opt, char *fmt, ...);
typedef void (*pvaLRMErrorFunc_t) (int thid, int regID, pINT64_t instID, int srcfile, int lineno, char *fmt, ...);
typedef void (*pvaLRMPrintFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaLRMPrintfFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaLRMWarningFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaLRMInfoFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaStrobeFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaMonitorFunc_t) (int thid, int regID, pINT64_t instID, int exprID, char * fname, ...);
typedef void (*pvaDisplayFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaWriteFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaLRMDebugFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef void (*pvaSimpleDebugFunc_t) (int thid, int regID, pINT64_t instID, char * fname, ...);
typedef int * (*pvaCharCountLocationFunc_t) (int thid, int regID, pINT64_t instID, int fnumber);
typedef void * (*pvaNewPortListFunc_t) (int portType, int start, int end);
typedef void (*pvaUpdateDC__Func_t) (int thid);
typedef int (*pvaLRMFinish_Current_AnalysisFunc_t) (int thid, char *fname, int lineno, double time, int opt);
typedef void (*pvaLRMCompleteFinishFunc_t) ();
typedef void (*pvaLRMFinishFunc_t) (int thid, char *fname,int lineno,double time, int opt);
typedef void (*pvaLRMStopFunc_t) (int thid, char *fname,int lineno,double time, int opt);
typedef void (*pvaNonconvergenceFunc_t) (int, int);
typedef void (*pvaSetRtlFlgFunc_t) (int what, double data);
typedef void (*pvaRegisterAutoStopFunc_t) (void *base, int *id);
typedef void (*pvaSetInsideInitialFunc_t) (int inside);
typedef int (*pvaSaveAnalogObjsFunc_t) (void **objs, int count, FILE *fp);
typedef int (*pvaRestoreAnalogObjsFunc_t) (void **objs, int count, FILE *fp);
typedef int (*pvaRandomFunc_t) (int thid, pINT64_t instID, int seed, int *update);
typedef double (*pvaDistUniformFunc_t) (int thid, pINT64_t instID, int seed, double start, double end, int *update);
typedef double (*pvaDistNormalFunc_t) (int thid, pINT64_t instID, int seed, double mean, double dev, int *update);
typedef double (*pvaDistExponentialFunc_t) (int thid, pINT64_t instID, int seed, double mean, int *update);
typedef double (*pvaDistPoissonFunc_t) (int thid, pINT64_t instID, int seed, double mean, int *update);
typedef double (*pvaDistChiSquareFunc_t) (int thid, pINT64_t instID, int seed, double deg, int *update);
typedef double (*pvaDistTFunc_t) (int thid, pINT64_t instID, int seed, double degree, int *update);
typedef double (*pvaDistErlangFunc_t) (int thid, pINT64_t instID, int seed, double k_stage, double mean, int *update);
typedef void (*pvaRandomUpdateSeedsFunc_t) (int thid, pINT64_t);
typedef void (*pvaRandomInitFunc_t) (int num_of_thid);
typedef void (*pvaRandomInit2SeedsFunc_t) ();
typedef double (*pvaRTLclog2Func_t) (double);
typedef double (*pvaLnFunc_t) (double);
typedef double (*pvaLogFunc_t) (double);
typedef double (*pvaLog10Func_t) (double);
typedef double (*pvaRTLlogFunc_t) (double);
typedef double (*pvaRTLlog10Func_t) (double);
typedef double (*pvaRTLlog_derivFunc_t) (double);
typedef double (*pvaRTLlog10_derivFunc_t) (double);
typedef int (*pvaSimulatorFunc_t) (void);
typedef double (*pvaCMIwarningFunc_t) (double, double, double);
typedef double (*pva_exp_srcFunc_t) (double);
typedef double (*pva_get_expmaxFunc_t) (int);
typedef double (*pvaDivideFunc_t) (int thid, double, double, char *, int);
typedef double (*pvaDiv_Func_t) (int thid, double, double, char *, int);
typedef double (*pvaUseDelta_Func_t) (double, double);
typedef double (*pvaUseGmin_Func_t) (double);
typedef double (*pvaUseCmin_Func_t) (double);
typedef double (*pvaUseUnity_Func_t) (int thid, double);
typedef void (*pvaChkRHSNanInf__Func_t) (int thid, double *, double, char *);
typedef double (*pvaCheckNanInfRHS__Func_t) (int thid, int term, double, char *, char *);
typedef double (*pvaRealExpFunc_t) (double, int, int, int);
typedef double (*pvaRTLexpFunc_t) (double, double, double);
typedef double (*pvaRTLexp1pFunc_t) (double, double, double);
typedef double (*pvaRTLpowerFunc_t) (double, double);
typedef double (*pvaMinFunc_t) (double, double);
typedef double (*pvaMaxFunc_t) (double, double);
typedef double (*pvaAbsFunc_t) (double);
typedef double (*pvaFloorFunc_t) (double);
typedef double (*pvaCeilFunc_t) (double);
typedef double (*pvaTruncFunc_t) (double);
typedef double (*pvaModFunc_t) (double, double, int, int);
typedef double (*pvaPower_Func_t) (double, double);
typedef double (*pvaPowerIntFunc_t) (double, int);
typedef double (*pvaPowerInt2Func_t) (int, int);
typedef int (*pvaIntPowerFunc_t) (int, int);
typedef double (*pvaAsinFunc_t) (double);
typedef double (*pvaAsin1pFunc_t) (double);
typedef double (*pvaAcosFunc_t) (double);
typedef double (*pvaAcos1pFunc_t) (double);
typedef double (*pvaAcoshFunc_t) (double);
typedef double (*pvaAtanhFunc_t) (double);
typedef double (*pvaScaled__Func_t) (int);
typedef int (*pvaRealEQFunc_t) (double, double);
typedef int (*pvaRealLEFunc_t) (double, double);
typedef int (*pvaRealLTFunc_t) (double, double);
typedef int (*pvaRealGTFunc_t) (double, double);
typedef int (*pvaRealGEFunc_t) (double, double);
typedef int (*pvaRealNEFunc_t) (double, double);
typedef int (*pvaIntShiftLFunc_t) (int, int);
typedef int (*pvaIntShiftRFunc_t) (int, int);
typedef double (*pvaTimeStepFunc_t) (int thid, int);
typedef double (*pvaTimeStepTypeFunc_t) (int thid, int);
typedef int (*pvaAcFinalStepFunc_t) (double, int);
typedef double (*pvaCpuTimeFunc_t) (int, pINT64_t, int);
typedef void (*pvaRegisterEvalFunc_t) (int, int, int);
typedef int (*pvaAcceptTimePointFunc_t) (int thid, void *dis, int regID, pINT64_t instID, char *hierName, int has_strobe, double time);
typedef void (*pvaPreIterationFunc_t) (int thid, int monID, int regID, pINT64_t instID, void *gmd, void *base, char *hierName, int has_strobe, double time, double temp, char *vafile, char *modName, int isAC);
typedef void (*pvaPreIteration2Func_t) (int thid, int regID, pINT64_t instID, char *hierName, double time, double temp, char *vafile);
typedef void (*pvaEndIterationFunc_t) (int thid, int monID, int regID, pINT64_t instID, char *hierName, int has_strobe, double time, double temp, char *vafile);
typedef int (*pvaIsSkipEvalNotifySimModeFunc_t) (int thid);
typedef int (*pvaInitStepFunc_t) (int thid, int mode, double time, int isAC);
typedef int (*pvaFinalStepFunc_t) (int thid, int mode, double time, int isAC);
typedef int (*pvaFinalStepSimpleFunc_t) (double time);
typedef double (*pvaGetFinalTimeFunc_t) ();
typedef int (*pvaAnalysisFunc_t) (int thid, int mode, double time, int isAC);
typedef double (*pvaSimparamFunc_t) (int thid, char *name, double def, int filename, int lineno);
typedef void (*pvaSimCopyDisFunc_t) (void *gmd_, void *masterDis, void *copyDis, pINT64_t new_instID, int new_regionID);
typedef int (*pvaSimSaveFunc_t) (void *gmd_, void *dis, FILE *fp);
typedef int (*pvaSimRestoreFunc_t) (void *gmd_, void *dis, FILE *fp);
typedef int (*pvaSimSetValueFunc_t) (void *gmd_, void *dis, char *name, int index, double value, int incr_);
typedef void (*pvaGetSimParamsFunc_t) (gmdInfoRealType infoReal);
typedef int (*pvaSupportNullPortFunc_t) ();
typedef void (*pvaProcessSimulatorOptsFunc_t) (void * infoReal, int enable, char *rtl_flags, int initial);
typedef void (*pvaProcessSimulatorEpva2pvaFunc_t) (int thid, FILE *, int);
typedef void (*pvaWriteChkPtLineFunc_t) (char *line);
typedef int (*pvaAbsDeltaFunc_t) (int thid, void * dis, int loc, int loop, int size, double time, double expr, double delta, double ttol, double vtol, int enable, char *name, char *node);
typedef double (*pvaTransitionFunc_t) (int thid, void * dis, int loc, double *dscale, int loop, int size, double time, double expr, double delay, double tr, double tf, double tol, int evalProbe, int flags);
typedef int (*pvaCrossMFunc_t) (int thid, void * dis, int loc, int loop, int size, double time, double *expr, int *direction);
typedef int (*pvaCrossFunc_t) (int thid, void * dis, void *gmd, int loc, int loop, int size, double time, char *refer, double expr, int direction, double tol, double tol2, int en, int tighter);
typedef double (*pvaLastCrossingFunc_t) (int thid, void * dis, int loc, int loop, double time, double expr, int direction);
typedef int (*pvaAboveFunc_t) (int thid, void * dis, void *gmd, int loc, int loop, int size, double time, char *refer, double expr, double tol, double tol2, int en);
typedef double (*pvaDelayFunc_t) (int thid, void * dis, int loc, int loop, int size, int ac, double *d, double time, double expr, double td, double maxDelay);
typedef double (*pvaSlewFunc_t) (int thid, void *, int, int, int, int, double, double, double, double, double *);
typedef int (*pvaTimerFunc_t) (int, void *, void *, int loop, int loc, int count, int fast, double time, double stop, double period, double tol, int en, char *fname, int lineno, int isAC);
typedef double (*pvaIdtFunc_t) (int thid, void *dis, int ic_flag, pINT64_t instID, int loc, int loop, double t, double val, double ic, int assert_val, double tol);
typedef double (*pvaIdt_order2Func_t) (int thid, void *dis, int ic_flag, pINT64_t instID, int loc, int loop, double t, double val, double ic);
typedef double (*pvaIdtmodFunc_t) (int thid, void *dis, int ic_flag, pINT64_t instID, int loc, int loop, double t, double val, double ic, double modulus, double offset, double tol);
typedef double (*pvaIdtDxFunc_t) (int thid, void *dis, int ic_flag, int loc, int loop, double t);
typedef double (*pvaDdtFunc_t) (int thid, void *dis, int loc, int loop, double t, double val, double tol);
typedef double (*pvaDdtDxFunc_t) (int thid, void *dis, int loc, int loop, double t);
typedef double (*pvaLimexpFunc_t) (double coef, double arg, double time, pINT64_t inst, int id, int lpCnt);
typedef double (*pvaLimexpSimpleFunc_t) (int thid, double input);
typedef double (*pvaLimexpDiffFunc_t) (int thid, double input);
typedef double (*pvaLimitFunc_t) (int thid, double access, double time, pINT64_t inst, int id, int lpCnt, double (*func)(int thid, void *, void *, void *, double, double, va_list), ...);
typedef double (*pvaLimitStrFunc_t) (int thid, double access, double time, pINT64_t inst, int id, int lpCnt, char *funcName, ...);
typedef double (*pvaPnjlimFunc_t) (int thid, void *, void *, void *, double, double, va_list);
typedef double (*pvaFetlimFunc_t) (int thid, void *, void *, void *, double, double, va_list);
typedef double (*pvaTableModelEvalFunc_t) (int thid, int srcfile, int lineno, int callCount, void *gmd, char *idStr, char *modName, char *instName, int index, char *file, int locale, int dim, int cnt, char *argType, char *ctrl, ...);
typedef double (*pvaTableModelEvalPFunc_t) (int thid, int srcfile, int lineno, void **tbl, char *modName, char *instName, int index, char *file, int locale, int dim, int cnt, char *argType, char *ctrl, ...);
typedef void (*pvaFreeRuntimeMemoryFunc_t) (int);
typedef int (*pvaAssignRealMeFunc_t) (double *param, double *src, int start, int end);
typedef int (*pvaAssignRealFunc_t) (double **param, double *src, int start, int end, int force);
typedef int (*pvaAssignIntegerFunc_t) (int **param, double *src, int start, int end, int force);
typedef int (*pvaArrayEqualFunc_t) (int *p1, int *p2, int l1, int l2);
typedef double (*_pva2Ac__Func_t) (double);
typedef long long (*_pvaFtoTFunc_t) (double);
typedef int (*pvaIsForHighZsetFunc_t) ();
typedef int (*pvaGetThreadIdFunc_t) ();
typedef double (*pvaSimProbeFunc_t) (int xmr_id, char *iname, char *pname, double expr, int has_expr, int filename, int lineno);
typedef int (*pvaProbeOffsetFunc_t) (void *, char *, char *, int);
typedef double (*pvaSimProbeINHVAFunc_t) (int xmr_id, double value, char *iname, char *pname, double expr, int has_expr, int filename, int lineno);
typedef void (*pvaDiscontinuityFunc_t) (int action);
typedef void (*pvaBoundStep2Func_t) (int thid, void *base, double step, double ct, char *file, int line);
typedef void (*pvaBoundStepFunc_t) (int thid, void *base, double step, double ct, char *file, int line, int hard);
typedef int (*pvaGetNextTimeFunc_t) (int thid, void *base, double time, double * step, int *bk);
typedef void (*pvaWarningFunc_t) (char * fmt, ...);
typedef void (*pvaNIYFunc_t) (char * fmt, ...);
typedef void (*pvaCheckFilePathFunc_t) (int, char *, char *);
typedef int (*pvaInfoStrFuncFunc_t) (char *, char *, char *, char **);
typedef char * (*_pvaItoAFunc_t) (char *,int);
typedef char * (*_pvaFtoAFunc_t) (char *,double);
typedef char * (*pvaStrToupperFunc_t) (char *);
typedef char * (*pvaStrTolowerFunc_t) (char *);
typedef char * (*pvaSubstrFunc_t) (char *, int, int);
typedef char * (*pvaConcatFunc_t) (char *, ...);
typedef char * (*pvaSformatFunc_t) (int, char *, int *, int *, char *, char *, ...);
typedef char * (*pvaValueToStringFunc_t) (int, int);
typedef char * (*pvaBits2StrFunc_t) (char *, int);
typedef char * (*pvaReal2BitsFunc_t) (double);
typedef double (*pvaBits2RealFunc_t) (char *);
typedef int (*pvaGetHierInstNameFunc_t) (pINT64_t, char *);
typedef int (*pvaRevHierInstNameFunc_t) (char *, int *ID, char *);
typedef int (*pvaSetFlagBuildInstFuncFunc_t) (int);
typedef int (*pvaUpdateParameterFunc_t) (int, int *, void *, void *, void *, void *, char *, char *, char *);
typedef int (*pvaInitialOneTimeFunc_t) (int, void *, int, int);
typedef void (*pvaErrorFunc_t) (char *file, int line, char * fmt, ...);
typedef void (*pvaInforFunc_t) (char * fmt, ...);
typedef void (*pvaInforMeFunc_t) (char * fmt, ...);
typedef int (*pvaErrGenCExitFunc_t) ();
typedef void (*pvaErrGenCCountFunc_t) ();
typedef int (*pvaPutStrTblFunc_t) (char *);
typedef char * (*pvaGetStrTblFunc_t) (int);
typedef int (*pvaRTLmemoryFunc_t) (void *ptr);
typedef int (*_pvaSetInitValueFunc_t) (void *gmd_,int termCount);
typedef int (*_pvaSetTermTblFunc_t) (void *gmd_, int is_port, char *pname, int is_bus, int idx, int dir, char *dName);
typedef void (*_pvaGetTermNameFunc_t) (void *,int,char *);
typedef void (*_pvaGetTermOffsetFunc_t) (void *gmd_,char *p, int is_bus1, int idx1, char *n, int is_bus2, int idx2, int *p_idx, int *n_idx);
typedef DiwTbl_t * (*_pvaSetTermOffsetFunc_t) (void *gmd_,int is_term, char *p, int is_bus1, int idx1, char *n, int is_bus2, int idx2, char *bname, int filename, int lineno);
typedef void (*_pvaSetDerivTermOffsetFunc_t) (void *gmd_,int is_term, DiwTbl_t *diw, int derID, char *p, int is_bus1, int idx1, char *n, int is_bus2, int idx2);
typedef void (*_pvaFinishDiwSetupFunc_t) (void *gmd_);
typedef void (*pvaNumInvalidFunc_t) (int thid, int code, char *nname, char *hierName, char *mname, int filename, int lineno);
typedef void (*pvaCheckNanInfFunc_t) (int thid, int i, double *diw, char *nname, char *hierName, char *mname, int filename, int lineno);
typedef int (*epvaAnalogNodeAliasFunc_t) (int xmr_id, double time_, int array_idx, int filename, int lineno);
typedef int (*epvaSetupXMRaliasFunc_t) (char *mname, char *nname, char *hname, void *gmd);
typedef double (*epvaGetXMRresolveStatusFunc_t) (int xmr_id);
typedef double (*epvaGetXMRValueFunc_t) (int xmr_id, double time_, int array_idx, int is_alias, int filename, int lineno);
typedef void (*epvaSetXMRValueFunc_t) (int xmr_id, double time_, int array_idx, double new_valie, int incr_, int filename, int lineno);
typedef int (*pvaPortConnectedFunc_t) (char *hierName, char *portName);
typedef void (*pvaSimpleFatalFunc_t) (char *file, int line);
typedef void (*_pvaSetPortConnectedFunc_t) (void *, unsigned int, int);
typedef int (*_iDXFunc_t) (void *gmd_, int is_term, char *p, int is_bus1, int idx1, char *n, int is_bus2, int idx2, char *bname);
typedef int (*_iDXLevel2Func_t) (void *gmd_, int cid, int is_term, char *p, int is_bus1, int idx1, char *n, int is_bus2, int idx2, char *bname);
typedef void (*_pvaAddIDXIndexFunc_t) (void *ptr, int cid, int currID, int key, char *name, int idx, char *nname, int idx2, int id);
typedef int (*_pvaFindIDXIndexFunc_t) (void *ptr, int cid, int currID, int key, char *name, int idx, char *nname, int idx2);
typedef int (*_pvaGetDerivIDXIndexFunc_t) (int thid, void *ptr, int);
typedef int (*_pvaGetIDXIndexFunc_t) (int thid, void *ptr, int);
typedef void (*_pvaPutDerivIDXIndexFunc_t) (int thid, void *ptr, int position, int);
typedef void (*_pvaPutIDXIndexFunc_t) (int thid, void *ptr, int position, int);
typedef void (*_pvaIncIDXLoopFunc_t) (int thid, void *ptr, int reset);
typedef void (*pvaNotifyAbstolFunc_t) (pINT64_t, double, int);
typedef double * (*_pvaBuildRealArrayFunc_t) (int size, double *addr, ...);
typedef void (*pvaReportPowerFunc_t) (pINT64_t, double);
typedef int * (*pvaDummyIntPFunc_t) (int,int,int);
typedef double * (*pvaDummyRealPFunc_t) (int,double,int);
typedef int (*pvaDummyIntP_GETFunc_t) (int,int);
typedef double (*pvaDummyRealP_GETFunc_t) (int,int);
typedef void (*pvaHashDisStatesFunc_t) (int thid, char *, void *, int, char *);
typedef void (*pvaFreeDisStatesFunc_t) (int thid, char *name, void *, int, char *);
typedef int (*pvaDecrDisUseFunc_t) (char *instName, char *hashkey);
typedef void (*pvaCheckDiwFunc_t) (int thid, void *gmd, double *diw, char *hierName, char *mname, int mode, int is_fpe3);
typedef void (*pvaCheckDiwVFunc_t) (void *gmd, double *diw, char *hierName, char *mname, int mode);
typedef void (*pvaCheckDiwIFunc_t) (void *gmd, double *diw, char *hierName, char *mname, int mode);
typedef void (*pvaCheckDiwQFunc_t) (void *gmd, double *diw, char *hierName, char *mname, int mode);
typedef void (*pvaNullifyFunc_t) (void *gmd, double *diw, int offset);
typedef char * (*pvaR2SFunc_t) (double, char *);
typedef void (*pvaAddVarDescFunc_t) (char *modName, char *name, int nodeType, int offset, int dataType, int isArray, int indBegin, int indEnd, int rangeFixed, int bds, char *unit);
typedef int (*pvaVarProbeSizeFunc_t) (char *modName);
typedef char * (*pvaVarProbeNameFunc_t) (char *modName, int index);
typedef char * (*pvaVarProbeUnitsFunc_t) (char *modName, int index);
typedef int (*pvaVarProbeIndexFunc_t) (char *modName, const char *pName);
typedef int (*pvaHasIProbeFunc_t) (char *modName, int hasSwitch);
typedef void (*pvaExtractValueFunc_t) (char *modName, char *state, char *gmd, double *dest);
typedef int (*pvaIsVarDBCompleteFunc_t) (char *modName, char *inst);
typedef int (*pvaModVarCompleteFunc_t) (char *modName, int nport);
typedef const char * (*pvaEscapeLookupFunc_t) (const char *escKey);
typedef int (*pvaCheckIntegerTypeFunc_t) (char *modName, char *vname);
typedef char (*pvaV2LFunc_t) (double);
typedef int (*pvaL2IntFunc_t) (double);
typedef int (*pvaL2IntAFunc_t) (double *,int,int);
typedef char * (*pvaL2StrFunc_t) (double);
typedef char * (*pvaL2StrAFunc_t) (double *,int,int,int);
typedef int (*pvaBitsCmpFunc_t) (double,char *);
typedef int (*pvaBitsCmpAFunc_t) (double *,int,int,char *);
typedef double (*pvaBitwiseLFunc_t) (double);
typedef void (*pvaBitwiseLAFunc_t) (double *,int,int);
typedef int (*pvaBitShiftLFunc_t) (double *,int,int,int,int);
typedef int (*pvaBitShiftRFunc_t) (double *,int,int,int,int);
typedef int (*pvaConvert2IntFunc_t) (int, char *);
typedef char * (*pvaConstBits2StrFunc_t) (char *, int num, ...);
typedef int (*pvaPosNegEdgeFunc_t) (int thid, void *, int, int, double, double);
typedef pvaLogicType (*pvaV2LogicFunc_t) (char *, char *, double, double, int);
typedef pvaLogicType (*pvaV2LogicAFunc_t) (char *, char *, double, double *,int,int,int,int);
typedef int (*pvaLogic2IntFunc_t) (pvaLogicType);
typedef char * (*pvaLogic2StrFunc_t) (pvaLogicType, int);
typedef pvaLogicType (*pvaInt2LogicFunc_t) (unsigned int);
typedef double (*pvaInt2LogicVFunc_t) (unsigned int);
typedef pvaLogicType (*pvaStr2LogicFunc_t) (char *);
typedef double (*pvaLogic2VFunc_t) (pvaLogicType);
typedef pvaLogicType (*pvaOpLogicNegateFunc_t) (pvaLogicType op);
typedef pvaLogicType (*pvaOpLogicUnaryMinusFunc_t) (pvaLogicType op);
typedef pvaLogicType (*pvaOpLogicAndFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicOrFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicXorFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicNorFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicXnorFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicReductAndFunc_t) (pvaLogicType op);
typedef pvaLogicType (*pvaOpLogicReductOrFunc_t) (pvaLogicType op);
typedef pvaLogicType (*pvaOpLogicReductXorFunc_t) (pvaLogicType op);
typedef pvaLogicType (*pvaOpLogicCmpFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef int (*pvaOpLogicCmpFullFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicAddFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicSubFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicMultFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaOpLogicShiftLFunc_t) (pvaLogicType op, int shift);
typedef pvaLogicType (*pvaOpLogicShiftRFunc_t) (pvaLogicType op, int shift);
typedef int (*pvaLogicCmpXFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef int (*pvaLogicCmpZFunc_t) (pvaLogicType op1, pvaLogicType op2);
typedef pvaLogicType (*pvaLogicTruncFunc_t) (pvaLogicType, int, int);
typedef void (*pvaLogicOneBitAddFunc_t) (int,int,int,int *,int *);
typedef int (*pvaLogicCheckXZFunc_t) (pvaLogicType);
typedef void (*pvaInitFastIndexFunc_t) (int **, int **);
typedef int (*pvaHelpNodeFunc_t) (int);
typedef int (*pvaHelpSelectFunc_t) (int thid, char *, char *, int, int, int, int);
typedef int (*pvaHelpBussFunc_t) (int thid, char *, char *, int, int, int, int);
typedef int (*pvaHelpBuss2Func_t) (int thid, char *, char *, int, int, int, int);
typedef char * (*pvaWorkingModuleFunc_t) ();
typedef void (*pvaLapGmdFunc_t) (void **, void*, void**, char *key_, int, int, double*, double*, int, int, int, double);
typedef int (*pvaParentParamGivenFunc_t) (char *);
typedef void (*pvaUpdateDynamicLapGmdFunc_t) (char *, int, void *, int, int, double *, double *, int, int, double);
typedef void (*pvaGetDCvoltageGMDFunc_t) (void *, void **, double, int, char *);
typedef void * (*pvaLinearResistorFunc_t) (double, void *);
typedef void * (*pvaLinearCapacitorFunc_t) (double, void *);
typedef void (*pvaCreateVSRCFunc_t) (void **, int);
typedef void (*pvaGetPulseFunc_t) (void *, void **, int, double, double, double, int, char *);
typedef void (*pvaCreateVsrcPWLFunc_t) (void **, void *, int, double *);
typedef void * (*pvaGetDisObjsFunc_t) (char *);
typedef void (*pvaPutDisObjsFunc_t) (char *, void *);
typedef void (*pvaSetVaFileLineFunc_t) (char *, int);
typedef int (*pvaEVS2modeFunc_t) (void);
typedef int (*pvaIsFastSimulatorFunc_t) ();
typedef double (*pvaZiTransFunc_t) (int thid, void *dis, int loc, int loop, int type, double time, double input, int lz, double *zeros, int lp, double *poles, double T, double tau, double t0, char *fname, int line);
typedef void (*pvaZiAcceptFunc_t) (int thid, void *obj, double t);
typedef double (*pvaZiTransACFunc_t) (int thid, void *dis, int loc, int loop, int acMode, double freq, int isReal);
typedef double * (*pvaGetTempLoc_Func_t) (double);
typedef void (*pvaEndTimeStep_Func_t) (int thid);
typedef void (*pvaUpdateDC_Func_t) (int *);
typedef int (*pvaCosimSnpsReadDIntByHandleFunc_t) (char *, int, void **handle, double);
typedef int (*pvaCosimSnpsReadDIntArrayByHandleFunc_t) (char *, int, void **handle, int);
typedef int (*pvaCosimSnpsReadDSignalByHandleFunc_t) (char *, int, void **handle);
typedef int (*pvaCosimSnpsReadDSignalArrayByHandleFunc_t) (char *, int, void **handle, int);
typedef double (*pvaCosimSnpsReadDRealByHandleFunc_t) (char *, int, void **handle);
typedef double (*pvaCosimSnpsReadDRealArrayByHandleFunc_t) (char *, int, void **handle, int);
typedef pvaLogicType (*pvaV2LogicByHandleFunc_t) (char *, char *, double, double, int, void **handle);
typedef pvaLogicType (*pvaV2LogicAByHandleFunc_t) (char *, char *, double, double *,int,int,int,int, void **handle);
typedef int (*pvaCosimSnpsReadDIntFunc_t) (char *, int, double);
typedef int (*pvaCosimSnpsReadDIntArrayFunc_t) (char *, int, int);
typedef int (*pvaCosimSnpsReadDSignalFunc_t) (char *, int);
typedef int (*pvaCosimSnpsReadDSignalArrayFunc_t) (char *, int, int);
typedef double (*pvaCosimSnpsReadDRealFunc_t) (char *, int);
typedef double (*pvaCosimSnpsReadDRealArrayFunc_t) (char *, int, int);
typedef int (*pvaCosimSnpsDAccessGetDIntByHandleFunc_t) (char *, char *, void **handle);
typedef double (*pvaCosimSnpsDAccessGetDRealByHandleFunc_t) (char *, char *, void **handle);
typedef int (*pvaCosimSnpsDAccessGetDIntArrayByHandleFunc_t) (char *, char *, void **handle, int *array);
typedef int (*pvaCosimSnpsDAccessGetDRealArrayByHandleFunc_t) (char *, char *, void **handle, double *array);
typedef int (*pvaCosimSnpsAccessGetAIntByHandleFunc_t) (char *, char *, void **handle);
typedef double (*pvaCosimSnpsAccessGetARealByHandleFunc_t) (char *, char *, void **handle);
typedef double (*pvaWhiteNoiseFunc_t) (double power, int dummy);
typedef double (*pvaFlickerNoiseFunc_t) (double freq, double power, double exp, int dummy);
typedef double (*pvaNoiseTableFunc_t) (double freq, int tbSize, double *table, int dummy);
typedef double (*pvaNoiseTableLogFunc_t) (double freq, int tbSize, double *table, int dummy);
typedef void (*pvaMergeNoiseComponentsFunc_t) (double *diw, int *targets, int *sources, int count);
typedef void * (*pvaSysMallocFunc_t) (int size, char * filenamee, char * functionnm, int linen);
typedef void * (*pvaSysCallocFunc_t) (int nelem, int elsize, char * filenamee, char * functionnm, int linen);
typedef void (*pvaSysFreeFunc_t) (void *ptr, char * filenamee, char * functionnm, int linen);
typedef void * (*pvaSysReallocFunc_t) (void *ptr, int size, char * filenamee, char * functionnm, int linen);
typedef char * (*pvaStrdupFunc_t) (char * str);
typedef char * (*pvaStrMcatFunc_t) (char *, ...);
typedef int (*pvaStrcmpFunc_t) (char *,char *);
typedef char * (*pvaStrcatFunc_t) (char *,char *);
typedef char * (*pvaStrcpyFunc_t) (char *,char *);
typedef double (*pvaSimpleTransitionFunc_t) (void *, double *, double, double, double, double, double);
typedef int (*pvaChkPortConnFunc_t) (void *, char *);
typedef void (*pvaSetDefaultHashSizeFunc_t) ();
typedef void (*pvaSetNewHashSizeFunc_t) (int n_size);
typedef char * (*pvaGetAnalysisNameFunc_t) (int thid, char *);
typedef char * (*pvaGetAnalysisTypeFunc_t) (int thid, char *);
typedef int (*pvaIsNanFunc_t) (double);

pvaLRMFOpenFunc_t pvaLRMFOpen;
pvaLRMFCloseFunc_t pvaLRMFClose;
pvaLRMFlushFunc_t pvaLRMFlush;
pvaLRMFeofFunc_t pvaLRMFeof;
pvaLRMFseekFunc_t pvaLRMFseek;
pvaLRMFtellFunc_t pvaLRMFtell;
pvaLRMrewindFunc_t pvaLRMrewind;
pvaLRMFGetsFunc_t pvaLRMFGets;
pvaLRMFScanfFunc_t pvaLRMFScanf;
pvaLRMFErrorFunc_t pvaLRMFError;
pvaLRMFWarningFunc_t pvaLRMFWarning;
pvaLRMFPrintFunc_t pvaLRMFPrint;
pvaLRMFPrintfFunc_t pvaLRMFPrintf;
pvaFStrobeFunc_t pvaFStrobe;
pvaFMonitorFunc_t pvaFMonitor;
pvaFDisplayFunc_t pvaFDisplay;
pvaLRMFWriteFunc_t pvaLRMFWrite;
pvaFDebugFunc_t pvaFDebug;
pvaSprintfFunc_t pvaSprintf;
pvaLRMFatalFunc_t pvaLRMFatal;
pvaLRMErrorFunc_t pvaLRMError;
pvaLRMPrintFunc_t pvaLRMPrint;
pvaLRMPrintfFunc_t pvaLRMPrintf;
pvaLRMWarningFunc_t pvaLRMWarning;
pvaLRMInfoFunc_t pvaLRMInfo;
pvaStrobeFunc_t pvaStrobe;
pvaMonitorFunc_t pvaMonitor;
pvaDisplayFunc_t pvaDisplay;
pvaWriteFunc_t pvaWrite;
pvaLRMDebugFunc_t pvaLRMDebug;
pvaSimpleDebugFunc_t pvaSimpleDebug;
pvaCharCountLocationFunc_t pvaCharCountLocation;
pvaNewPortListFunc_t pvaNewPortList;
pvaUpdateDC__Func_t pvaUpdateDC__;
pvaLRMFinish_Current_AnalysisFunc_t pvaLRMFinish_Current_Analysis;
pvaLRMCompleteFinishFunc_t pvaLRMCompleteFinish;
pvaLRMFinishFunc_t pvaLRMFinish;
pvaLRMStopFunc_t pvaLRMStop;
pvaNonconvergenceFunc_t pvaNonconvergence;
pvaSetRtlFlgFunc_t pvaSetRtlFlg;
pvaRegisterAutoStopFunc_t pvaRegisterAutoStop;
pvaSetInsideInitialFunc_t pvaSetInsideInitial;
pvaSaveAnalogObjsFunc_t pvaSaveAnalogObjs;
pvaRestoreAnalogObjsFunc_t pvaRestoreAnalogObjs;
pvaRandomFunc_t pvaRandom;
pvaDistUniformFunc_t pvaDistUniform;
pvaDistNormalFunc_t pvaDistNormal;
pvaDistExponentialFunc_t pvaDistExponential;
pvaDistPoissonFunc_t pvaDistPoisson;
pvaDistChiSquareFunc_t pvaDistChiSquare;
pvaDistTFunc_t pvaDistT;
pvaDistErlangFunc_t pvaDistErlang;
pvaRandomUpdateSeedsFunc_t pvaRandomUpdateSeeds;
pvaRandomInitFunc_t pvaRandomInit;
pvaRandomInit2SeedsFunc_t pvaRandomInit2Seeds;
pvaRTLclog2Func_t pvaRTLclog2;
pvaLnFunc_t pvaLn;
pvaLogFunc_t pvaLog;
pvaLog10Func_t pvaLog10;
pvaRTLlogFunc_t pvaRTLlog;
pvaRTLlog10Func_t pvaRTLlog10;
pvaRTLlog_derivFunc_t pvaRTLlog_deriv;
pvaRTLlog10_derivFunc_t pvaRTLlog10_deriv;
pvaSimulatorFunc_t pvaSimulator;
pvaCMIwarningFunc_t pvaCMIwarning;
pva_exp_srcFunc_t pva_exp_src;
pva_get_expmaxFunc_t pva_get_expmax;
pvaDivideFunc_t pvaDivide;
pvaDiv_Func_t pvaDiv_;
pvaUseDelta_Func_t pvaUseDelta_;
pvaUseGmin_Func_t pvaUseGmin_;
pvaUseCmin_Func_t pvaUseCmin_;
pvaUseUnity_Func_t pvaUseUnity_;
pvaChkRHSNanInf__Func_t pvaChkRHSNanInf__;
pvaCheckNanInfRHS__Func_t pvaCheckNanInfRHS__;
pvaRealExpFunc_t pvaRealExp;
pvaRTLexpFunc_t pvaRTLexp;
pvaRTLexp1pFunc_t pvaRTLexp1p;
pvaRTLpowerFunc_t pvaRTLpower;
pvaMinFunc_t pvaMin;
pvaMaxFunc_t pvaMax;
pvaAbsFunc_t pvaAbs;
pvaFloorFunc_t pvaFloor;
pvaCeilFunc_t pvaCeil;
pvaTruncFunc_t pvaTrunc;
pvaModFunc_t pvaMod;
pvaPower_Func_t pvaPower_;
pvaPowerIntFunc_t pvaPowerInt;
pvaPowerInt2Func_t pvaPowerInt2;
pvaIntPowerFunc_t pvaIntPower;
pvaAsinFunc_t pvaAsin;
pvaAsin1pFunc_t pvaAsin1p;
pvaAcosFunc_t pvaAcos;
pvaAcos1pFunc_t pvaAcos1p;
pvaAcoshFunc_t pvaAcosh;
pvaAtanhFunc_t pvaAtanh;
pvaScaled__Func_t pvaScaled__;
pvaRealEQFunc_t pvaRealEQ;
pvaRealLEFunc_t pvaRealLE;
pvaRealLTFunc_t pvaRealLT;
pvaRealGTFunc_t pvaRealGT;
pvaRealGEFunc_t pvaRealGE;
pvaRealNEFunc_t pvaRealNE;
pvaIntShiftLFunc_t pvaIntShiftL;
pvaIntShiftRFunc_t pvaIntShiftR;
pvaTimeStepFunc_t pvaTimeStep;
pvaTimeStepTypeFunc_t pvaTimeStepType;
pvaAcFinalStepFunc_t pvaAcFinalStep;
pvaCpuTimeFunc_t pvaCpuTime;
pvaRegisterEvalFunc_t pvaRegisterEval;
pvaAcceptTimePointFunc_t pvaAcceptTimePoint;
pvaPreIterationFunc_t pvaPreIteration;
pvaPreIteration2Func_t pvaPreIteration2;
pvaEndIterationFunc_t pvaEndIteration;
pvaIsSkipEvalNotifySimModeFunc_t pvaIsSkipEvalNotifySimMode;
pvaInitStepFunc_t pvaInitStep;
pvaFinalStepFunc_t pvaFinalStep;
pvaFinalStepSimpleFunc_t pvaFinalStepSimple;
pvaGetFinalTimeFunc_t pvaGetFinalTime;
pvaAnalysisFunc_t pvaAnalysis;
pvaSimparamFunc_t pvaSimparam;
pvaSimCopyDisFunc_t pvaSimCopyDis;
pvaSimSaveFunc_t pvaSimSave;
pvaSimRestoreFunc_t pvaSimRestore;
pvaSimSetValueFunc_t pvaSimSetValue;
pvaGetSimParamsFunc_t pvaGetSimParams;
pvaSupportNullPortFunc_t pvaSupportNullPort;
pvaProcessSimulatorOptsFunc_t pvaProcessSimulatorOpts;
pvaProcessSimulatorEpva2pvaFunc_t pvaProcessSimulatorEpva2pva;
pvaWriteChkPtLineFunc_t pvaWriteChkPtLine;
pvaAbsDeltaFunc_t pvaAbsDelta;
pvaTransitionFunc_t pvaTransition;
pvaCrossMFunc_t pvaCrossM;
pvaCrossFunc_t pvaCross;
pvaLastCrossingFunc_t pvaLastCrossing;
pvaAboveFunc_t pvaAbove;
pvaDelayFunc_t pvaDelay;
pvaSlewFunc_t pvaSlew;
pvaTimerFunc_t pvaTimer;
pvaIdtFunc_t pvaIdt;
pvaIdt_order2Func_t pvaIdt_order2;
pvaIdtmodFunc_t pvaIdtmod;
pvaIdtDxFunc_t pvaIdtDx;
pvaDdtFunc_t pvaDdt;
pvaDdtDxFunc_t pvaDdtDx;
pvaLimexpFunc_t pvaLimexp;
pvaLimexpSimpleFunc_t pvaLimexpSimple;
pvaLimexpDiffFunc_t pvaLimexpDiff;
pvaLimitFunc_t pvaLimit;
pvaLimitStrFunc_t pvaLimitStr;
pvaPnjlimFunc_t pvaPnjlim;
pvaFetlimFunc_t pvaFetlim;
pvaTableModelEvalFunc_t pvaTableModelEval;
pvaTableModelEvalPFunc_t pvaTableModelEvalP;
pvaFreeRuntimeMemoryFunc_t pvaFreeRuntimeMemory;
pvaAssignRealMeFunc_t pvaAssignRealMe;
pvaAssignRealFunc_t pvaAssignReal;
pvaAssignIntegerFunc_t pvaAssignInteger;
pvaArrayEqualFunc_t pvaArrayEqual;
_pva2Ac__Func_t _pva2Ac__;
_pvaFtoTFunc_t _pvaFtoT;
pvaIsForHighZsetFunc_t pvaIsForHighZset;
pvaGetThreadIdFunc_t pvaGetThreadId;
pvaSimProbeFunc_t pvaSimProbe;
pvaProbeOffsetFunc_t pvaProbeOffset;
pvaSimProbeINHVAFunc_t pvaSimProbeINHVA;
pvaDiscontinuityFunc_t pvaDiscontinuity;
pvaBoundStep2Func_t pvaBoundStep2;
pvaBoundStepFunc_t pvaBoundStep;
pvaGetNextTimeFunc_t pvaGetNextTime;
pvaWarningFunc_t pvaWarning;
pvaNIYFunc_t pvaNIY;
pvaCheckFilePathFunc_t pvaCheckFilePath;
pvaInfoStrFuncFunc_t pvaInfoStrFunc;
_pvaItoAFunc_t _pvaItoA;
_pvaFtoAFunc_t _pvaFtoA;
pvaStrToupperFunc_t pvaStrToupper;
pvaStrTolowerFunc_t pvaStrTolower;
pvaSubstrFunc_t pvaSubstr;
pvaConcatFunc_t pvaConcat;
pvaSformatFunc_t pvaSformat;
pvaValueToStringFunc_t pvaValueToString;
pvaBits2StrFunc_t pvaBits2Str;
pvaReal2BitsFunc_t pvaReal2Bits;
pvaBits2RealFunc_t pvaBits2Real;
pvaGetHierInstNameFunc_t pvaGetHierInstName;
pvaRevHierInstNameFunc_t pvaRevHierInstName;
pvaSetFlagBuildInstFuncFunc_t pvaSetFlagBuildInstFunc;
pvaUpdateParameterFunc_t pvaUpdateParameter;
pvaInitialOneTimeFunc_t pvaInitialOneTime;
pvaErrorFunc_t pvaError;
pvaInforFunc_t pvaInfor;
pvaInforMeFunc_t pvaInforMe;
pvaErrGenCExitFunc_t pvaErrGenCExit;
pvaErrGenCCountFunc_t pvaErrGenCCount;
pvaPutStrTblFunc_t pvaPutStrTbl;
pvaGetStrTblFunc_t pvaGetStrTbl;
pvaRTLmemoryFunc_t pvaRTLmemory;
_pvaSetInitValueFunc_t _pvaSetInitValue;
_pvaSetTermTblFunc_t _pvaSetTermTbl;
_pvaGetTermNameFunc_t _pvaGetTermName;
_pvaGetTermOffsetFunc_t _pvaGetTermOffset;
_pvaSetTermOffsetFunc_t _pvaSetTermOffset;
_pvaSetDerivTermOffsetFunc_t _pvaSetDerivTermOffset;
_pvaFinishDiwSetupFunc_t _pvaFinishDiwSetup;
pvaNumInvalidFunc_t pvaNumInvalid;
pvaCheckNanInfFunc_t pvaCheckNanInf;
epvaAnalogNodeAliasFunc_t epvaAnalogNodeAlias;
epvaSetupXMRaliasFunc_t epvaSetupXMRalias;
epvaGetXMRresolveStatusFunc_t epvaGetXMRresolveStatus;
epvaGetXMRValueFunc_t epvaGetXMRValue;
epvaSetXMRValueFunc_t epvaSetXMRValue;
pvaPortConnectedFunc_t pvaPortConnected;
pvaSimpleFatalFunc_t pvaSimpleFatal;
_pvaSetPortConnectedFunc_t _pvaSetPortConnected;
_iDXFunc_t _iDX;
_iDXLevel2Func_t _iDXLevel2;
_pvaAddIDXIndexFunc_t _pvaAddIDXIndex;
_pvaFindIDXIndexFunc_t _pvaFindIDXIndex;
_pvaGetDerivIDXIndexFunc_t _pvaGetDerivIDXIndex;
_pvaGetIDXIndexFunc_t _pvaGetIDXIndex;
_pvaPutDerivIDXIndexFunc_t _pvaPutDerivIDXIndex;
_pvaPutIDXIndexFunc_t _pvaPutIDXIndex;
_pvaIncIDXLoopFunc_t _pvaIncIDXLoop;
pvaNotifyAbstolFunc_t pvaNotifyAbstol;
_pvaBuildRealArrayFunc_t _pvaBuildRealArray;
pvaReportPowerFunc_t pvaReportPower;
pvaDummyIntPFunc_t pvaDummyIntP;
pvaDummyRealPFunc_t pvaDummyRealP;
pvaDummyIntP_GETFunc_t pvaDummyIntP_GET;
pvaDummyRealP_GETFunc_t pvaDummyRealP_GET;
pvaHashDisStatesFunc_t pvaHashDisStates;
pvaFreeDisStatesFunc_t pvaFreeDisStates;
pvaDecrDisUseFunc_t pvaDecrDisUse;
pvaCheckDiwFunc_t pvaCheckDiw;
pvaCheckDiwVFunc_t pvaCheckDiwV;
pvaCheckDiwIFunc_t pvaCheckDiwI;
pvaCheckDiwQFunc_t pvaCheckDiwQ;
pvaNullifyFunc_t pvaNullify;
pvaR2SFunc_t pvaR2S;
pvaAddVarDescFunc_t pvaAddVarDesc;
pvaVarProbeSizeFunc_t pvaVarProbeSize;
pvaVarProbeNameFunc_t pvaVarProbeName;
pvaVarProbeUnitsFunc_t pvaVarProbeUnits;
pvaVarProbeIndexFunc_t pvaVarProbeIndex;
pvaHasIProbeFunc_t pvaHasIProbe;
pvaExtractValueFunc_t pvaExtractValue;
pvaIsVarDBCompleteFunc_t pvaIsVarDBComplete;
pvaModVarCompleteFunc_t pvaModVarComplete;
pvaEscapeLookupFunc_t pvaEscapeLookup;
pvaCheckIntegerTypeFunc_t pvaCheckIntegerType;
pvaV2LFunc_t pvaV2L;
pvaL2IntFunc_t pvaL2Int;
pvaL2IntAFunc_t pvaL2IntA;
pvaL2StrFunc_t pvaL2Str;
pvaL2StrAFunc_t pvaL2StrA;
pvaBitsCmpFunc_t pvaBitsCmp;
pvaBitsCmpAFunc_t pvaBitsCmpA;
pvaBitwiseLFunc_t pvaBitwiseL;
pvaBitwiseLAFunc_t pvaBitwiseLA;
pvaBitShiftLFunc_t pvaBitShiftL;
pvaBitShiftRFunc_t pvaBitShiftR;
pvaConvert2IntFunc_t pvaConvert2Int;
pvaConstBits2StrFunc_t pvaConstBits2Str;
pvaPosNegEdgeFunc_t pvaPosNegEdge;
pvaV2LogicFunc_t pvaV2Logic;
pvaV2LogicAFunc_t pvaV2LogicA;
pvaLogic2IntFunc_t pvaLogic2Int;
pvaLogic2StrFunc_t pvaLogic2Str;
pvaInt2LogicFunc_t pvaInt2Logic;
pvaInt2LogicVFunc_t pvaInt2LogicV;
pvaStr2LogicFunc_t pvaStr2Logic;
pvaLogic2VFunc_t pvaLogic2V;
pvaOpLogicNegateFunc_t pvaOpLogicNegate;
pvaOpLogicUnaryMinusFunc_t pvaOpLogicUnaryMinus;
pvaOpLogicAndFunc_t pvaOpLogicAnd;
pvaOpLogicOrFunc_t pvaOpLogicOr;
pvaOpLogicXorFunc_t pvaOpLogicXor;
pvaOpLogicNorFunc_t pvaOpLogicNor;
pvaOpLogicXnorFunc_t pvaOpLogicXnor;
pvaOpLogicReductAndFunc_t pvaOpLogicReductAnd;
pvaOpLogicReductOrFunc_t pvaOpLogicReductOr;
pvaOpLogicReductXorFunc_t pvaOpLogicReductXor;
pvaOpLogicCmpFunc_t pvaOpLogicCmp;
pvaOpLogicCmpFullFunc_t pvaOpLogicCmpFull;
pvaOpLogicAddFunc_t pvaOpLogicAdd;
pvaOpLogicSubFunc_t pvaOpLogicSub;
pvaOpLogicMultFunc_t pvaOpLogicMult;
pvaOpLogicShiftLFunc_t pvaOpLogicShiftL;
pvaOpLogicShiftRFunc_t pvaOpLogicShiftR;
pvaLogicCmpXFunc_t pvaLogicCmpX;
pvaLogicCmpZFunc_t pvaLogicCmpZ;
pvaLogicTruncFunc_t pvaLogicTrunc;
pvaLogicOneBitAddFunc_t pvaLogicOneBitAdd;
pvaLogicCheckXZFunc_t pvaLogicCheckXZ;
pvaInitFastIndexFunc_t pvaInitFastIndex;
pvaHelpNodeFunc_t pvaHelpNode;
pvaHelpSelectFunc_t pvaHelpSelect;
pvaHelpBussFunc_t pvaHelpBuss;
pvaHelpBuss2Func_t pvaHelpBuss2;
pvaWorkingModuleFunc_t pvaWorkingModule;
pvaLapGmdFunc_t pvaLapGmd;
pvaParentParamGivenFunc_t pvaParentParamGiven;
pvaUpdateDynamicLapGmdFunc_t pvaUpdateDynamicLapGmd;
pvaGetDCvoltageGMDFunc_t pvaGetDCvoltageGMD;
pvaLinearResistorFunc_t pvaLinearResistor;
pvaLinearCapacitorFunc_t pvaLinearCapacitor;
pvaCreateVSRCFunc_t pvaCreateVSRC;
pvaGetPulseFunc_t pvaGetPulse;
pvaCreateVsrcPWLFunc_t pvaCreateVsrcPWL;
pvaGetDisObjsFunc_t pvaGetDisObjs;
pvaPutDisObjsFunc_t pvaPutDisObjs;
pvaSetVaFileLineFunc_t pvaSetVaFileLine;
pvaEVS2modeFunc_t pvaEVS2mode;
pvaIsFastSimulatorFunc_t pvaIsFastSimulator;
pvaZiTransFunc_t pvaZiTrans;
pvaZiAcceptFunc_t pvaZiAccept;
pvaZiTransACFunc_t pvaZiTransAC;
pvaGetTempLoc_Func_t pvaGetTempLoc_;
pvaEndTimeStep_Func_t pvaEndTimeStep_;
pvaUpdateDC_Func_t pvaUpdateDC_;
pvaCosimSnpsReadDIntByHandleFunc_t pvaCosimSnpsReadDIntByHandle;
pvaCosimSnpsReadDIntArrayByHandleFunc_t pvaCosimSnpsReadDIntArrayByHandle;
pvaCosimSnpsReadDSignalByHandleFunc_t pvaCosimSnpsReadDSignalByHandle;
pvaCosimSnpsReadDSignalArrayByHandleFunc_t pvaCosimSnpsReadDSignalArrayByHandle;
pvaCosimSnpsReadDRealByHandleFunc_t pvaCosimSnpsReadDRealByHandle;
pvaCosimSnpsReadDRealArrayByHandleFunc_t pvaCosimSnpsReadDRealArrayByHandle;
pvaV2LogicByHandleFunc_t pvaV2LogicByHandle;
pvaV2LogicAByHandleFunc_t pvaV2LogicAByHandle;
pvaCosimSnpsReadDIntFunc_t pvaCosimSnpsReadDInt;
pvaCosimSnpsReadDIntArrayFunc_t pvaCosimSnpsReadDIntArray;
pvaCosimSnpsReadDSignalFunc_t pvaCosimSnpsReadDSignal;
pvaCosimSnpsReadDSignalArrayFunc_t pvaCosimSnpsReadDSignalArray;
pvaCosimSnpsReadDRealFunc_t pvaCosimSnpsReadDReal;
pvaCosimSnpsReadDRealArrayFunc_t pvaCosimSnpsReadDRealArray;
pvaCosimSnpsDAccessGetDIntByHandleFunc_t pvaCosimSnpsDAccessGetDIntByHandle;
pvaCosimSnpsDAccessGetDRealByHandleFunc_t pvaCosimSnpsDAccessGetDRealByHandle;
pvaCosimSnpsDAccessGetDIntArrayByHandleFunc_t pvaCosimSnpsDAccessGetDIntArrayByHandle;
pvaCosimSnpsDAccessGetDRealArrayByHandleFunc_t pvaCosimSnpsDAccessGetDRealArrayByHandle;
pvaCosimSnpsAccessGetAIntByHandleFunc_t pvaCosimSnpsAccessGetAIntByHandle;
pvaCosimSnpsAccessGetARealByHandleFunc_t pvaCosimSnpsAccessGetARealByHandle;
pvaWhiteNoiseFunc_t pvaWhiteNoise;
pvaFlickerNoiseFunc_t pvaFlickerNoise;
pvaNoiseTableFunc_t pvaNoiseTable;
pvaNoiseTableLogFunc_t pvaNoiseTableLog;
pvaMergeNoiseComponentsFunc_t pvaMergeNoiseComponents;
pvaSysMallocFunc_t pvaSysMalloc;
pvaSysCallocFunc_t pvaSysCalloc;
pvaSysFreeFunc_t pvaSysFree;
pvaSysReallocFunc_t pvaSysRealloc;
pvaStrdupFunc_t pvaStrdup;
pvaStrMcatFunc_t pvaStrMcat;
pvaStrcmpFunc_t pvaStrcmp;
pvaStrcatFunc_t pvaStrcat;
pvaStrcpyFunc_t pvaStrcpy;
pvaSimpleTransitionFunc_t pvaSimpleTransition;
pvaChkPortConnFunc_t pvaChkPortConn;
pvaSetDefaultHashSizeFunc_t pvaSetDefaultHashSize;
pvaSetNewHashSizeFunc_t pvaSetNewHashSize;
pvaGetAnalysisNameFunc_t pvaGetAnalysisName;
pvaGetAnalysisTypeFunc_t pvaGetAnalysisType;
pvaIsNanFunc_t pvaIsNan;
#endif
