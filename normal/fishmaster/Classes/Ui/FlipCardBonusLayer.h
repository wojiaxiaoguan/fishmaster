//
//  FlipCardBonusLayer.h
//  fish
//
//  
//
//

#ifndef __fish__FlipCardBonusLayer__
#define __fish__FlipCardBonusLayer__
#include "headerLibrary.h"
#include "FlipCardBonus.h"


#define FONT_COLOR     ccc3(63.0f,47.0f,36.0f)

#define kFlipCardBonusNotification ("kFlipCardBonusNotification")

class FlipCardBonusLayer : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener
{
public:
	FlipCardBonusLayer();
	virtual ~FlipCardBonusLayer();
    
	static CCScene *scene(BonusTrigger trigger = KillSeaHorse);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FlipCardBonusLayer, create);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void update(float dt);
    
    void playSound(CCNode* sender, void* data);
    
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
private:
	void onEnter();
    
	void onExit();
	
    //翻牌
    void flip( CCMenuItemImage *btn);
    
	// 快速开始菜单
	void onCardClicked(CCObject *pSender);
    
    void onStartClicked(CCObject *pSender);
    
    //填充ui元素
    void fillUIElements();
    
    void doFlipHelper(CCMenuItemImage *btn);
    
    void removeSelf();
    
    void runHighlightAnimation( const int num, const CCPoint &pos);
    
private:
    FlipCardBonusManager *manager;
    
private:
    CCMenu *cb_menuCards;
    CCMenu *cb_menuStart;
    
    CCLayer *cb_layerCardsContainer;
    CCLayer *cb_layerBegin;
    CCLayer *cb_layerEnd;
    CCLayer *cb_layerContainer;
    CCLayer *cb_layerCards;

    CCLabelTTF *cb_lblCurScore;
    CCLabelTTF *cb_lblScoreTip;
    CCLabelTTF *cb_lblEndScoreFG;
    CCLabelTTF *cb_lblEndScoreBG;
    
    CCSprite  *spClickPoint;

    
    bool isTouchInCardMenu;
    bool isTouchInStartMenu;
    bool isBeginLayerShow;  //当beginLayer存在时,不对card layer进行判定,以阻止其可以被点中

};

class FlipCardBonusLayerBuilderLoad : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FlipCardBonusLayerBuilderLoad, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FlipCardBonusLayer);
};



#endif /* defined(__fish__FlipCardBonusLayer__) */
