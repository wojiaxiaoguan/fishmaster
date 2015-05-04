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
    //????????��?��????��??�?为�?? ??????[HG1]
    GameLayer();
    //�??????�类???????????��?��??该为?????��?? ??????[HG2]
    virtual ~GameLayer();
    
    static CCScene *scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameLayer, create);
    
    //�???�触??��??�?�?件�??主�??�?????????�转???
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void keyBackClicked();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pBullets, Bullets);//�???��??段�?�象??????
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pFishes, Fishes);
    CC_SYNTHESIZE_RETAIN(RollNumGroup *, m_pRollNumGroup, RollNumGroup);//�?�????�?
    
    //??��?�转�?net?????��?��??�????容�??�?�?�???????对�?????载�??�?�?�???��??
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
    
    // ?????�游??? �???��??public
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
    
   
    //??��?��?????button
    void onInitRechargeNotify();
    
    //�?次�????��???????????

    
    //翻翻�?�????
    void onFlipCardBonusNotify(CCObject *);
    
    
private:
	void onEnter();
    void onEnterTransitionDidFinish();
	void onExit();
    
    void loadBcakground();
    
    //�?止�?????
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
    
    //载�?��??�???��?��??plist???�?
    void initFrames();
    //???载游????????? ??? ?????��?�座
    void initBackground();
    //???载�??鱼大???
    void initCannon();
    //???载鱼??��??�?弹�??�?
    void initFishes();
    //??��?�游?????��????��??
    void initUnlockItems();
    void updateGame(cocos2d::CCTime dt);
    //鱼�?��??建�?��??
    void updateFish(cocos2d::CCTime dt);
    //�?游�??主�?????�?添�??鱼�??
    void addFish();
    
//    void hideWaterWave();
//    void showWaterWave();
    
    void checkMine();
    void checkBullet();
    
    //???级大????????????
    void addCannonSize(CCObject *pSender);
    //???级大?????????
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
    
    //�????
    void fillUIElements();
    
    void mineSel(CCObject *pSender);
    void helpExitSel(CCObject *pSender);
    
    void changeBg();
    void endSwitchBg();
    void switchBg();
    void prepareSwitchBg();
    void generateBombFish();
    
    //�?买�??级�????��?????
    void buySuperPower();
    
    //�?买�??级�?????�??????????
    void buyMaxPower();
    //�?�?Vip
    void buyVipCard();
    //�?买�??级大礼�??
    void buyUpGradGift();
    //延�?��?�示???级大礼�????��??
    void showUpGradGift();
    void showGoodSixGift();
    void buyGoodSixGift();
   void buyDragonGift();
    void buyMermaidGift();
    void buyXihaGift();
    //设置任�?��?��??
    void setTaskInfoPanle(int index);
    
    
    
    void setToken(int pToken) { m_iToken = pToken; };
    void setTaskIndex(int pType) { m_TaskIndex = pType; };
    
    void showXihaGift();
    
    // ??��?��?��??海�???????��??
    // SIMPLE
//    void updateSeaMonsterTime(float delta);
    // ??��?�模�?�?海�??�????满�?? ???�?10�???��??100HP
//    void addSeaMonsterBlood(float delta);
    // ??��?�模�?�? 45 ??? 60 �???��?��??�???�弹
//    void addSeaMonsterBomb(float delta);
//    void onGetDamage();
public:
    void buyTaskSuccess(int m_id);
    void buyTask(ProductType m_id);
    void startEle();
    void addEle();
    // �???��????�任???
//    void checkTask();
//    void checkAddTask(float delta);
//    void checkAddSpecifiedTask(int difficulty); // ?????????�???�度任�??
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
    CCMenuItemImage* m_pBnAdd;//???级�????��?????
    CCMenuItemImage* m_pBnReduce;//???级�?????
//    CCMenuItemImage* cb_btnInitRecharge;  //�?次�????��??�?
    
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
    
    //�?????????????声�??�?private
    CC_SYNTHESIZE_RETAIN(Cannon *, m_pCannon, Cannon);
    // top cannon fire
//    CC_SYNTHESIZE_RETAIN(Cannon *, m_pCannonTop, CannonTop);
    
    //??????已�????��??�?�???????任�??
    bool isInitRecharged;
    
    bool _isFreezeing;  //??��?��?�翻翻�??�???��??�?为�??,??��????????计�?��?????
    
    bool isFishGeneratorStarted;
    bool isLightAnimation;
    
    int m_iToken;
    int m_TaskIndex;
    
    // 任�?��?��??
    // SIMPLE
//    CCLayer* ly_task;
//    CCSprite* m_sTaskIcon;
//    CCMenuItemImage* m_pMiiTask;
//    CCLabelBMFont* bmf_taskprogress;
//    CCLabelBMFont* bmf_tasktime;
    
    // ???�????
    // SIMPLE
//    CCLayer* ly_relief;
//    CCLabelBMFont* bmf_reliefCoin;
    
    // 海�??模�??
    // SIMPLE
//    CCLayer* ly_seamonster;
//    CCSprite* sp_seamonster_blood;
//    CCSprite* sp_seamonster_time_bg;
//    CCLabelTTF* ttf_seamonster_time;
//    CCSprite* sp_seamonster_result;
    
    // 游�??模�??
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
