//
//  TaskDetailLayer.h
//  fish
//
//
//

#ifndef __fish__TaskDetailLayer__
#define __fish__TaskDetailLayer__

#include "headerLibrary.h"

class TaskDetailLayer : public CCLayer, public CCBMemberVariableAssigner, public CCBSelectorResolver, public CCNodeLoaderListener
{
public:
    TaskDetailLayer();
    virtual ~TaskDetailLayer();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TaskDetailLayer, create);
    
    static TaskDetailLayer* layer(CCNode* pParent, unsigned int pTaskId);
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
    void updateUi(unsigned int pTaskId);
    
    void giveUpCallback(cocos2d::CCObject* pSender);
    void resetCallback(cocos2d::CCObject* pSender);
    void closeCallback(cocos2d::CCObject* pSender);
    
    void dialogGiveUpOkCallback(cocos2d::CCObject* pSender);
    void dialogResetOkCallback(cocos2d::CCObject* pSender);
    void dialogCloseCallback(cocos2d::CCObject* pSender);
private:
    unsigned int m_iTaskId;
    
    CCSprite*       m_sTaskDetail;
    CCSprite*       m_sDescription;
    
    CCLabelBMFont*  m_lBmfTimeLimit;
    CCLabelBMFont*  m_lBmfTimesLimit;
    CCLabelBMFont*  m_lBmfRewardCoin;
    CCLabelBMFont*  m_lBmfRewardExp;
    CCLabelBMFont*  m_lBmfRewardDiamond;
    CCLabelBMFont*  m_lBmfRewardBlackPearl;
    
    CCMenuItemImage*    m_pMiiGiveUp;
    CCMenuItemImage*    m_pMiiReset;
    
    CCSprite*       m_sDialogBg;
    CCSprite*       m_sDialogContent;
    CCLabelBMFont*  m_bmfCost;
    
    CCMenuItemImage*    m_pMiiDialogOk;
};

class TaskDetailLayerLoader : public CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskDetailLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TaskDetailLayer);
};

#endif /* defined(__fish__TaskDetailLayer__) */
