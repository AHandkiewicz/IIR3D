/*
 * dbg.h
 *
 *  Created on: Dec 22, 2015
 *      Author: konrad
 */

#ifndef INCLUDES_DBG_H_
#define INCLUDES_DBG_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#define clean_errno()

#define log_err(M, ...)

#define log_warn(M, ...)

#define log_info(M, ...)

#define check(A, M, ...)

#define sentinel(M, ...)

#define check_mem(A)

#define check_debug(A, M, ...)
#else
#define debug(M, ...)                                           \
  {                                                             \
    fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, \
            ##__VA_ARGS__);                                     \
    fflush(stderr);                                             \
  }
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...)                                                       \
  {                                                                           \
    fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, \
            clean_errno(), ##__VA_ARGS__);                                    \
    fflush(stderr);                                                           \
  }

#define log_warn(M, ...)                                                     \
  {                                                                          \
    fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, \
            clean_errno(), ##__VA_ARGS__);                                   \
    fflush(stderr);                                                          \
  }

#define log_info(M, ...)                                          \
  {                                                               \
    fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, \
            ##__VA_ARGS__);                                       \
    fflush(stderr);                                               \
  }

#define check(A, M, ...)       \
  if (!(A)) {                  \
    log_err(M, ##__VA_ARGS__); \
    errno = 0;                 \
    goto error;                \
  }

#define sentinel(M, ...)       \
  {                            \
    log_err(M, ##__VA_ARGS__); \
    errno = 0;                 \
    goto error;                \
  }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) \
  if (!(A)) {                  \
    debug(M, ##__VA_ARGS__);   \
    errno = 0;                 \
    goto error;                \
  }
#endif

#endif /* INCLUDES_DBG_H_ */
