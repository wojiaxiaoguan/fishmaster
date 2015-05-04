#ifndef __IntroLayer_H__
#define __IntroLayer_H__

#include "headerLibrary.h"
#include "RippleGrid3D.h"
#include "Fish.h"


/**
* 登陆UI
*/
class IntroLayer : public CCLayer,
	public CCBMemberVariableAssigner,
	public CCBSelectorResolver, 
	public CCNodeLoaderListener,
    public FishInterface
{
public:
	IntroLayer();
	virtual ~IntroLayer();
    
	static CCScene *scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(IntroLayer, create);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void keyBackClicked();
    
    virtual void update(float dt);
    
    void setButtonStatus( bool b);
    void removeFish(Fish *pf);
    
    
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);

private:
	void onEnter();

	void onExit();
	
    void onEnterTransitionDidFinish();
	// 快速开始菜单
	void onFastStart(CCObject *pSender);
    // 反馈菜单
    void onFeedback(CCObject *pSender);
   // void onSound(CCObject *pSender);
//	void onSceneSelectionClicked(CCObject *pSender);
//    void onInfo_(CCObject *pSender);
//    void onAboutExit(CCObject *pSender);
//    void onSeaMonsterCallback(CCObject* pSender);
//    void onSeaMonsterCloseCallback(CCObject* pSender);
//    void onSeaMonsterStartCallback(CCObject* pSender);
//    void updateSeaMonsterTimes();

    void updateFish();
    
    void replaceScene();
    
    void wheelIdleAnimation();
	//播放随机的旗袍
    void playSmallQipao();
    


private:
    
    bool isTouchInMenu;
    bool isexitInMenu;
    bool isTouchInWaveRipple;
    
    CCMenu *cb_menuActions;
    CCMenuItem* menuFastEnter_;
//    CCMenuItemImage* menuSound_;
//    CCMenuItem* menuInfo_;
//    CCMenuItem* menuScene_;
    
    CCSprite* sp_bg;
    CCSprite* sp_loading;
    
    CCLayer *m_pWaveRipple;
//    CCLayer *ly_about;
    CCSprite *sp_title;
    
    
//    CCSprite *cb_spWheel;
    
//    CCLayer* ly_seamonster;
//    CCLabelBMFont*  bmf_normalTimes;
//    CCLabelBMFont*  bmf_difficultyTimes;
    
//    CCMenuItemImage* m_pMiiSeaMonsterNormal;
//    CCMenuItemImage* m_pMiiSeaMonsterDiffculty;
//    float delaytime;
//    int exitcount;
//    bool exitStatus;
};

class IntroLayerBuilderLoad : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(IntroLayerBuilderLoad, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(IntroLayer);
};

#endif
