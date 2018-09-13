/******************************************************************************
 * Filename:        bplib_os_posix.c
 * Purpose:         POSIX OS abstraction for Bundle Protocol Library
 * Design Notes:
 ******************************************************************************/

/******************************************************************************
 INCLUDES
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "bplib.h"

/******************************************************************************
 DEFINES
 ******************************************************************************/

#define MAX_LOG_ENTRY_SIZE  256
#define UNIX_SECS_AT_2000   946684800
#define MAX_MUTEXES         32

/******************************************************************************
 FILE DATA
 ******************************************************************************/

pthread_mutex_t* locks[MAX_MUTEXES] = {0};
pthread_mutex_t lock_of_locks;

/******************************************************************************
 EXPORTED FUNCTIONS
 ******************************************************************************/

/*--------------------------------------------------------------------------------------
 * bplib_os_init -
 *-------------------------------------------------------------------------------------*/
void bplib_os_init(void)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&lock_of_locks, &attr);
}

/*--------------------------------------------------------------------------------------
 * bplib_os_log -
 *
 * 	Returns - the error code passed in (for convenience)
 *-------------------------------------------------------------------------------------*/
int bplib_os_log(const char* file, unsigned int line, int error, const char* fmt, ...)
{
    char formatted_string[MAX_LOG_ENTRY_SIZE];
    va_list args;
	int vlen, msglen;

    /* Build Formatted String */
    va_start(args, fmt);
    vlen = vsnprintf(formatted_string, MAX_LOG_ENTRY_SIZE - 1, fmt, args);
    msglen = vlen < MAX_LOG_ENTRY_SIZE - 1 ? vlen : MAX_LOG_ENTRY_SIZE - 1;
    va_end(args);
    if (msglen < 0) return error; // nothing to do
    formatted_string[msglen] = '\0';

	/* Print Log Message */
    printf("%s:%d:%d:%s", file, line, error, formatted_string);

	/* Return Error Code */
	return error;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_memset -
 *-------------------------------------------------------------------------------------*/
void bplib_os_memset(void* addr, int len, int val)
{
	memset(addr, len, val);
}

/*--------------------------------------------------------------------------------------
 * bplib_os_memcpy -
 *-------------------------------------------------------------------------------------*/
void bplib_os_memcpy(void* dst, void* src, int len)
{
	memcpy(dst, src, len);
}

/*--------------------------------------------------------------------------------------
 * bplib_os_systime -
 *-------------------------------------------------------------------------------------*/
int bplib_os_systime(uint32_t* tm)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    *tm = now.tv_sec - 946684800;
    return BP_SUCCESS;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_createlock -
 *-------------------------------------------------------------------------------------*/
int bplib_os_createlock(void)
{
    int i;
    int handle = -1;
    pthread_mutex_lock(&lock_of_locks);
    {
        for(i = 0; i < MAX_MUTEXES; i++)
        {
            if(locks[i] == NULL)
            {
                locks[i] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
                pthread_mutexattr_t attr;
                pthread_mutexattr_init(&attr);
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
                pthread_mutex_init(locks[i], &attr);
                handle = i;
                break;
            }
        }
    }
    pthread_mutex_unlock(&lock_of_locks);
    return handle;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_destroylock -
 *-------------------------------------------------------------------------------------*/
void bplib_os_destroylock(int handle)
{
    pthread_mutex_lock(&lock_of_locks);
    {
        if(locks[handle] != NULL)
        {
            free(locks[handle]);
            locks[handle] = NULL;
        }
    }
    pthread_mutex_unlock(&lock_of_locks);
}

/*--------------------------------------------------------------------------------------
 * bplib_os_lock -
 *-------------------------------------------------------------------------------------*/
void bplib_os_lock(int handle)
{
    pthread_mutex_lock(locks[handle]);
}

/*--------------------------------------------------------------------------------------
 * bplib_os_unlock -
 *-------------------------------------------------------------------------------------*/
void bplib_os_unlock(int handle)
{
    pthread_mutex_unlock(locks[handle]);
}
