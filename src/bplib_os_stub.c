/******************************************************************************
 * Filename:        bplib_os_stub.c
 * Purpose:         Stubbed out OS abstraction for Bundle Protocol Library
 * Design Notes:
 ******************************************************************************/

/******************************************************************************
 INCLUDES
 ******************************************************************************/


#include "bplib.h"


/******************************************************************************
 EXPORTED FUNCTIONS
 ******************************************************************************/

/*--------------------------------------------------------------------------------------
 * bplib_os_init -
 *-------------------------------------------------------------------------------------*/
void bplib_os_init(void)
{
}

/*--------------------------------------------------------------------------------------
 * bplib_os_log -
 *
 * 	Returns - the error code passed in (for convenience)
 *-------------------------------------------------------------------------------------*/
int bplib_os_log(const char* file, unsigned int line, int error, const char* fmt, ...)
{
    (void)file;
    (void)line;
    (void)error;
    (void)fmt;
	return 0;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_memset -
 *-------------------------------------------------------------------------------------*/
void bplib_os_memset(void* addr, int len, int val)
{
    (void)addr;
    (void)len;
    (void)val;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_memcpy -
 *-------------------------------------------------------------------------------------*/
void bplib_os_memcpy(void* dst, void* src, int len)
{
    (void)dst;
    (void)src;
    (void)len;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_systime -
 *-------------------------------------------------------------------------------------*/
int bplib_os_systime(uint32_t* tm)
{
    (void)tm;
    return 0;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_createlock -
 *-------------------------------------------------------------------------------------*/
int bplib_os_createlock(void)
{
    return 0;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_destroylock -
 *-------------------------------------------------------------------------------------*/
void bplib_os_destroylock(int handle)
{
    (void)handle;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_lock -
 *-------------------------------------------------------------------------------------*/
void bplib_os_lock(int handle)
{
    (void)handle;
}

/*--------------------------------------------------------------------------------------
 * bplib_os_unlock -
 *-------------------------------------------------------------------------------------*/
void bplib_os_unlock(int handle)
{
    (void)handle;
}
