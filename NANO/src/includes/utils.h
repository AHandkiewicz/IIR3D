/*
 * utils.h
 *
 *  Created on: Sep 26, 2018
 *      Author: konrad
 */

#ifndef INCLUDES_UTILS_H_
#define INCLUDES_UTILS_H_

#define true 1
#define false 0

#define COMPILED_TIME __TIME__
#define COMPILED_DATE __DATE__

struct options {
  char version;
  char help;
  char iterrations;
  int maxIter;
  int dim;
  int d1;
  int d2;
  int d3;
  float tau;
  char projectFileName[256];
  char variableFileName[256];
  char initialFileName[256];
  char goalFileName[256];
  char analyze;
  char real;
  char realmm;
  char Tau;
  char nrAnalFiles;
  char analyzeType;
  char random;
  int nrFiles;
#ifdef CACHE
  int maxCache;
  char cache;
#endif
};

extern char *progname;
void PrintfBold(char *string);
void Usage(void);
int getoptions(int argc, char *argv[], struct options *opt);
#endif /* INCLUDES_UTILS_H_ */
