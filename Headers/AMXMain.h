#include "Headers/Unistd.h"
#include "String.h"
#include "stdio.h"
#include "malloc.h"

#ifndef __MAIN_H__
	#define __MAIN_H__

#define LOCALE_NAME_MAX_LENGTH 85
#endif

typedef void (*logprintf_t)(char* format, ...);


logprintf_t logprintf;
extern void* pAMXFunctions;