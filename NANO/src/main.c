#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "includes/dbg.h"
#include "includes/hooke-jeeves.h"
#include "includes/utils.h"
extern int initSN(char *prjName);
/* number of variables */
int var = 0;
char logg;
#define DEBUG 1

int lines = 0;

int thrs = 0;

#ifdef CACHE
struct cache *cacheData;
int maxCache = 0;
#endif
float ideal[819200];
extern char anal;
extern int nr;
int loadIdeal(char analize, int nrFiles, float *idealValues, int *samp) {
  int lines = 0;
  FILE *fp = 0;
  int i, x;
  /* string line from file */
  char text[256];
  char str[12];
  /* name of file */
  char fname[256];
  /* temporary char */
  char *pch;
  /* number of column to read */
  int column;
  int result = 0;
  x = 0;
  if (analize == 's') {
    x = 0;
    for (i = 0; i < nrFiles; i++) {
      lines = 0;
      sprintf(str, "%d", i);
      strcpy(fname, "s");
      strcat(fname, str);
      printf("fname:%s\n", fname);
      if ((fp = fopen(fname, "r")) == NULL) return -1;
      /* read number of lines */
      do {
        if (lines > 1) {
          result = fscanf(fp, "%[^\n]\n", text);
          if (result != EOF) {
            pch = strtok(text, " ");
            while (pch != NULL) {
              pch = strtok(NULL, " ");
              if (pch != NULL) {
                idealValues[x] = (double)atof(pch);
//                printf("pch:%s\n", pch);
              }
            }
            x++;
          }
        } else if (lines == 0) {
          result = fscanf(fp, "%d\n", &column);
        } else if (lines == 1)
          result = fscanf(fp, "%[^\n]\n", text);
        lines++;
      } while (result != EOF);
      if (fp) fclose(fp);
    }

    for (i = 0; i < x; i++) printf("ideal:%lf\n", idealValues[i]);
  }

  if (analize == 'z') {
    x = 0;
    for (i = 0; i < nrFiles; i++) {
      lines = 0;
      sprintf(str, "%d", i);
      strcpy(fname, "z");
      strcat(fname, str);
      printf("fname:%s\n", fname);
      if ((fp = fopen(fname, "r")) == NULL) return -1;
      /* read number of lines */
      do {
        if (lines > 1) {
          result = fscanf(fp, "%[^\n]\n", text);
          if (result != EOF) {
            pch = strtok(text, " ");
            while (pch != NULL) {
              pch = strtok(NULL, " ");
              if (pch != NULL) {
                idealValues[x] = (double)atof(pch);
//                printf("pch:%s\n", pch);
              }
            }
            x++;
          }
        } else if (lines == 0) {
          result = fscanf(fp, "%d\n", &column);
        } else if (lines == 1)
          result = fscanf(fp, "%[^\n]\n", text);
        lines++;
      } while (result != EOF);
      if (fp) fclose(fp);
    }

    for (i = 0; i < x; i++) printf("ideal:%lf\n", idealValues[i]);
  }

  if (analize == 't' || analize == 'm') {
    x = 0;

    for (i = 1; i < nrFiles; i++) {
      int sam = 0;
      lines = 0;
      sprintf(str, "%d", i);
      strcpy(fname, "t");
      strcat(fname, str);
      /*printf("fname:%s\n", fname); */
      if ((fp = fopen(fname, "r")) == NULL) return -1;
      /* read number of lines */
      do {
//        printf("r %d\n", x);
        result = fscanf(fp, "%f\n", &idealValues[x]);
        x++;
        sam++;
//        printf("id:%f\n", idealValues[x - 1]);
      } while (result != EOF);
      // exit(-1);
      x--;
      sam--;
      *samp = sam;
      // nr=x;
      if (fp) fclose(fp);
    }

    /*for (i = 0; i < x; i++)
       printf("%f\n", io[i]); */
  }
  return x;
}

int XX;
int samp;
int main(int argc, char *argv[]) {
  int zarodek;
  time_t tt;
  double eps = 1e-15;
  int i = 0;
  // int maxIter = 10;
  double minimumValue = 0;
  /* clock_t start, finish; */
  FILE *fp = 0;
  struct variable *vekX;
  int err = 0;
  struct options opt = {0};
  opt.tau = 1e-3;
  memset(&opt, 0, sizeof(struct options));

#ifndef NDEBUG
  FILE *logger = 0;
#endif
  progname = argv[0];

  if (getoptions(argc, argv, &opt) != 0) {
    return -1;
  }
#ifndef NDEBUG

  logger = freopen("hjoptimizer.log", "w", stderr);
  if (logger == 0) {
    debug("Logger problem");
    log_err("Can't open %s file", "hjoptimizer.log");
    return -1;
  }
#endif
  maxCache = opt.maxCache;

  lines = allocMem(fp, opt.initialFileName);
  var = lines;
  if (lines <= 0) {
    log_err("Can't open file!");
    return -1;
  }
  log_info("%d variables", lines);
  vekX = (struct variable *)malloc(sizeof(struct variable) * (var + 1));
#ifdef CACHE
  cacheData = (struct cache *)malloc(sizeof(struct cache) * (maxCache));
#endif
  if (loadParams(fp, vekX, lines, opt.initialFileName) <= 0)
    if (lines <= 0) {
      free(vekX);
      log_err("Can't open file!");
      return -1;
    }
  if (opt.random == true) {
    zarodek = time(&tt);
    srand(zarodek);
    if (opt.real)
      for (i = 1; i < var + 1; i++)
        vekX[i].value = ((rand() % 10000)) / 10000.0;
    else {
      for (i = 1; i < var + 1; i++) {
        vekX[i].value =
            ((((rand() % 10000)) / 10000.0) * (vekX[i].max - vekX[i].min)) +
            vekX[i].min;
        printf("Init:%f\n", vekX[i].value);
      }
    }
  }

  opt.nrFiles=initSN(opt.projectFileName);
  XX = loadIdeal(opt.analyzeType, opt.nrFiles, ideal, &samp);
  // for (int i=0;i<255;i++)
  // printf("idealne:%f",ideal[i]);
  // exit(-1);
  anal = opt.analyzeType;
  nr = opt.nrFiles;
  /* start = clock(); */
  if (opt.real)
    err = minFunHJReal(vekX, 1e-12, (double)opt.tau, opt.maxIter, &minimumValue,
                       FF, var, opt.initialFileName, opt.projectFileName,
                       opt.goalFileName, opt.variableFileName);
  else if (opt.realmm) {
    err = minFunHJRealMinMax(vekX, 1e-12, (double)opt.tau, opt.maxIter,
                             &minimumValue, FF, var, opt.initialFileName,
                             opt.projectFileName, opt.goalFileName,
                             opt.variableFileName);
  } else
    err = minFunHJ(vekX, eps, 1e-0, opt.maxIter, &minimumValue, FF, var,
                   opt.initialFileName, opt.projectFileName, opt.goalFileName,
                   opt.variableFileName);
  /* finish = clock(); */
  if (err == -1) {
    debug("Optimization problem");
    log_err("Optimization error!");
  }
  /* duration = (double) (finish - start) / CLOCKS_PER_SEC; */

  for (i = 1; i < var + 1; i++)
    log_info("Variable %d = %.3f", i, vekX[i].value);
  log_info("Goal function: %f", minimumValue);

  if (vekX) free(vekX);
#ifndef NDEBUG
  if (logger) fclose(logger);
#endif
  return 0;
}
