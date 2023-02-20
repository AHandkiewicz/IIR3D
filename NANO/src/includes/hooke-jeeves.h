/*
 * hooke-jeeves.h
 *
 *  Created on: Dec 13, 2016
 *      Author: konrad
 */

#ifndef INCLUDES_HOOKE_JEEVES_H_
#define INCLUDES_HOOKE_JEEVES_H_
#include <stdio.h>
#include <stdlib.h>
#ifdef CACHE

struct cache {
  double *values;
  double result;
};
extern struct cache *cacheData;
extern int maxCache;
#endif

struct variable {
  double value; /* initial parameter value */
  double min;   /* minimum value */
  double max;   /* maximum value */
  double step;  /* minimum step value */
};

int minFunHJ(struct variable *vekX, double eps, double tau, int maxit,
             double *minF,
             int (*FF)(struct variable *vekX, double *value, int thr_num,
                       char *variableFileName, char *projectFileName,
                       char *goalFileName, int nVar),
             int nVar, char *initialFileName, char *projectFileName,
             char *goalFileName, char *variableFileName);
int minFunHJReal(struct variable *vekX, double eps, double tau, int maxit,
                 double *minF,
                 int (*FF)(struct variable *vekX, double *value, int thr_num,
                           char *variableFileName, char *projectFileName,
                           char *goalFileName, int nVar),
                 int nVar, char *initialFileName, char *projectFileName,
                 char *goalFileName, char *variableFileName);
int minFunHJRealMinMax(struct variable *vekX, double eps, double tau, int maxit,
                       double *minF,
                       int (*FF)(struct variable *vekX, double *value,
                                 int thr_num, char *variableFileName,
                                 char *projectFileName, char *goalFileName,
                                 int nVar),
                       int nVar, char *initialFileName, char *projectFileName,
                       char *goalFileName, char *variableFileName);
int FF(struct variable *vekX, double *value, int thr_num,
       char *variableFileName, char *projectFileName, char *goalFileName,
       int nVar);
int saveParams(FILE *fp, struct variable *vekX, unsigned int lines, int thr_num,
               char *variableFileName);
int loadParams(FILE *fp, struct variable *vekX, unsigned int lines,
               char *initialFileName);
int allocMem(FILE *fp, char *initialFileName);
int checkCache(struct variable *vekX, double *value, int nVar);
int addToCache(struct variable *vekX, double *value, int nVar);
double calculation(struct variable *vekX, int nVar);
int initSN(char *prjName);

#endif /* INCLUDES_HOOKE_JEEVES_H_ */
