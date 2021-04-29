#ifndef WIN32
#include <unistd.h>
#define _malloca malloc
#define _mkdir rmdir
#else
#include "Headers\Unistd.h"
#endif

#include "Headers\AMXMain.h"

#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"
#include "../Headers/AMXMain.h"

char dir[LOCALE_NAME_MAX_LENGTH + 5] = "";

cell AMX_NATIVE_CALL MkDir(AMX* amx, cell* params)
{
    if(strlen(dir) == 0) return 0;
    char new_dir[LOCALE_NAME_MAX_LENGTH];

    char* string = nullptr;

    amx_StrParam(amx, params[1], string);

    if(!IsValidFolderName(string)) return 0;

#ifdef WIN32
    snprintf(new_dir, LOCALE_NAME_MAX_LENGTH, "%s\\%s", dir, string);
#else
    snprintf(new_dir, LOCALE_NAME_MAX_LENGTH, "%s/%s", dir, string);
#endif

    char str[128] = "";
    snprintf(str, 128, "<Plugin> File Created: scriptfiles/%s", new_dir);

    logprintf(str);
    _mkdir(new_dir);
    return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;}

PLUGIN_EXPORT int PLUGIN_CALL Load(void **ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t) ppData[PLUGIN_DATA_LOGPRINTF];

    snprintf(dir, LOCALE_NAME_MAX_LENGTH, "%s", getcwd(dir, LOCALE_NAME_MAX_LENGTH));

    char folder_dir[128];
    snprintf(folder_dir, LOCALE_NAME_MAX_LENGTH, "<Plugin> loaded at: %s", dir);

#ifdef WIN32
    snprintf(dir, LOCALE_NAME_MAX_LENGTH, "%s\\%s", dir, "scriptfiles");
#else
    snprintf(dir, LOCALE_NAME_MAX_LENGTH, "%s/%s", dir, "scriptfiles");
#endif

    logprintf(folder_dir);
    return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {logprintf("<Plugin> unloaded.");}

AMX_NATIVE_INFO PluginNatives[] =
{
    {"MkDir", MkDir},
    {0, 0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
    return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) {return AMX_ERR_NONE;}
