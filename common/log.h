#pragma once
#include <stdio.h>

#define LOG_LEVEL_DEBUG 4
#define LOG_LEVEL_INFO  3
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_ERR   1

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

#define LOG_ERROR(fmt, ...) if (LOG_LEVEL >= LOG_LEVEL_ERR)  printf("[ERR] " fmt "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  if (LOG_LEVEL >= LOG_LEVEL_WARN) printf("[WRN] " fmt "\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  if (LOG_LEVEL >= LOG_LEVEL_INFO) printf("[INF] " fmt "\n", ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) if (LOG_LEVEL >= LOG_LEVEL_DEBUG) printf("[DBG] " fmt "\n", ##__VA_ARGS__)

void log_init(void);
