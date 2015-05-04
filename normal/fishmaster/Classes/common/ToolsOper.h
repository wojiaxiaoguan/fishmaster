//
//  ToolsOper.h
//  DFHD_LOG
//
//

#ifndef __DFHD_LOG__ToolsOper__
#define __DFHD_LOG__ToolsOper__

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "cocos2d.h"
class ToolsOper
{
public:
    static void WriteLog(const char *pszFormat,...);
};
#define DF_LOG(format,...)    ToolsOper::WriteLog(format,##__VA_ARGS__)
#define MAX_LOGLEN     2048
#endif /* defined(__DFHD_LOG__ToolsOper__) */
