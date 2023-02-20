/*
 * cunittestss.c
 *
 *  Created on: Aug 22, 2018
 *      Author: konrad
 */

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <memory.h>
#include <stdio.h>  // for printf
#include <stdlib.h>

#include "includes/dbg.h"
#include "includes/hooke-jeeves.h"
#include "includes/utils.h"

/* Test Suite setup and cleanup functions: */
#ifdef CACHE
struct cache *cacheData;
int maxCache = 2;
#endif
int init_suite(void) { return 0; }

int clean_suite(void) { return 0; }

char logg;
void add_cache_test(void) {
  // CU_ASSERT_EQUAL( max(1,2), 2);
  // CU_ASSERT_EQUAL( max(2,1), 2);
  struct variable vekX[4];
  vekX[0].value = 1.1;
  vekX[0].step = 0.1;
  vekX[0].min = 0.1;
  vekX[0].max = 2.1;

  vekX[1].value = 3.1;
  vekX[1].step = 0.1;
  vekX[1].min = 0.1;
  vekX[1].max = 2.1;

  vekX[2].value = 4.1;
  vekX[2].step = 0.1;
  vekX[2].min = 0.1;
  vekX[2].max = 2.1;

  vekX[3].value = 5.1;
  vekX[3].step = 0.1;
  vekX[3].min = 0.1;
  vekX[3].max = 2.1;

  double val = 1.2;
  int nvar = 3;
#ifdef CACHE
  cacheData = (struct cache *)malloc(sizeof(struct cache) * (maxCache));
#endif
  addToCache(vekX, &val, nvar);
  if (cacheData[0].values[1] == vekX[1].value &&
      cacheData[0].values[2] == vekX[2].value &&
      cacheData[0].values[3] == vekX[3].value && cacheData[0].result == val)
    CU_ASSERT(1)
  else
    CU_ASSERT(0);

  vekX[0].value = 1.1;
  vekX[0].step = 0.1;
  vekX[0].min = 0.1;
  vekX[0].max = 2.1;

  vekX[1].value = 30.1;
  vekX[1].step = 0.1;
  vekX[1].min = 0.1;
  vekX[1].max = 2.1;

  vekX[2].value = 40.1;
  vekX[2].step = 0.1;
  vekX[2].min = 0.1;
  vekX[2].max = 2.1;

  vekX[3].value = 50.1;
  vekX[3].step = 0.1;
  vekX[3].min = 0.1;
  vekX[3].max = 2.1;

  val = 1.3;
  addToCache(vekX, &val, nvar);
  if (cacheData[1].values[1] == vekX[1].value &&
      cacheData[1].values[2] == vekX[2].value &&
      cacheData[1].values[3] == vekX[3].value && cacheData[1].result == val)
    CU_ASSERT(1)
  else
    CU_ASSERT(0);

  vekX[0].value = 1.1;
  vekX[0].step = 0.1;
  vekX[0].min = 0.1;
  vekX[0].max = 2.1;

  vekX[1].value = 6.1;
  vekX[1].step = 0.1;
  vekX[1].min = 0.1;
  vekX[1].max = 2.1;

  vekX[2].value = 7.1;
  vekX[2].step = 0.1;
  vekX[2].min = 0.1;
  vekX[2].max = 2.1;

  vekX[3].value = 8.1;
  vekX[3].step = 0.1;
  vekX[3].min = 0.1;
  vekX[3].max = 2.1;

  val = 1.4;
  addToCache(vekX, &val, nvar);
  if (cacheData[0].values[1] == vekX[1].value &&
      cacheData[0].values[2] == vekX[2].value &&
      cacheData[0].values[3] == vekX[3].value && cacheData[0].result == val)
    CU_ASSERT(1)
  else
    CU_ASSERT(0);
}

void check_cache_test(void) {
  struct variable vekX[4];
  vekX[0].value = 1.1;
  vekX[0].step = 0.1;
  vekX[0].min = 0.1;
  vekX[0].max = 2.1;

  vekX[1].value = 6.1;
  vekX[1].step = 0.1;
  vekX[1].min = 0.1;
  vekX[1].max = 2.1;

  vekX[2].value = 7.1;
  vekX[2].step = 0.1;
  vekX[2].min = 0.1;
  vekX[2].max = 2.1;

  vekX[3].value = 8.1;
  vekX[3].step = 0.1;
  vekX[3].min = 0.1;
  vekX[3].max = 2.1;
  double val = 1.4;
  CU_ASSERT_EQUAL(checkCache(vekX, &val, 3), 1);
  vekX[3].value = 1.111;
  CU_ASSERT_EQUAL(checkCache(vekX, &val, 3), 0);

  vekX[0].value = 1.1;
  vekX[0].step = 0.1;
  vekX[0].min = 0.1;
  vekX[0].max = 2.1;

  vekX[1].value = 3.1;
  vekX[1].step = 0.1;
  vekX[1].min = 0.1;
  vekX[1].max = 2.1;

  vekX[2].value = 4.1;
  vekX[2].step = 0.1;
  vekX[2].min = 0.1;
  vekX[2].max = 2.1;

  vekX[3].value = 5.1;
  vekX[3].step = 0.1;
  vekX[3].min = 0.1;
  vekX[3].max = 2.1;

  CU_ASSERT_EQUAL(checkCache(vekX, &val, 3), 0);
}

void getoptions_test(void) {
  struct options opt;
  memset(&opt, 0, sizeof(struct options));
  char *argv[7];
  argv[0] = "unittests";
  argv[1] = "-i";
  argv[2] = "100";
  argv[3] = "unittests";
  argv[4] = "unittests";
  argv[5] = "unittests";
  argv[6] = "unittests";
  CU_ASSERT_EQUAL(getoptions(7, argv, &opt), 0);
  memset(&opt, 0, sizeof(struct options));
  argv[0] = "unittests";
  argv[1] = "-i";
  argv[2] = "100";
  argv[3] = "proj1";
  argv[4] = "unittests";
  argv[5] = "unittests";
  argv[6] = "unittests";
  CU_ASSERT_EQUAL(getoptions(7, argv, &opt), -5);
  memset(&opt, 0, sizeof(struct options));
  argv[0] = "unittests";
  argv[1] = "-i";
  argv[2] = "100";
  argv[3] = "unittests";
  argv[4] = "proj1";
  argv[5] = "unittests";
  argv[6] = "proj";
  CU_ASSERT_EQUAL(getoptions(7, argv, &opt), -6);
  memset(&opt, 0, sizeof(struct options));
  argv[0] = "unittests";
  argv[1] = "-i";
  argv[2] = "-100";
  argv[3] = "unittests";
  argv[4] = "proj1";
  argv[5] = "unittests";
  argv[6] = "proj";
  CU_ASSERT_EQUAL(getoptions(7, argv, &opt), -1);
  memset(&opt, 0, sizeof(struct options));
  argv[0] = "unittests";
  argv[1] = "-i";
  argv[2] = "sd";
  argv[3] = "unittests";
  argv[4] = "proj1";
  argv[5] = "unittests";
  argv[6] = "proj";
  CU_ASSERT_EQUAL(getoptions(7, argv, &opt), -1);
}

void hj_allocmem_test(void) {}

void hj_loadparams_test(void) {}

void hj_saveparams_test(void) {}

int main(void) {
  CU_pSuite pSuiteCache = NULL;
  CU_pSuite pSuiteOptions = NULL;
  CU_pSuite pSuiteHJ = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

  /* add a suite to the registry */
  pSuiteCache = CU_add_suite("cache_test_suite", init_suite, clean_suite);
  if (NULL == pSuiteCache) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  pSuiteOptions = CU_add_suite("options_test_suite", init_suite, clean_suite);
  if (NULL == pSuiteCache) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  pSuiteHJ = CU_add_suite("hj_test_suite", init_suite, clean_suite);
  if (NULL == pSuiteHJ) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuiteCache, "add_cache_test", add_cache_test)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuiteCache, "check_cache_test", check_cache_test)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuiteOptions, "options_test", getoptions_test)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuiteHJ, "hj_allocmem_test", hj_allocmem_test)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuiteHJ, "hj_loadparams_test", hj_loadparams_test)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuiteHJ, "hj_saveparams_test", hj_saveparams_test)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run all tests using the basic interface
  CU_basic_set_mode(CU_BRM_SILENT);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Run all tests using the automated interface */
  //  CU_automated_run_tests();
  //  CU_list_tests_to_file();
  /*
     // Run all tests using the automated interface
     CU_automated_run_tests();
     CU_list_tests_to_file();

     // Run all tests using the console interface
     CU_console_run_tests();
   */
  /* Clean up registry and return */
  CU_cleanup_registry();
  return CU_get_error();
}
