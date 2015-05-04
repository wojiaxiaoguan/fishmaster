
#define CCB_CLASS_NAME TemplateClassName

#ifndef __fish__CCB_CLASS_NAME__
#define __fish__CCB_CLASS_NAME__

#include "headerLibrary.h"



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
    void onExitClicked(CCObject *pSender);
    
    //填充ui元素
    void fillUIElements();
    
private:
    
private:
  //  CCMenu *cb_menuChests;
    
};

class XConn(CCB_CLASS_NAME, BuilderLoad) : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(XConn(CCB_CLASS_NAME, BuilderLoad), loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCB_CLASS_NAME);
};


#endif /* defined(__fish__CCB_CLASS_NAME__) */
