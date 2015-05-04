//
//  SeqLoginBonusLayer.h
//  fish
//
//
//

#ifndef __fish__SeqLoginBonusLayer__
#define __fish__SeqLoginBonusLayer__

#include "headerLibrary.h"
#include "SeqLoginBonus.h"

class SeqLoginBonusLayer : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener
{
public:
	SeqLoginBonusLayer();
	virtual ~SeqLoginBonusLayer();
    
	static CCScene *scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SeqLoginBonusLayer, create);
    
    
    void playSound(CCNode* sender, void* data);
    
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    
private:
	void onEnter();
    void onEnterTransitionDidFinish();
    
	void onExit();
	
    // 快速开始菜单
	void onChestClicked(CCObject *pSender);
    
    //退出
    void onExitClicked(CCObject *pSender);
    
    //填充ui元素
    void fillUIElements();
    
    void replaceScene(float ct);
    
    void removeSelf();
    
    //获得金币的气泡动画
    void coinAnimation( const int num, const CCPoint &pos);
    
    //获得宝石的气泡动画
    void diamondAnimation( DiamondType diamond, const CCPoint &pos);
    
    //以上两个函数的实际实现
    void animationHelper( CCSprite *sprite, const CCPoint &pos);

    //是否是Vip  是否需要金币奖励
    void  isVipReward();
    
private:
    SeqLoginBonusManager *manager;
    
private:
    CCMenu *cb_menuChests;
    CCSprite *cb_spCanOpenTip;
    
    //CCLabelTTF *cb_lblDayKeys[MAX_SEQ_LOGIN_DAYS];
    //CCLabelTTF *cb_lblDayValues[MAX_SEQ_LOGIN_DAYS];
    
    CCLabelTTF *cb_lblFooter;
    
    CCLayer    *cb_layerRoot;
    bool isTouchInMenu;
    
};

class SeqLoginBonusLayerBuilderLoad : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SeqLoginBonusLayerBuilderLoad, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SeqLoginBonusLayer);
};


#endif /* defined(__fish__SeqLoginBonusLayer__) */
