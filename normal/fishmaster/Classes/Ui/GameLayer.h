//
//  GameLayer.h

//
//  
//
//

#ifndef FishingJoyStep1_GameLayer_h
#define FishingJoyStep1_GameLayer_h

#include "headerLibrary.h"
#include "Cannon.h"
#include "RollNum.h"
#include "Mine.h"
#include "Fish.h"
#include "Bullet.h"
#include "Helper.h"
#include "GameData.h"
#include "GameAwardLayer.h"


#define SP_TAG_CANNON 7
#define MAX_FISH_COUNT 50
//#define WaterWaveFrameCount 31
#ifdef PUBLISH_GOVERNMENT
#define LOSE_COUNT 0
#define HIT_PERCENTAGE (0.86f)
#elif defined  PUBLISH_OFFLINE
#define LOSE_COUNT 0
#define HIT_PERCENTAGE (0.86f)
#endif
  
class GameLayer : public cocos2d::CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener,
public FishInterface
{
public:
    //????????½æ?°ä????½å??ä¹?ä¸ºè?? ??????[HG1]
    GameLayer();
    //å¤??????ºç±»???????????½æ?°å??è¯¥ä¸º?????½æ?? ??????[HG2]
    virtual ~GameLayer();
    
    static CCScene *scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameLayer, create);
    
    //å®???°è§¦??¸æ??ä¸?äº?ä»¶ï??ä¸»è??å¤?????????°è½¬???
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void keyBackClicked();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pBullets, Bullets);//å­???¨å??æ®µå?¹è±¡??????
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pFishes, Fishes);
    CC_SYNTHESIZE_RETAIN(RollNumGroup *, m_pRollNumGroup, RollNumGroup);//å®?ä¹????å¸?
    
    //??¨æ?¥è½¬è½?net?????¸å?³è??æº????å®¹å??ï¼?ä»?ä»???????å¯¹å?????è½½ä??å¼?èµ?æº???¾ç??
//    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNodeNet1, BatchNodeNet1);
//    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNodeNet2, BatchNodeNet2);
//    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNodeNet3, BatchNodeNet3);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNodeFish, BatchNodeFish);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNodePao, BatchNodePao);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNodeCoin, BatchNodeCoin);
    
    
    void startRollLottery();
    void startLaser(bool isForce);
    void startPower(bool isForce);
    void dropGemstone(DiamondType type);
    void playParticleFireworks(float ct);
    void startFishGenerator(bool start);
    void removeFish(Fish *pf);
    void showMenu(bool show);
    
    void setFreezeing( bool b ) {
        _isFreezeing = b;
    }
    bool isFreezeing() {
        return _isFreezeing;
    }
    
    void updateScoreUI(int addScore);
    
    void setMenuEnable(bool pEnable);
    
    // ?????ºæ¸¸??? ä¿???¹æ??public
    void exitGameLayerSel(CCObject *pSender);
    
    //   shoptip
    void cancleGameLayerTip(CCObject *pSender);
    void enterGameLayerTip(CCObject *pSender);
    
    void syncScoreUI();
    void syncHideUI();
    void updateMinePower(int addPower);
    
    void fishdeadCallBack(cocos2d::CCPoint deadPoint);
    void fishdeadEndCallBack(CCNode* node);
    void light1EndCallBack(CCNode* node);
    void dellightCallBack(CCNode* node);
    void delboxCallBack(CCNode* node);
    
    void onBoughtResultNotify();
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
   
    //??¹å?»é?????button
    void onInitRechargeNotify();
    
    //é¦?æ¬¡å????¼ç???????????

    
    //ç¿»ç¿»ä¹?ç»????
    void onFlipCardBonusNotify(CCObject *);
    
    
private:
	void onEnter();
    void onEnterTransitionDidFinish();
	void onExit();
    
    void loadBcakground();
    
    //ç¦?æ­¢å?????
    GameLayer(const GameLayer &other);
    

private:
    
    void lotteryEndSound();
    void endRollLottery(CCNode* aObj,void* index);
    
    void updateUIExp();
   
    
    void updateLaserOrPower();
    bool isBgSwithing;
    
    void updateBonus();
    void updateGemstoneCD();
    void updateCannonCD();
    
    
    void enableGameSet();
    void hideMenu();
    
    //è½½å?¥é??è¦???¨å?°ç??plist???ä»?
    void initFrames();
    //???è½½æ¸¸????????? ??? ?????°å?ºåº§
    void initBackground();
    //???è½½æ??é±¼å¤§???
    void initCannon();
    //???è½½é±¼??¿å??å­?å¼¹è??æº?
    void initFishes();
    //??´æ?°æ¸¸?????´ä????»è??
    void initUnlockItems();
    void updateGame(cocos2d::CCTime dt);
    //é±¼å?¿å??å»ºé?»è??
    void updateFish(cocos2d::CCTime dt);
    //å¾?æ¸¸æ??ä¸»ç?????ä¸?æ·»å??é±¼å??
    void addFish();
    
//    void hideWaterWave();
//    void showWaterWave();
    
    void checkMine();
    void checkBullet();
    
    //???çº§å¤§????????????
    void addCannonSize(CCObject *pSender);
    //???çº§å¤§?????????
    void reduceCannonSize(CCObject *pSender);
    
    void setGameLayerSel(CCObject *pSender);
    void soundGameLayerSel(CCObject *pSender);
    // SIMPLE
    void helpGameLayerSel(CCObject *pSender);
    void storeGameLayerSel(CCObject *pSender);
    
   
    //   buy power
    void buyPower(CCObject *pSender);
    // SIMPLE
//    void leftCallback(CCObject *pSender);
//    void rightCallback(CCObject *pSender);
//    void taskCallback(CCObject* pSender);
//    void reliefCallback(CCObject* pSender);
    
    void showAward(GameAwardType aType);
    void catchFish(Fish *pFish, FatherBullet *pBullet);
    
//    void onInitRechargeClicked(CCObject *pSender);
    
    //å¡????
    void fillUIElements();
    
    void mineSel(CCObject *pSender);
    void helpExitSel(CCObject *pSender);
    
    void changeBg();
    void endSwitchBg();
    void switchBg();
    void prepareSwitchBg();
    void generateBombFish();
    
    //è´?ä¹°è??çº§æ????¨æ?????
    void buySuperPower();
    
    //è´?ä¹°è??çº§æ?????ä¸??????????
    void buyMaxPower();
    //è´?ä¹?Vip
    void buyVipCard();
    //è´?ä¹°å??çº§å¤§ç¤¼å??
    void buyUpGradGift();
    //å»¶æ?¶æ?¾ç¤º???çº§å¤§ç¤¼å????¢æ??
    void showUpGradGift();
    void showGoodSixGift();
    void buyGoodSixGift();
   void buyDragonGift();
    void buyMermaidGift();
    void buyXihaGift();
    //è®¾ç½®ä»»å?¡é?¢æ??
    void setTaskInfoPanle(int index);
    
    
    
    void setToken(int pToken) { m_iToken = pToken; };
    void setTaskIndex(int pType) { m_TaskIndex = pType; };
    
    void showXihaGift();
    
    // ??´æ?°å?»æ??æµ·æ???????¶é??
    // SIMPLE
//    void updateSeaMonsterTime(float delta);
    // ??°é?¾æ¨¡å¼?ä¸?æµ·æ??ä¸????æ»¡è?? ???æ¯?10ç§???¢å??100HP
//    void addSeaMonsterBlood(float delta);
    // ??°é?¾æ¨¡å¼?ä¸? 45 ??? 60 ç§???·æ?°ä??ä¸???¸å¼¹
//    void addSeaMonsterBomb(float delta);
//    void onGetDamage();
public:
    void buyTaskSuccess(int m_id);
    void buyTask(ProductType m_id);
    void startEle();
    void addEle();
    // æ£???¥å????¾ä»»???
//    void checkTask();
//    void checkAddTask(float delta);
//    void checkAddSpecifiedTask(int difficulty); // ?????????å®???¾åº¦ä»»å??
//    void taskCountDown(float delta);
private:
    CCLayer* ly_fish; // fish layer
//    CCLayer* ly_bg; // background layer
    CCLayer* ly_switch; //switch layer
    CCLayer* ly_wheel;
    // SIMPLE
    CCLayerColor* ly_guide;
    
//    CCSprite* sp_water; //background water
    CCSprite* sp_switch; //switch water wave
    CCSprite* sp_bg; //background
    CCSprite* sp_bg1; //background
    
    CCSprite* sp_power;
    CCSprite* sp_power_active;
    
    CCSprite* sp_cannon;
    CCSprite* sp_scoreboard;
    // top cannon fire
    CCSprite* sp_topCannonBg;
    CCSprite* sp_cannonTop;
    
    CCSprite* cur_bg;
    CCSprite* bak_bg;
    
    CCSprite* sp_exp_double;
    CCSprite* sp_power_count;
    CCSprite* sp_fire2;
    CCSprite* sp_user_exp;
    CCSprite* sp_user_exp_active;
    CCSprite* sp_wheel;
    CCSprite* sp_hidebullet;
    CCSprite* sp_laserbullet;
    
    
    CCLabelBMFont* ttf_cannon_score;
    CCSprite* ttf_player_level;
    CCLabelBMFont* ttf_hidebullect_cnt;
    CCLabelTTF* ttf_laserbullet_cnt;
    CCLabelBMFont* ttf_bonus_time;
    
    CCSprite*   sp_coinshort;
    CCMenu* cb_menu;
    
    CCMenuItemImage* bn_mine;
    CCMenuItemImage* bn_mine_ele;
    CCMenuItemImage* bn_set;
    CCMenuItemImage* bn_exit;
    CCMenuItemImage* bn_sound;
    CCMenuItemImage* bn_power;
    // SIMPLE
    CCMenuItemImage* bn_help;
    CCMenuItemImage* m_pBnAdd;//???çº§ç????°æ?????
    CCMenuItemImage* m_pBnReduce;//???çº§ç?????
//    CCMenuItemImage* cb_btnInitRecharge;  //é¦?æ¬¡å????¼æ??ç­?
    
//    char* m_HelpFrame[4];
//    CCSprite* m_pHelp;
//    int m_iHelpIndex;
//    CCSprite* m_SeaMonsterHelp;
//    CCMenuItemImage* m_pMiiHelpLeft;
//    CCMenuItemImage* m_pMiiHelpRight;
    //add by andy 2015-03-23
    int hit_count;
    int task_index;
    bool isUnLockMaxConnon;
    bool isTaskVisable;
    
    //add end by andy 2015-03-23
    Mine* m_pMine;
    
    
    
    
    GoldControl *sp_gold;
    
    bool isMineSelected;
    bool isShot;
    
    int cd_gemstone;
    int cd_cannon;
    int cur_background_index;
    
    char* bgFileNamePrefix;
    
//    CCArray* water_wave_arr;
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, fish_batch_arr, FishBatch);
    
    //å°?????????????å£°æ??ä¸?private
    CC_SYNTHESIZE_RETAIN(Cannon *, m_pCannon, Cannon);
    // top cannon fire
//    CC_SYNTHESIZE_RETAIN(Cannon *, m_pCannonTop, CannonTop);
    
    //??????å·²ç????§è??è¿?é¦???????ä»»å??
    bool isInitRecharged;
    
    bool _isFreezeing;  //??¨å?ºç?°ç¿»ç¿»ä??ç­???¶ä??è¡?ä¸ºæ??,??»ç????????è®¡æ?¶é?????
    
    bool isFishGeneratorStarted;
    bool isLightAnimation;
    
    int m_iToken;
    int m_TaskIndex;
    
    // ä»»å?¡ç?¸å??
    // SIMPLE
//    CCLayer* ly_task;
//    CCSprite* m_sTaskIcon;
//    CCMenuItemImage* m_pMiiTask;
//    CCLabelBMFont* bmf_taskprogress;
//    CCLabelBMFont* bmf_tasktime;
    
    // ???æµ????
    // SIMPLE
//    CCLayer* ly_relief;
//    CCLabelBMFont* bmf_reliefCoin;
    
    // æµ·æ??æ¨¡å??
    // SIMPLE
//    CCLayer* ly_seamonster;
//    CCSprite* sp_seamonster_blood;
//    CCSprite* sp_seamonster_time_bg;
//    CCLabelTTF* ttf_seamonster_time;
//    CCSprite* sp_seamonster_result;
    
    // æ¸¸æ??æ¨¡å??
    GameType m_gameType;
    int lost_count;
    int meiren_count;
    
    //
//    int m_bShowFastBuy;
    
};

class GameLayerBuilderLoad : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameLayerBuilderLoad, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameLayer);
};

#endif
