#ifndef __fish__InitRechareLayer_H_
#define  __fish__InitRechareLayer_H_


#include "headerLibrary.h"

#define kInitRechargeNotifiction ("kInitRechargeNotifiction")

#define CCB_CLASS_NAME InitRechargeLayer

class CCB_CLASS_NAME : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener
{
public:
	CCB_CLASS_NAME();
	virtual ~ CCB_CLASS_NAME();
    
	static CCScene *scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCB_CLASS_NAME, create);
    
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
    
	void onExit();
	
    
    //退出
    void onRechargeClicked(CCObject *pSender);
    
    //填充ui元素
    void fillUIElements();
    
    void fillUIElementsHelper( CCLabelTTF *target, CCLabelTTF *tmpl, const char *text );
    
private:
    
private:
    
    CCLabelTTF * cb_lblUnlockKey;
    
    CCLabelTTF * cb_lblCoinVal;
    CCLabelTTF * cb_lblPearlVal;
    CCLabelTTF * cb_lblExpVal;
    CCLabelTTF * cb_lblUnlockVal;
    CCLabelTTF * cb_lblTip;
    
    CCMenu * cb_menuRecharge;
    bool isTouchInMenu;
};

class XConn(CCB_CLASS_NAME, BuilderLoad) : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(XConn(CCB_CLASS_NAME, BuilderLoad), loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCB_CLASS_NAME);
};


#endif /* defined( XConn(__fish__, CCB_CLASS_NAME) ) */
