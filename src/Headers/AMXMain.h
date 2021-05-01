//#include "Headers/Unistd.h"
#include "string.h"
#include "stdio.h"
#include "malloc.h"

#ifndef __MAIN_H__
#define __MAIN_H__

#define LOCALE_NAME_MAX_LENGTH 228

#define MAX_DIS_CHARS 9

char disallowed_chars[] =
{
	':',
	'*',
	'?',
	'"',
	'<',
	'>',
	'|'
};

#define MAX_DIS_NAMES 24
char disallowed_names[MAX_DIS_NAMES][5] =
{
	"CON",
	"PRN",
	"AUX",
	"NUL",
	"COM1", 
	"COM2", 
	"COM3", 
	"COM4", 
	"COM5", 
	"COM6", 
	"COM7", 
	"COM8", 
	"COM9", 
	"COM0",
	"LPT1", 
	"LPT2", 
	"LPT3", 
	"LPT4", 
	"LPT5", 
	"LPT6", 
	"LPT7", 
	"LPT8", 
	"LPT9", 
	"LPT0"
};

typedef void (*logprintf_t)(char* format, ...);


logprintf_t logprintf;
extern void* pAMXFunctions;

#endif

int DoesStrContainChar(const char* string, char ch, size_t size)
{
	for(unsigned int i = 0; i <= size; i++)
	{
		if(string[i] == NULL || i >= strlen(string)) return 0;
		if(string[i] == ch) return 1;
	}

	return 0;
}

int DoesStrContainDisallowedChars(const char* string)
{
	for(unsigned int i = 0; i <= MAX_DIS_CHARS; i++) if(DoesStrContainChar(string, disallowed_chars[i], strlen(string))) return 1;
	return 0;
}

int IsStrDisallowedWinFileName(const char* string)
{
	for(int i = 0; i < MAX_DIS_NAMES; i++) if(strcmp(string, disallowed_names[i]) == 0) return 1;
	return 0;
}

bool IsValidFolderName(const char* string)
{
	if(strlen(string) == 0) return 0;

	if(strlen(string) == 1)
	{
		if (string[0] == ' ') return 0;
		if (string[0] == '.') return 0;
	}
	if(DoesStrContainDisallowedChars(string)) return 0;

#ifdef WIN32
	if(IsStrDisallowedWinFileName(string)) return 0;
#endif

	return 1;
}