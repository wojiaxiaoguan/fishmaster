//
//  TaskDetailLayer.cpp
//  fish
//
//
//

#include "TaskDetailLayer.h"
#include "../config/CConfig.h"
#include "../Data/GameData.h"
#include "GameLayer.h"

TaskDetailLayer::TaskDetailLayer()
{
    m_iTaskId = 0;
    
    m_sTaskDetail = NULL;
    m_sDescription = NULL;
    
    m_lBmfTimeLimit = NULL;
    m_lBmfTimesLimit = NULL;
    m_lBmfRewardCoin = NULL;
    m_lBmfRewardExp = NULL;
    m_lBmfRewardDiamond = NULL;
    m_lBmfRewardBlackPearl = NULL;
    
    m_pMiiGiveUp = NULL;
    m_pMiiReset = NULL;
    
    m_sDialogBg = NULL;
    m_sDialogContent = NULL;
    m_bmfCost = NULL;
    m_pMiiDialogOk = NULL;
}

TaskDetailLayer::~TaskDetailLayer()
{
    CC_SAFE_RELEASE(m_sDescription);
    
    CC_SAFE_RELEASE(m_sTaskDetail);
    CC_SAFE_RELEASE(m_lBmfTimeLimit);
    CC_SAFE_RELEASE(m_lBmfTimesLimit);
    CC_SAFE_RELEASE(m_lBmfRewardCoin);
    CC_SAFE_RELEASE(m_lBmfRewardExp);
    CC_SAFE_RELEASE(m_lBmfRewardDiamond);
    CC_SAFE_RELEASE(m_lBmfRewardBlackPearl);
    
    CC_SAFE_RELEASE(m_pMiiGiveUp);
    CC_SAFE_RELEASE(m_pMiiReset);
    
    CC_SAFE_RELEASE(m_sDialogBg);
    CC_SAFE_RELEASE(m_sDialogContent);
    CC_SAFE_RELEASE(m_bmfCost);
    CC_SAFE_RELEASE(m_pMiiDialogOk);
}

TaskDetailLayer* TaskDetailLayer::layer(cocos2d::CCNode *pParent, unsigned int pTaskId)
{
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("TaskDetailLayer", TaskDetailLayerLoader::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	TaskDetailLayer* node = (TaskDetailLayer*)ccbReader->readNodeGraphFromFile("ios/ccbResources/TaskDetailLayer.ccbi", pParent);
    ccbReader->release();
	if (node)
    {
        pParent->addChild(node);
        node->updateUi(pTaskId);
        node->m_pParent = pParent;
    }
	return node;
}

void TaskDetailLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

bool TaskDetailLayer::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sTaskDetail", CCSprite *, this->m_sTaskDetail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sDescription", CCSprite *, this->m_sDescription);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lBmfTimeLimit", CCLabelBMFont *, this->m_lBmfTimeLimit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lBmfTimesLimit", CCLabelBMFont *, this->m_lBmfTimesLimit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lBmfRewardCoin", CCLabelBMFont *, this->m_lBmfRewardCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lBmfRewardExp", CCLabelBMFont *, this->m_lBmfRewardExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lBmfRewardDiamond", CCLabelBMFont *, this->m_lBmfRewardDiamond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lBmfRewardBlackPearl", CCLabelBMFont *, this->m_lBmfRewardBlackPearl);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiGiveUp", CCMenuItemImage *, this->m_pMiiGiveUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiReset", CCMenuItemImage *, this->m_pMiiReset);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sDialogBg", CCSprite *, this->m_sDialogBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sDialogContent", CCSprite *, this->m_sDialogContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_bmfCost", CCLabelBMFont *, this->m_bmfCost);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiDialogOk", CCMenuItemImage *, this->m_pMiiDialogOk);
    return true;
}

SEL_MenuHandler TaskDetailLayer::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "giveUpCallback", TaskDetailLayer::giveUpCallback);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "resetCallback", TaskDetailLayer::resetCallback);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "closeCallback", TaskDetailLayer::closeCallback);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "dialogCloseCallback", TaskDetailLayer::dialogCloseCallback);
    return NULL;
}

SEL_CCControlHandler TaskDetailLayer::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void TaskDetailLayer::updateUi(unsigned int pTaskId)
{
    char achTemp[32] = {0};
    memset(achTemp, 0, sizeof(achTemp));
    // times
    GameTimesRecord* pRecord = GameData::getSharedGameData()->getGameRecordInfo(GameRecordType_Task, GameData::getSharedGameData()->genDayStamp());
    int pTimes = 3;
    if (pRecord)
    {
        pTimes = 3 - pRecord->times;
    }
    pTimes = pTimes > 0 ? pTimes : 0;
    sprintf(achTemp, "%d", pTimes);
    m_lBmfTimesLimit->setString(achTemp);
    // task detail
    m_iTaskId = pTaskId;
    const TaskCfg* pTaskCfg = CConfig::sharedConfig()->getTask(m_iTaskId);
    if (pTaskCfg)
    {
        // description
        sprintf(achTemp, "%s.png", pTaskCfg->description.c_str());
        m_sDescription->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(achTemp));
        // time limit
        sprintf(achTemp, "%d分钟", pTaskCfg->time / 60);
        m_lBmfTimeLimit->setString(achTemp);
        // reward
        m_lBmfRewardExp->setString("0");
        m_lBmfRewardCoin->setString("0");
        m_lBmfRewardDiamond->setString("0");
        m_lBmfRewardBlackPearl->setString("0");
        for (int i = 0; i < pTaskCfg->reward.size(); i++)
        {
            if (pTaskCfg->reward.at(i)->type == TASK_REWARD_COIN)
            {
                sprintf(achTemp, "%d", (int)pTaskCfg->reward.at(i)->quantity);
                m_lBmfRewardCoin->setString(achTemp);
            }
            else if (pTaskCfg->reward.at(i)->type == TASK_REWARD_EXP)
            {
                sprintf(achTemp, "%d", (int)pTaskCfg->reward.at(i)->quantity);
                m_lBmfRewardExp->setString(achTemp);
            }
            else if (pTaskCfg->reward.at(i)->type == TASK_REWARD_EXPPER)
            {
                sprintf(achTemp, "%d", (int)(GameData::getSharedGameData()->nextLevel()->m_expForUpgrade * pTaskCfg->reward.at(i)->quantity / 100));
                m_lBmfRewardExp->setString(achTemp);
            }
            else if (pTaskCfg->reward.at(i)->type == TASK_REWARD_DIAMOND)
            {
                sprintf(achTemp, "%d", (int)pTaskCfg->reward.at(i)->quantity);
                m_lBmfRewardDiamond->setString(achTemp);
            }
            else if (pTaskCfg->reward.at(i)->type == TASK_REWARD_BLACKPEARL)
            {
                sprintf(achTemp, "%d", (int)pTaskCfg->reward.at(i)->quantity);
                m_lBmfRewardBlackPearl->setString(achTemp);
            }
        }
    }
}

void TaskDetailLayer::giveUpCallback(cocos2d::CCObject *pSender)
{
    m_sTaskDetail->setVisible(false);
    m_pMiiGiveUp->setEnabled(false);
    m_pMiiReset->setEnabled(false);
    m_sDialogContent->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("txt5.png"));
    m_pMiiDialogOk->setTarget(this, menu_selector(TaskDetailLayer::dialogGiveUpOkCallback));
    m_bmfCost->setVisible(false);
    m_sDialogBg->setVisible(true);
}

void TaskDetailLayer::resetCallback(cocos2d::CCObject *pSender)
{
    m_sTaskDetail->setVisible(false);
    m_pMiiGiveUp->setEnabled(false);
    m_pMiiReset->setEnabled(false);
    m_sDialogContent->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("txt4.png"));
    m_pMiiDialogOk->setTarget(this, menu_selector(TaskDetailLayer::dialogResetOkCallback));
    char achTemp[32] = {0};
    memset(achTemp, 0, sizeof(achTemp));
    sprintf(achTemp, "%d", 50 * GameData::getSharedGameData()->currentLevel());
    m_bmfCost->setString(achTemp);
    m_bmfCost->setVisible(true);
    m_sDialogBg->setVisible(true);
}

void TaskDetailLayer::closeCallback(cocos2d::CCObject *pSender)
{
    if (dynamic_cast<GameLayer*>(m_pParent))
    {
        ((GameLayer*)m_pParent)->setMenuEnable(true);
    }
    removeFromParentAndCleanup(true);
}

void TaskDetailLayer::dialogGiveUpOkCallback(cocos2d::CCObject *pSender)
{
    GameTask* pGameTask = GameData::getSharedGameData()->getGameTaskIn();
    if (pGameTask)
    {
        GameData::getSharedGameData()->saveGameTask(pGameTask->m_id, 0, 0, pGameTask->m_time);
    }
    if (dynamic_cast<GameLayer*>(getParent()))
    {
        // SIMPLE
//        ((GameLayer*)getParent())->checkTask();
    }
    closeCallback(NULL);
}

void TaskDetailLayer::dialogResetOkCallback(cocos2d::CCObject *pSender)
{
    GameTask* pGameTask = GameData::getSharedGameData()->getGameTaskIn();
    if (pGameTask)
    {
        if (GameData::getSharedGameData()->score() < 50 * GameData::getSharedGameData()->currentLevel())
        {
            // 金币不足
            return;
        }
        GameData::getSharedGameData()->saveGameTask(pGameTask->m_id, 0, 0, pGameTask->m_time);
        if (dynamic_cast<GameLayer*>(getParent()))
        {
            // 扣减金币
            ((GameLayer*)getParent())->updateScoreUI(- 50 * GameData::getSharedGameData()->currentLevel());
            // 随机相同难度的任务
            const TaskCfg* pTaskCfg = CConfig::sharedConfig()->getTask(pGameTask->m_id);
            // SIMPLE
//            ((GameLayer*)getParent())->checkAddSpecifiedTask(pTaskCfg->difficulty);
        }
    }
    closeCallback(NULL);
}

void TaskDetailLayer::dialogCloseCallback(cocos2d::CCObject *pSender)
{
    m_sTaskDetail->setVisible(true);
    m_pMiiGiveUp->setEnabled(true);
    m_pMiiReset->setEnabled(true);
    m_sDialogBg->setVisible(false);
}
