//
//  CConfig.h
//  fish
//
//  
//
//

#ifndef __fish__CConfig__
#define __fish__CConfig__

#include <vector>
#include <string>
#include <map>

#include "cocos2d.h"
#include "common.h"

using namespace std;
USING_NS_CC;

typedef enum
{
    TASK_TYPE_CATCHFISH = 1, // 捕捉到鱼
    TASK_TYPE_CATCHMULTIFISH, // 捕捉到目标倍数的鱼
    TASK_TYPE_GETCOIN,  // 获得多少金币
    TASK_TYPE_USESPECIALWEAPON, // 使用超能武器
    TASK_TYPE_GETGEMSTONE, // 获取到目标宝石
    TASK_TYPE_CATCHFISHCIRCLE, // 捕捉到目标渔圈
    TASK_TYPE_CATCHMULTIFISHDOWN, // 捕捉到12倍数一下的鱼
    TASK_TYPE_CATCHMULTIFISHUP, // 捕捉到15倍数以上的鱼
} TaskType;

typedef enum
{
    TASK_REWARD_EXPPER = 1,
    TASK_REWARD_EXP,
    TASK_REWARD_COIN,
    TASK_REWARD_BLACKPEARL,
    TASK_REWARD_DIAMOND,
} TaskRewardType;

typedef struct _TaskRequire
{
    unsigned int id;
    unsigned int quantity;
} TaskRequire;

typedef struct _TaskReward
{
    TaskRewardType type;
    float quantity;
}TaskReward;

typedef struct  _TaskCfg
{
    unsigned int            id; // 任务编号
    string                  icon; // 任务图标
    TaskType                type; // 任务类型
    vector<TaskRequire*>    require; // 任务需求
    unsigned int            level; // 任务需求等级
    unsigned int            time; // 任务限时
    unsigned int            difficulty; // 任务难度
    vector<TaskReward*>     reward; // 任务奖励
    string                  description; // 任务描述
} TaskCfg;

class CConfig
{
private:
    CConfig();
public:
    virtual ~CConfig();
    
    static CConfig* sharedConfig();

    vector<string>* splitString(string strSrc, string delimit);
    
    void loadTask(const char* path);
    int getTaskSize() { return m_mTasksCfg.size(); };
    int getRandomTask(int pDifficulty, int pMaxLevel);
    const TaskCfg* getTask(unsigned int id) const;
    
    static unsigned long secondNow();
public:
    static const char* DELIMIT_LF;
    static const char* DELIMIT_CR;
    static const char* DELIMIT_COMMA;
    static const char* DELIMIT_VERTICAL;
    static const char* DELIMIT_HORIZONTAL;
    static const char* DELIMIT_COLON;
    
private:
    static CConfig* s_pSharedConfig;
    
    map<unsigned int, TaskCfg*> m_mTasksCfg;
};

#endif /* defined(__fish__CConfig__) */
