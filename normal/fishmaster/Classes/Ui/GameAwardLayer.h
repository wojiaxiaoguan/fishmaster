#ifndef __fish__GameAwardLayer__
#define __fish__GameAwardLayer__

#include "headerLibrary.h"
#include "FishUtils.h"

#define CCB_CLASS_NAME1 GameAwardLayer




#define DefaultLayerTag 1234

class CCB_CLASS_NAME1 : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener
{
public:
	CCB_CLASS_NAME1();
	virtual ~ CCB_CLASS_NAME1();
    
	static CCScene *scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCB_CLASS_NAME1, create);
    
    void setAwardType(GameAwardType aType);
    
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
	
    void exit();
    
    //填充ui元素
    void fillUIElements();
    
private:
    
private:
  //  CCMenu *cb_menuChests;
    CCSprite* sp_desp;
};

class XConn(CCB_CLASS_NAME1, BuilderLoad) : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(XConn(CCB_CLASS_NAME1, BuilderLoad), loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCB_CLASS_NAME1);
};


#endif /* defined(__fish__CCB_CLASS_NAME1__) */
