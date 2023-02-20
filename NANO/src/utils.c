/*
 * utils.c
 *
 *  Created on: Sep 26, 2018
 *      Author: konrad
 */

#include "includes/utils.h"

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "includes/dbg.h"

char appname[] = "Hooke-Jeeves optimizer";
char author[] = "Mariusz Naumowicz";
char version[22] = COMPILED_DATE;

#define STYLE_UNDERLINE "\033[4m"
#define STYLE_NO_UNDERLINE "\033[24m"

#define STYLE_BOLD "\033[1m"
#define STYLE_NO_BOLD "\033[22m"

char *progname = NULL;
int d1, d2, d3;
/* print version information */
void Version(void) {
  strcat(version, " - ");
  strcat(version, COMPILED_TIME);
  fprintf(stdout, "%s %s Rev:%s\n", appname, version, VERSION);
}

void PrintfBold(const char *string) {
  printf(STYLE_BOLD);
  printf("%s", string);
  printf(STYLE_NO_BOLD);
}

/* print usage message and exit with 0x48k status */
void Usage(void) {
  printf("Usage:\n\n");
  printf(
      " %s <option> [argument] <project filename> <filename of initial values> "
      "<filename of variables> <goal function value>\n\n",
      progname);
  printf("Available options are:\n\n");
  PrintfBold(" -i\n");
  printf("\t\t Number of algorithm iterations\n");
  PrintfBold(" -help\n");
  printf("\t\t Shows all available options\n");
  PrintfBold(" -log\n");
  printf("\t\t Create log file\n");
  PrintfBold(" -version\n");
  printf("\t\t Print the exact optimizer version\n");
  printf("\n");
}

int getoptions(int argc, char *argv[], struct options *opt) {
  int argNumber = 0;
  char go = true;
  FILE *fp = 0;
  if (argc == 1) {
    Version();
    Usage();
    return -1;
  }
  argNumber++;
  while (argNumber < argc) {
    while (go) {
      if (argv[argNumber][0] != '-') {
        go = false;
        break;
      }
      if (!strcmp(argv[argNumber], "-i") && opt->iterrations == false) {
        opt->iterrations = true;
        argNumber++;
        if (argNumber < argc) {
          opt->maxIter = atoi(argv[argNumber]);
          if (opt->maxIter <= 0) {
            log_warn("Iterations number has to be greater than 0!");
            return -1;
          }
        }
        break;
      }
      if (!strcmp(argv[argNumber], "-t") && opt->iterrations == false) {
        opt->Tau = true;
        argNumber++;
        if (argNumber < argc) {
          opt->tau = atof(argv[argNumber]);
        }
        break;
      }
      if (!strcmp(argv[argNumber], "-f") && opt->nrAnalFiles == false) {
        opt->nrAnalFiles = true;
        argNumber++;
        if (argNumber < argc) {
          opt->nrFiles = atoi(argv[argNumber]);
          if (opt->nrFiles <= 0) {
            log_warn("Number number of files has to be greater than 0!");
            return -1;
          }
        }
        break;
      }
      if (!strcmp(argv[argNumber], "-n") &&
          (opt->real == true || opt->realmm == true)) {
        opt->random = true;
        break;
      }
      if (!strcmp(argv[argNumber], "-r") && opt->real == false) {
        opt->real = true;
        break;
      }
      if (!strcmp(argv[argNumber], "-x") && opt->real == false) {
        opt->realmm = true;
        break;
      }

      if (!strcmp(argv[argNumber], "-d")) {
        argNumber++;
        d1 = 1;
        d2 = 1;
        d3 = 1;
        //      if (argNumber < argc) {
        //      opt->dim = atoi(argv[argNumber]);
        // argNumber++;
        d1 = atoi(argv[argNumber]);
        // if (opt->dim > 1) {
        argNumber++;
        d2 = atoi(argv[argNumber]);
        //      }
        // if (opt->dim > 2) {
        argNumber++;
        d3 = atoi(argv[argNumber]);
        //}
        //      }
        break;
      }

      if (!strcmp(argv[argNumber], "-a") && opt->analyze == false) {
        opt->analyze = true;
        argNumber++;
        if (argNumber < argc) {
          opt->analyzeType = *argv[argNumber];
          if (!(opt->analyzeType == 't' || opt->analyzeType == 's' ||
                opt->analyzeType == 'z' || opt->analyzeType == 'm')) {
            log_warn("Wrong analyze!");
            return -1;
          }
        }
        break;
      }
#ifdef CACHE
      if (!strcmp(argv[argNumber], "-c") && opt->cache == false) {
        opt->cache = true;
        argNumber++;
        if (argNumber < argc) {
          opt->maxCache = atoi(argv[argNumber]);
          if (opt->maxCache <= 0) {
            log_warn("Cache number has to be greater than 0!");
            return -2;
          }
        }
        break;
      }
#endif
      if (!strcmp(argv[argNumber], "-version") && opt->version == false) {
        Version();
        opt->version = true;
        argNumber++;
        return -3;
      }
      if (!strcmp(argv[argNumber], "-help") && opt->help == false) {
        Usage();
        opt->help = true;
        argNumber++;
        return -4;
      }
      break;
    }
    if (go == false) break;
    argNumber++;
  }
  if (argNumber < argc) {
    strcpy(opt->projectFileName, argv[argNumber]);
    fp = fopen(opt->projectFileName, "r");
    if (fp) {
      /* exists */
      fclose(fp);
    } else {
      /* doesn't exist */
      log_err("Project file %s cannot be opened!", opt->projectFileName);
      return -5;
    }
  }
  argNumber++;
  if (argNumber < argc) {
    strcpy(opt->initialFileName, argv[argNumber]);
    fp = fopen(opt->initialFileName, "r");
    if (fp) {
      /* exists */
      fclose(fp);
    } else {
      /* doesn't exist */
      log_err("Initialization file %s cannot be opened!", opt->initialFileName);
      return -6;
    }
  }

  return 0;
}
