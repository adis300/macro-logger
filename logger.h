/*
 * Copyright (c) 2012 David Rodrigues
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifndef LOG_LEVEL
#define LOG_LEVEL   INFO_LEVEL
#endif

#include <stdio.h>
#include <time.h>
#include <string.h>
// #endif

// === auxiliar functions
static inline char *timenow() {
    static char buffer[64];
    time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer, 64, "%H:%M:%S", timeinfo);
    
    return buffer;
}

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define NO_LOG          0x00
#define ERROR_LEVEL     0x01
#define WARNING_LEVEL   0x02
#define INFO_LEVEL      0x03
#define DEBUG_LEVEL     0x04

#ifdef __ANDROID__
#include <android/log.h>
#define PRINTF(format, ...)      __android_log_print(ANDROID_LOG_INFO, "FusiSDK", format , __VA_ARGS__)
#else
#define PRINTF(format, ...)      fprintf(stderr, format, __VA_ARGS__)
#endif

#define LOG_FMT             "%s [%s][Your Tag:%s:%d]>%s:"
#define LOG_ARGS(LOG_TAG)   timenow(), LOG_TAG, _FILE, __LINE__, __FUNCTION__

#define NEWLINE     "\n"

#define ERROR_TAG   "ERROR"
#define WARN_TAG "WARN"
#define INFO_TAG    "INFO"
#define DEBUG_TAG   "DEBUG"

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, ...)     PRINTF(LOG_FMT message NEWLINE, LOG_ARGS(DEBUG_TAG), ##__VA_ARGS__)
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, ...)      PRINTF(LOG_FMT message NEWLINE, LOG_ARGS(INFO_TAG), ##__VA_ARGS__)
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL >= WARNING_LEVEL
#define LOG_WARN(message, ...)     PRINTF(LOG_FMT message NEWLINE, LOG_ARGS(WARN_TAG), ##__VA_ARGS__)
#else
#define LOG_WARN(message, ...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, ...)     PRINTF(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ##__VA_ARGS__)
#else
#define LOG_ERROR(message, ...)
#endif

#if LOG_LEVEL >= NO_LOGS
#define LOG_IF_ERROR(condition, message, ...) if (condition) PRINTF(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ##__VA_ARGS__)
#else
#define LOG_IF_ERROR(condition, message, ...)
#endif

#endif