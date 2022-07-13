#undef LOCALE_NAME_MAX_LENGTH

#ifndef WIN32
#include <unistd.h>
#include <sys\stat.h>
#include "Headers/amx/sclinux.h"
#else
#include <direct.h>
#endif

char debug[256];

#include "Headers\amx\amx.h"
#include "Headers\plugincommon.h"

#include "Headers\AMXMain.h"

char dir[228] = "";

cell DoesFolderExist(const char* dir)
{
    cell success = 0;
#ifdef WIN32
    success = _mkdir(dir);
#else
    success = mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    if(success != 0) return 1;
#ifdef WIN32
    _rmdir(dir);
#else
    rmdir(dir);
#endif

    return 0;
}

void GetDirectory(const char* string, char* dest)
{
#ifdef WIN32
    snprintf(dest, 256, "%s\\%s", dir, string);
#else
    snprintf(dest, 256, "%s/%s", dir, string);
#endif
}

cell AMX_NATIVE_CALL RmDir(AMX* amx, cell* params)
{
	char* string = nullptr;

	amx_StrParam(amx, params[1], string);

	char dir[LOCALE_NAME_MAX_LENGTH];
	GetDirectory(string, dir);

	if(!DoesFolderExist(dir)) return 0;
	
	char str[128] = "";
	snprintf(str, 128, "<Plugin> Folder Deleted: scriptfiles/%s", string);
	
#ifdef WIN32
	_rmdir(dir);
#else
	rmdir(dir);
#endif
	
	logprintf(str);
	return 1;
}

cell AMX_NATIVE_CALL ChDir(AMX* amx, cell* params)
{
    char* string = nullptr;

    amx_StrParam(amx, params[1], string);

    char dir[LOCALE_NAME_MAX_LENGTH];
    GetDirectory(string, dir);
    return DoesFolderExist(dir);
}

cell AMX_NATIVE_CALL MkDir(AMX* amx, cell* params)
{
    char* string = nullptr;

    amx_StrParam(amx, params[1], string);

    if(!IsValidFolderName(string)) return 0;
    
	char new_dir[LOCALE_NAME_MAX_LENGTH];
    GetDirectory(string, new_dir);

    if(DoesFolderExist(new_dir)) return 0;

    char* str = (char*) calloc(128, sizeof(char));
    snprintf(str, 128, "<Plugin> Folder Created: scriptfiles/%s", string);
	
#ifdef WIN32
    _mkdir(new_dir);
#else
	mkdir(new_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
	
	logprintf(str);

    logprintf((char*) "MkDir finished");

    free(str);
    return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;}

PLUGIN_EXPORT int PLUGIN_CALL Load(void **ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t) ppData[PLUGIN_DATA_LOGPRINTF];

    snprintf(dir, LOCALE_NAME_MAX_LENGTH, "%s", _getcwd(dir, LOCALE_NAME_MAX_LENGTH));

    GetDirectory("scriptfiles", dir);

    char folder_dir[LOCALE_NAME_MAX_LENGTH];
    snprintf(folder_dir, LOCALE_NAME_MAX_LENGTH, "<Plugin> Loaded at: %s", dir);

    logprintf(folder_dir);
    return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {logprintf((char*) "<Plugin> Unloaded.");}

AMX_NATIVE_INFO PluginNatives[] =
{
    {"MkDir", MkDir},
    {"ChDir", ChDir},
    {"RmDir", RmDir},
    {0, 0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
    return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) {return AMX_ERR_NONE;}
