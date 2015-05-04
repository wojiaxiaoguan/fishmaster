//
//  ToolsOper.cpp
//  DFHD_LOG
//
//

#include "ToolsOper.h"
#include "common.h"
void ToolsOper::WriteLog(const char * pszFormat,...)
{
#ifndef PUBLISH_TEST   //  此处替换为正式打包的宏
#else
    static FILE *fp = NULL;
    
    // write file
    if (fp == NULL)
    {
        std::string mlogPath = "/Dingfeng_log.txt";
        //获取FileUtiles对象
        cocos2d::CCFileUtils *fileUtile=cocos2d::CCFileUtils::sharedFileUtils();
        //进入Documents目录下
        std::string pathToSave=fileUtile->getWritablePath();
        //添加到log文件夹
        pathToSave +="Dingfenglog";
        CCLOG("pathToSave=%s",pathToSave.c_str());
       
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
        DIR *pDir = NULL;
        //打开该路径
        pDir = opendir (pathToSave.c_str());
        if (! pDir)
        {
            //创建该路径
            mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        }
#else
        if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
        {
            CreateDirectoryA(pathToSave.c_str(), 0);
        }
#endif
         mlogPath =pathToSave+mlogPath;
        fp = fopen(mlogPath.c_str(), "w");
        if (!fp) {
            CCLOG("file error");
        }
    }
   // else
    {
        
        char szBuf[MAX_LOGLEN];
        va_list ap;
        va_start(ap,pszFormat);
        vsprintf(szBuf, pszFormat, ap);
        va_end(ap);
        fprintf(fp, "%s\n",szBuf);
        fflush(fp);
        
        
        //此处将printf 替换为CC_LOG
        CCLOG("%s",szBuf);
    }
#endif
}
