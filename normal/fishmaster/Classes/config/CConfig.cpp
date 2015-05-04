//
//  CConfig.cpp
//  fish
//
//  
//
//

#include "CConfig.h"

const char* CConfig::DELIMIT_LF         = "\n";
const char* CConfig::DELIMIT_CR         = "\r";
const char* CConfig::DELIMIT_COMMA      = ",";
const char* CConfig::DELIMIT_VERTICAL   = "|";
const char* CConfig::DELIMIT_HORIZONTAL = "-";
const char* CConfig::DELIMIT_COLON      = ":";

CConfig* CConfig::s_pSharedConfig = NULL;

CConfig::CConfig()
{
    
}

CConfig::~CConfig()
{
    for (map<unsigned int, TaskCfg*>::iterator it = m_mTasksCfg.begin(); it != m_mTasksCfg.end(); it++)
    {
        CC_SAFE_DELETE(it->second);
    }
    m_mTasksCfg.clear();
}

CConfig* CConfig::sharedConfig()
{
    if (s_pSharedConfig == NULL)
    {
        s_pSharedConfig = new CConfig();
    }
    return s_pSharedConfig;
}

vector<string>* CConfig::splitString(string strSrc, string delimit)
{
    string::size_type pos;
    vector<string>* result = new vector<string>();
    
    strSrc += delimit; //扩展字符串以方便操作
    
    int size = strSrc.size();
    
    for(int i = 0; i < size; i++)
    {
        pos = strSrc.find(delimit, i);
        if (pos < size)
        {
            string s = strSrc.substr(i, pos - i);
            result->push_back(s);
            i = pos + delimit.size() - 1;
        }
    }
    return result;
}

void CConfig::loadTask(const char *path)
{
    do
    {
    	if (m_mTasksCfg.size() > 0)
    	{
			return;
		}
        unsigned char * pData = NULL;
        unsigned long size    = 0;
        pData = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", &size);
		if (!pData)
		{
			break;
		}
        
		vector<string>* lines = splitString((const char*)pData, DELIMIT_LF);
        
		delete []pData;
		pData = NULL;
        
		int lineCount = lines->size();
        int len = 0;
		vector<string>* cfgs = NULL;
        for (int i = 0; i < lineCount; i++)
        {
        	if (cfgs)
        	{
        		cfgs->clear();
				delete cfgs;
				cfgs = NULL;
        	}
            
            cfgs = splitString(lines->at(i), DELIMIT_COMMA);
            len = cfgs->size();
            if (len < 8)
            {
                continue;
            }
            
            TaskCfg* pTask = new TaskCfg();
            pTask->id = atoi(cfgs->at(0).c_str());
            pTask->icon = cfgs->at(1);
            pTask->type = (TaskType)atoi(cfgs->at(2).c_str());
            vector<string>* requires = splitString(cfgs->at(3), DELIMIT_VERTICAL);
            for (int j = 0; j < requires->size(); j++)
            {
                vector<string>* require = splitString(requires->at(j), DELIMIT_COLON);
                if (require->size() >= 2)
                {
                    TaskRequire* pReq = new TaskRequire();
                    pReq->id = atoi(require->at(0).c_str());
                    pReq->quantity = atoi(require->at(1).c_str());
                    pTask->require.push_back(pReq);
                }
            }
            pTask->level = atoi(cfgs->at(4).c_str());
            pTask->time = atoi(cfgs->at(5).c_str());
            pTask->difficulty = atoi(cfgs->at(6).c_str());
            vector<string>* rewards = splitString(cfgs->at(7), DELIMIT_VERTICAL);
            for (int j = 0; j < rewards->size(); j++)
            {
                vector<string>* reward = splitString(rewards->at(j), DELIMIT_COLON);
                if (reward->size() >= 2)
                {
                    TaskReward* pRew = new TaskReward();
                    pRew->type = (TaskRewardType)atoi(reward->at(0).c_str());
                    pRew->quantity = atof(reward->at(1).c_str());
                    pTask->reward.push_back(pRew);
                }
            }
            pTask->description = cfgs->at(8);
            m_mTasksCfg.insert(pair<unsigned int, TaskCfg*>(pTask->id, pTask));
        }
		if (cfgs)
		{
			delete cfgs;
			cfgs = NULL;
		}
		if (lines)
		{
			delete lines;
			lines = NULL;
		}
    } while(0);
}

int CConfig::getRandomTask(int pDifficulty, int pMaxLevel)
{
    vector<int> pTaskId;
    map<unsigned int, TaskCfg*>::iterator it = m_mTasksCfg.begin();
    for (; it!= m_mTasksCfg.end(); ++it)
    {
        if (it->second->difficulty == pDifficulty && it->second->level <= pMaxLevel)
        {
            pTaskId.push_back(it->second->id);
        }
    }
    if (pTaskId.size() > 0)
    {
        srand(time(NULL));
        return pTaskId.at(rand() % pTaskId.size());
    }
    return  0;
}

const TaskCfg* CConfig::getTask(unsigned int id) const
{
    map<unsigned int, TaskCfg*>::const_iterator it = m_mTasksCfg.find(id);
    if (it != m_mTasksCfg.end())
    {
        return it->second;
    }
	return NULL;
}

unsigned long CConfig::secondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec + now.tv_usec / 1000000);
}