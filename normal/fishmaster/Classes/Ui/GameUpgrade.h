//
//  GameUpgrade.h
//  fish
//
//  
//
//

#ifndef __fish__GameUpgrade__
#define __fish__GameUpgrade__

#include <iostream>

#include "headerLibrary.h"


#define GameTTFBonusNumberTag   12
//#define GameTTFNewLevelTag      11
#define GameTTFUnlockItemTag    10
#define GameTTFNextUnlockTag    13


class GameUpgradeLayer : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener
{
public:
	GameUpgradeLayer();
	virtual ~GameUpgradeLayer();
    
	static CCScene *scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameUpgradeLayer, create);
    
    void playParticleFireworks(float ct);
    
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
private:
	
    //填充ui元素
    void fillUIElements();
    
    void exit();
    
private:
    CCSprite  *sp_bg;
};

class GameUpgradeLayerBuilderLoad : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameUpgradeLayerBuilderLoad, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameUpgradeLayer);
};


#endif /* defined(__fish__GameUpgrade__) */
