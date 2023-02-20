/*
 * hooke-jeeves.c
 *
 *  Created on: Dec 13, 2016
 *      Author: konrad
 */

#include "includes/hooke-jeeves.h"

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "includes/dbg.h"
extern double calculation(struct variable *vekX, int nVar);

/*
 Function : allocMem(FILE *fp)
 Input    : FILE *fp(Handle to file)
 Output   : number of variables (on success)
 Procedure: Reads number of lines with parameters
 */
int allocMem(FILE *fp, char *initialFileName) {
  int result = 0;
  /* text buffer */
  char text[256];
  /* number of lines in file */
  unsigned int lines = 0;
  /* full path to file with default variable parameters */
  /* check if file exist */
  if ((fp = fopen(initialFileName, "r")) == NULL) return -1;
  /* read number of lines */
  do {
    result = fscanf(fp, "%[^\n]\n", text);
    lines++;
  } while (result != EOF);

  lines--;
  /* save number of lines as number of variables */
  // var = lines;
  /* close file */
  fclose(fp);
  return lines;
}

/*
 Function : loadParams(FILE *fp, struct variable *vekX, unsigned int lines)
 Input    : FILE *fp(Handle to file), struct variable *vekX(Variables),
 Output   : 0 (on success)
 Procedure: Reads initial parameters from file to variable vekX
 */
int loadParams(FILE *fp, struct variable *vekX, unsigned int lines,
               char *initialFileName) {
  unsigned int nr = 0;
  int scanfResult = 0;
  double value1 = 0, value2 = 0, value3 = 0, value4 = 0;

  if ((fp = fopen(initialFileName, "r")) == NULL) return -1;

  do {
    scanfResult =
        fscanf(fp, "%lf %lf %lf %lf\n", &value1, &value2, &value3, &value4);
    // value4=0.000001;
    vekX[nr + 1].min = (double)value2;
    vekX[nr + 1].max = (double)value3;
    vekX[nr + 1].step = (double)value4;
    vekX[nr + 1].value = (double)value1;

    debug("min:%f value:%f max:%f step:%f", vekX[nr + 1].min,
          vekX[nr + 1].value, vekX[nr + 1].max, vekX[nr + 1].step);
    nr++;
  } while (nr < lines && scanfResult != EOF);
  fclose(fp);
  return 0;
}

#ifdef CACHE
int cacheLines = 0;

int checkCache(struct variable *vekX, double *value, int nVar) {
  int i;
  int a;
  int cacheHit = 0;
  if (cacheLines) {
    if (cacheLines < maxCache)
      a = cacheLines - 1;
    else
      a = maxCache - 1;
    if (cacheLines >= 0) do {
        cacheHit = 1;
        for (i = 1; i <= nVar; i++) {
          // printf("%f %f\n",vekX[i].value,cacheData[a].values[i]);
          if (vekX[i].value != cacheData[a].values[i]) {
            cacheHit = 0;
            break;
          }
        }

        if (cacheHit == 1) {
          *value = cacheData[a].result;
          log_info("Cache Hit!");
          break;
        }
        a--;
      } while (a >= 0);
    // printf("Return %d", cacheHit);
  }
  return cacheHit;
}

int addToCache(struct variable *vekX, double *value, int nVar) {
  int i;
  int a = 0;
  log_info("Cache write!");
  // if (cacheLines!=0)
  a = cacheLines % maxCache;
  cacheData[a].values = (double *)malloc(sizeof(double) * (nVar + 1));
  for (i = 1; i <= nVar; i++) {
    cacheData[a].values[i] = vekX[i].value;
  }
  cacheData[a].result = *value;
  cacheLines++;
  return 0;
}
#endif
/*
 Function : int FF(struct variable *vekX, double *value, int thr_num)
 Input    : struct variable *vekX(Variables), double *value(Value of goal
 function), int thr_num (Thread id which runs the function) Output   : 0 (on
 success) Procedure: Runs a HSPICE simulation and read a value of goal function
 */

int FF(struct variable *vekX, double *value, int thr_num,
       char *variableFileName, char *projectFileName, char *goalFileName,
       int nVar) {
  // float *X;

  double f = 0;

  /*X = (float*) malloc(nVar * sizeof(float));
     for (int i = 0; i < nVar; i++)
     X[i] = vekX[i].value; */
#ifdef CACHE
  // int cacheHit = 0;
//      cacheHit = checkCache(vekX, value, nVar);
#endif

#ifdef CACHE
  // if (cacheHit == 0) {
  f = calculation(vekX, nVar);
  //}

  *value = f;
  if (f == 0) printf("error goal function\n");
  //      addToCache(vekX, value, nVar);
  debug("Minimum:%f", *value);
#else

  k = 0;

  debug("Minimum:%f", f);

  /* save value of goal function */
  *value = f;
#endif
  return 0;
}

extern int XX;
extern double P1[200 * 200 * 200];
extern float ideal[819200];
/*---------------------------------------------------------------------------
 Hooke-Jeeves optimization algorithm
 Minimization of the objective function F(X) for many variables X[i] i=1,2,..,N
 vekX   - pointer to variables structure
 eps - accuracy
 tau - initial step
 maxit- total iteration value
 FF   - pointer to goal function procedure
 ---------------------------------------------------------------------------*/
int minFunHJ(struct variable *vekX, double eps, double tau, int maxit,
             double *minF,
             int (*FF)(struct variable *vekX, double *value, int thr_num,
                       char *variableFileName, char *projectFileName,
                       char *goalFileName, int nVar),
             int nVar, char *initialFileName, char *projectFileName,
             char *goalFileName, char *variableFileName) {
  double F2, F1, F0, ni, tau1;
  int k, m;
  // int nVar = var; /* number of variables */
  int ii;
  /* temporary variables */
  struct variable *x0;
  struct variable *x1;
  struct variable *vekXTmp;
  double *hjNI;
  double *hjTAU;
  /* best solution of goal function */
  double bestsol = 0;
  int Czy;
  double vFun = 0;
  int err = 0;
  *minF = 0;

  x0 = (struct variable *)malloc((nVar + 1) * sizeof(struct variable));
  x1 = (struct variable *)malloc((nVar + 1) * sizeof(struct variable));
  hjNI = (double *)malloc((nVar + 1) * sizeof(struct variable));
  hjTAU = (double *)malloc((nVar + 1) * sizeof(struct variable));
  vekXTmp = (struct variable *)malloc((nVar + 1) * sizeof(struct variable));
  for (ii = 1; ii <= nVar; ii++) x0[ii].value = vekX[ii].value;
  for (ii = 1; ii <= nVar; ii++) hjNI[ii] = vekX[ii].step;
  err =
      FF(vekX, &vFun, 0, variableFileName, projectFileName, goalFileName, nVar);
  debug("Initial minimum: %f", vFun);
  F2 = (double)vFun;
  bestsol = F2;
  F0 = F2;
  F1 = F2;
  Czy = 0;
  m = 0;
  ni = (double)tau;

  if (err != 0) return -1;

  m = 0;
  fflush(stdout);
  for (k = 1; k <= nVar; k++) {
    vekXTmp[k].value = vekX[k].value;
  }
  do {
    if (err != 0) break;
    log_info("Iteration: %d/%d", m + 1, maxit);
    m++;
    tau1 = ni;
    for (k = 1; k <= nVar; k++) hjTAU[k] = hjNI[k];
    for (ii = 1; ii <= nVar; ii++) x1[ii].value = vekX[ii].value;

    for (k = 1; k <= nVar; k++) {
      if (err != 0) break;
      for (ii = 1; ii <= nVar; ii++) x1[ii].value = vekX[ii].value;

      if ((vekX[k].value + hjNI[k]) >= vekX[k].min &&
          (vekX[k].value + hjNI[k]) <= vekX[k].max)
        x1[k].value = vekX[k].value + hjNI[k];
      if ((err = FF(x1, &vFun, 0, variableFileName, projectFileName,
                    goalFileName, nVar)) < 0)
        break;
      F1 = (double)vFun;
      if (F1 < F2) {
        vekX[k].value = x1[k].value;
        if (F1 < bestsol) {
          vekXTmp[k].value = vekX[k].value;
          bestsol = F1;
        }
        F2 = F1;
      } else {
        for (ii = 1; ii <= nVar; ii++) x1[ii].value = vekX[ii].value;
        if ((vekX[k].value - hjNI[k]) >= vekX[k].min &&
            (vekX[k].value - hjNI[k]) <= vekX[k].max)
          x1[k].value = vekX[k].value - hjNI[k];
        if ((err = FF(x1, &vFun, 0, variableFileName, projectFileName,
                      goalFileName, nVar)) < 0)
          break;
        F1 = (double)vFun;
        if (F1 < F2) {
          vekX[k].value = x1[k].value;
          if (F1 < bestsol) {
            vekXTmp[k].value = vekX[k].value;
            bestsol = F1;
          }
          F2 = F1;
        };
      }
    }  // k
    if (err != 0) break;
    if (F2 < F0) {
      bestsol = F2;
      for (k = 1; k <= nVar; k++) {
        x1[k].value = x0[k].value;
        x0[k].value = vekX[k].value;
        vekXTmp[k].value = vekX[k].value;
        if ((x0[k].value + (4.0) * (vekX[k].value - x1[k].value)) >=
                vekX[k].min &&
            (x0[k].value + (4.0) * (vekX[k].value - x1[k].value)) <=
                vekX[k].max)
          vekX[k].value =
              (double)(x0[k].value + (4.0) * (vekX[k].value - x1[k].value));
      }
      F0 = F2;
      if ((err = FF(vekX, &vFun, 0, variableFileName, projectFileName,
                    goalFileName, nVar)) < 0)
        break;
      F2 = (double)vFun;
      /*ni*=1.2;  */
      Czy = 1;
      for (k = 1; k <= nVar; k++)
        if ((vekX[k].step) <= (hjNI[k] * (2.0))) hjNI[k] *= (2.0);
    } else {
      if (Czy == 1) {
        for (ii = 1; ii <= nVar; ii++) vekX[ii].value = x0[ii].value;
        F2 = F0;
        Czy = 0;
      } else { /*if (tau1>eps)  */

        for (k = 1; k <= nVar; k++)
          if (hjTAU[k] > eps) {
            if ((vekX[k].step) <= (hjNI[k] * 0.5))
              hjNI[k] *= 0.5;
            else
              hjNI[k] = vekX[k].step;
            /*                              ni*=0.2; */
          }
      }
    }

    for (k = 1; k <= nVar; k++) {
      debug("Variable%d %.15lf\n", k, vekXTmp[k].value);
    }
    debug("Goal function value: %.15lf\n", bestsol);

    if (F0 < bestsol) {
      bestsol = F0;
      for (k = 1; k <= nVar; k++) {
        vekXTmp[k].value = vekX[k].value;
      }
    }

    if (F2 < bestsol) {
      bestsol = F2;
      for (k = 1; k <= nVar; k++) {
        vekXTmp[k].value = vekX[k].value;
      }
    }
    debug("Current minimum: %.12lf\n", bestsol);
    fflush(stdout);
  } while (!(tau1 <= eps || m > (maxit - 1) || err));

  FF(vekXTmp, &vFun, 0, variableFileName, projectFileName, goalFileName, nVar);
  *minF = (double)vFun;
  for (int i = 0; i < XX; i++) printf("%lf %lf\n", P1[i], ideal[i]);
  printf("Goal function value:%.15f\n", *minF);
  printf("Variables:\n");
  for (int i = 0; i < nVar; i++) printf("%.15lf\n", vekXTmp[i + 1].value);
  if (x0) free(x0);
  if (x1) free(x1);
  if (hjNI) free(hjNI);
  if (hjTAU) free(hjTAU);
  if (vekXTmp) free(vekXTmp);
  if (m > maxit)
    return 1;
  else
    return err;
} /*minFunHJ */

#define false 0
#define true 1
int minFunHJReal(struct variable *vekX, double eps, double tau, int maxit,
                 double *minF,
                 int (*FF)(struct variable *vekX, double *value, int thr_num,
                           char *variableFileName, char *projectFileName,
                           char *goalFileName, int nVar),
                 int nVar, char *initialFileName, char *projectFileName,
                 char *goalFileName, char *variableFileName) {
  double F2, F1, F0, ni, tau1;
  int k, m;
  const int N = nVar;
  *minF = 0;
  struct variable *X0;
  struct variable *X1;
  // double *X0 ;
  // double *X1 ;
  // X0 = (double*)malloc((N+1) * sizeof(double));
  //      X1 = (double*)malloc((N+1) * sizeof(double));
  X0 = (struct variable *)malloc((nVar + 1) * sizeof(struct variable));
  X1 = (struct variable *)malloc((nVar + 1) * sizeof(struct variable));
  unsigned char Czy;
  for (int ii = 1; ii <= N; ii++) X0[ii].value = vekX[ii].value;

  // F2=FF(Rown, WekX);
  FF(vekX, &F2, 0, variableFileName, projectFileName, goalFileName, nVar);
  F0 = F2;
  Czy = false;
  m = 0;
  ni = tau;
  do {
    m++;
    tau1 = ni;
    for (k = 1; k <= N; k++) {
      for (int ii = 1; ii <= N; ii++) X1[ii].value = vekX[ii].value;
      X1[k].value = vekX[k].value + ni;
      FF(X1, &F1, 0, variableFileName, projectFileName, goalFileName, nVar);
      if (F1 < F2) {
        vekX[k].value = X1[k].value;
        F2 = F1;
      } else {
        for (int ii = 1; ii <= N; ii++) X1[ii].value = vekX[ii].value;
        X1[k].value = vekX[k].value - ni;
        //      F1=FF(Rown, X1) ;
        FF(X1, &F1, 0, variableFileName, projectFileName, goalFileName, nVar);
        if (F1 < F2) {
          vekX[k].value = X1[k].value;
          F2 = F1;
        };
      }
    }  // k
    if (F2 < F0) {
      for (k = 1; k <= N; k++) {
        X1[k].value = X0[k].value;
        X0[k].value = vekX[k].value;
        vekX[k].value = X0[k].value + 1.4 * (vekX[k].value - X1[k].value);
      }
      F0 = F2;
      FF(vekX, &F2, 0, variableFileName, projectFileName, goalFileName, nVar);
      // F2=FF(Rown, vekX);
      ni *= 1.2;
      Czy = true;
    } else {
      if (Czy) {
        for (int ii = 1; ii <= N; ii++) vekX[ii].value = X0[ii].value;
        F2 = F0;
        Czy = false;
      } else {
        if (tau1 > eps) ni *= 0.2;
      }
    }
  } while (!(tau1 <= eps || m > maxit));
  FF(vekX, minF, 0, variableFileName, projectFileName, goalFileName, nVar);
  printf("real\n");
  for (int i = 0; i < XX; i++) printf("%lf %lf\n", P1[i], ideal[i]);
  printf("Goal function value:%.15f\n", *minF);
  printf("Variables:\n");
  for (int i = 0; i < nVar; i++) printf("%.15lf\n", vekX[i + 1].value);
  //*minF=FF(Rown, vekX);
  if (m > maxit)
    return 1;
  else
    return 0;
} /*minFunHJ */

int minFunHJRealMinMax(struct variable *vekX, double eps, double tau, int maxit,
                       double *minF,
                       int (*FF)(struct variable *vekX, double *value,
                                 int thr_num, char *variableFileName,
                                 char *projectFileName, char *goalFileName,
                                 int nVar),
                       int nVar, char *initialFileName, char *projectFileName,
                       char *goalFileName, char *variableFileName) {
  double F2, F1, F0, ni, tau1;
  int k, m;
  const int N = nVar;
  *minF = 0;
  struct variable *X0;
  struct variable *X1;
  // double *X0 ;
  // double *X1 ;
  // X0 = (double*)malloc((N+1) * sizeof(double));
  //      X1 = (double*)malloc((N+1) * sizeof(double));
  X0 = (struct variable *)malloc((nVar + 1) * sizeof(struct variable));
  X1 = (struct variable *)malloc((nVar + 1) * sizeof(struct variable));
  unsigned char Czy;
  for (int ii = 1; ii <= N; ii++) X0[ii].value = vekX[ii].value;

  // F2=FF(Rown, WekX);
  FF(vekX, &F2, 0, variableFileName, projectFileName, goalFileName, nVar);
  F0 = F2;
  Czy = false;
  m = 0;
  ni = tau;
  do {
    m++;
    tau1 = ni;
    for (k = 1; k <= N; k++) {
      for (int ii = 1; ii <= N; ii++) X1[ii].value = vekX[ii].value;
      if ((vekX[k].value + ni) >= vekX[k].min &&
          (vekX[k].value + ni) <= vekX[k].max)
        X1[k].value = vekX[k].value + ni;
      FF(X1, &F1, 0, variableFileName, projectFileName, goalFileName, nVar);
      if (F1 < F2) {
        vekX[k].value = X1[k].value;
        F2 = F1;
      } else {
        for (int ii = 1; ii <= N; ii++) X1[ii].value = vekX[ii].value;
        if ((vekX[k].value - ni) >= vekX[k].min &&
            (vekX[k].value - ni) <= vekX[k].max)
          X1[k].value = vekX[k].value - ni;
        //      F1=FF(Rown, X1) ;
        FF(X1, &F1, 0, variableFileName, projectFileName, goalFileName, nVar);
        if (F1 < F2) {
          vekX[k].value = X1[k].value;
          F2 = F1;
        };
      }
    }  // k
    if (F2 < F0) {
      for (k = 1; k <= N; k++) {
        X1[k].value = X0[k].value;
        X0[k].value = vekX[k].value;
        if ((X0[k].value + 1.4 * (vekX[k].value - X1[k].value)) >=
                vekX[k].min &&
            (X0[k].value + 1.4 * (vekX[k].value - X1[k].value)) <= vekX[k].max)
          vekX[k].value = X0[k].value + 1.4 * (vekX[k].value - X1[k].value);
      }
      F0 = F2;
      FF(vekX, &F2, 0, variableFileName, projectFileName, goalFileName, nVar);
      // F2=FF(Rown, vekX);
      ni *= 1.2;
      Czy = true;
    } else {
      if (Czy) {
        for (int ii = 1; ii <= N; ii++) vekX[ii].value = X0[ii].value;
        F2 = F0;
        Czy = false;
      } else {
        if (tau1 > eps) ni *= 0.2;
      }
    }
  } while (!(tau1 <= eps || m > maxit));
  FF(vekX, minF, 0, variableFileName, projectFileName, goalFileName, nVar);
  printf("realmm\n");
  for (int i = 0; i < XX; i++) printf("%lf %lf\n", P1[i], ideal[i]);
  printf("Goal function value:%.15f\n", *minF);
  printf("Variables:\n");
  for (int i = 0; i < nVar; i++) printf("%.15lf\n", vekX[i + 1].value);
  //*minF=FF(Rown, vekX);
  if (m > maxit)
    return 1;
  else
    return 0;
} /*minFunHJ */
