//
//  GameLayer.cpp
//
// 
//
//

#include "GameLayer.h"
#include "Cannon.h"
#include "Fish.h"
#include "FishGroup.h"
#include "FishMatrix.h"
#include "GameData.h"
#include "Bullet.h"
#include "Sound.h"
#include "IntroLayer.h"
#include "Helper.h"
#include "GameStore.h"
#include "GameUpgrade.h"

#include "SeqLoginBonus.h"
#include "SeqLoginBonusLayer.h"
#include "PlatformHandler.h"

//#include "FlipCardBonusLayer.h"
//#include "InitRechargeLayer.h"

//#include "TaskDetailLayer.h"
#include "../config/CConfig.h"


using namespace cocos2d;
using namespace std;

#define TAG_INIT_RECHARGE_LAYER 1001


static void ScreenShoot()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //???????∞œ????∞‚?????∞‚?????¬±????????¬ß????????????????§√??????????????
    CCRenderTexture* pScreen = CCRenderTexture::create(size.width,size.height, kCCTexture2DPixelFormat_RGBA8888);
    //???????????Œ©??????????????????????
    CCScene* pCurScene = CCDirector::sharedDirector()->getRunningScene();
    //???????§√????????????????¬∫????????????
    pScreen->begin();
    //??Œ©??????????????????∞‚?????¬™????
    pCurScene->visit();
    //??¬™??????????
    pScreen->end();
    //??∞√??????????∞‚???png
    pScreen->saveToFile("XXXXXX.png", kCCImageFormatPNG);
    //??∞√??????????∞‚???jpg
    pScreen->saveToFile("XXXXXX.jpg", kCCImageFormatJPEG);
    CC_SAFE_DELETE(pScreen);
}


CCScene* GameLayer::scene(){
    
    CCScene *sc = CCScene::create();
    
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("GameLayer", GameLayerBuilderLoad::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	GameLayer* node = (GameLayer*)ccbReader->readNodeGraphFromFile("ios/ccbResources/GameLayer.ccbi", sc);
	
    
    ccbReader->release();
    
	if (node)
    {
        sc->addChild(node);
        node->setTag(100);
        node->setKeypadEnabled(true);
    }
    
	return sc;
}

GameLayer::GameLayer():
    m_pBullets(NULL),
    m_pFishes(NULL),
//    water_wave_arr(NULL),
    m_pRollNumGroup(NULL),
    m_pCannon(NULL),
//    m_pCannonTop(NULL),
    m_pBnAdd(NULL),
    m_pBnReduce(NULL),
    sp_cannon(NULL),
    sp_cannonTop(NULL),
//    sp_topCannonBg(NULL),
//    ly_bg(NULL),
    ly_fish(NULL),
//    sp_water(NULL),
    sp_scoreboard(NULL),
    sp_switch(NULL),
    sp_bg(NULL),
    sp_bg1(NULL),
    ly_switch(NULL),
    ttf_cannon_score(NULL),
    bn_mine(NULL),
    bn_mine_ele(NULL),
    isMineSelected(false),
    m_pMine(NULL),
    fish_batch_arr(NULL),
    sp_power(NULL),
    sp_power_active(NULL),
    sp_user_exp_active(NULL),
    bn_set(NULL),
    bn_sound(NULL),
    bn_power(NULL),
    bn_help(NULL),
    bn_exit(NULL),
//    cb_btnInitRecharge(NULL),
    sp_fire2(NULL),
    cb_menu(NULL),
    ly_wheel(NULL),
    ly_guide(NULL),
    sp_wheel(NULL),
    sp_user_exp(NULL),
    sp_hidebullet(NULL),
    ttf_hidebullect_cnt(NULL),
    sp_laserbullet(NULL),
    ttf_laserbullet_cnt(NULL),
    sp_gold(NULL),
    ttf_bonus_time(NULL),
    sp_coinshort(NULL),
    cd_gemstone(15),
    cd_cannon(3*50),
    sp_exp_double(NULL),
    sp_power_count(NULL),
    ttf_player_level(NULL),
    isFishGeneratorStarted(true)
//    m_pHelp(NULL)
//	  m_SeaMonsterHelp(NULL),
//	  m_pMiiHelpLeft(NULL),
//	  m_pMiiHelpRight(NULL),
//    ly_task(NULL),
//    m_sTaskIcon(NULL),
//    m_pMiiTask(NULL),
//    bmf_taskprogress(NULL),
//    bmf_tasktime(NULL),
//    ly_relief(NULL),
//    bmf_reliefCoin(NULL),
//    ly_seamonster(NULL),
//    sp_seamonster_blood(NULL),
//    sp_seamonster_time_bg(NULL),
//    ttf_seamonster_time(NULL),
//    sp_seamonster_result(NULL)
{
//    m_HelpFrame[0] = "help-1.png";
//    m_HelpFrame[1] = "help-2.png";
//    m_HelpFrame[2] = "help-3.png";
//    m_HelpFrame[3] = "help-4.png";
//    m_iHelpIndex = 0;
    _isFreezeing = false;
//    m_bShowFastBuy = 0;
    hit_count =0;
    task_index =-1;
    isUnLockMaxConnon = false;
    
    
    m_iToken = -1;
    isTaskVisable = false;
    
    lost_count = LOSE_COUNT;
    meiren_count =1;
    isLightAnimation = false;
}

GameLayer::~GameLayer(){
//    CC_SAFE_DELETE(water_wave_arr);
    CC_SAFE_DELETE(ly_fish);
//    CC_SAFE_RELEASE(ly_bg);
//    CC_SAFE_RELEASE(sp_water);
    CC_SAFE_RELEASE(sp_scoreboard);
    CC_SAFE_RELEASE(sp_cannon);
    CC_SAFE_RELEASE(sp_cannonTop);
//    CC_SAFE_RELEASE(sp_topCannonBg);
    CC_SAFE_RELEASE(m_pCannon);
//    CC_SAFE_RELEASE(m_pCannonTop);
    CC_SAFE_RELEASE(m_pBullets);
    CC_SAFE_RELEASE(m_pFishes);
    CC_SAFE_RELEASE(fish_batch_arr);
    CC_SAFE_RELEASE(m_pRollNumGroup);
    CC_SAFE_RELEASE(ly_switch);
    CC_SAFE_RELEASE(sp_switch);
    CC_SAFE_RELEASE(sp_bg);
    CC_SAFE_RELEASE(sp_bg1);
    CC_SAFE_RELEASE(ttf_cannon_score);
    CC_SAFE_RELEASE(bn_mine);
    CC_SAFE_RELEASE(bn_mine_ele);
    CC_SAFE_RELEASE(m_pMine);
    CC_SAFE_RELEASE(sp_power);
    CC_SAFE_RELEASE(sp_power_active);
    CC_SAFE_RELEASE(sp_user_exp_active);
    
    CC_SAFE_RELEASE(bn_set);
    CC_SAFE_RELEASE(bn_sound);
    CC_SAFE_DELETE(bn_power);
    CC_SAFE_RELEASE(bn_help);
    CC_SAFE_RELEASE(bn_exit);
//    CC_SAFE_RELEASE(cb_btnInitRecharge);
    
    
    CC_SAFE_RELEASE(sp_fire2);
    CC_SAFE_RELEASE(cb_menu);
    
    CC_SAFE_RELEASE(ly_wheel);
    CC_SAFE_RELEASE(ly_guide);
    CC_SAFE_RELEASE(sp_wheel);
    
    CC_SAFE_RELEASE(sp_user_exp);
    
    CC_SAFE_RELEASE(sp_hidebullet);
    CC_SAFE_RELEASE(ttf_hidebullect_cnt);
    
    CC_SAFE_RELEASE(sp_laserbullet);
    CC_SAFE_RELEASE(ttf_laserbullet_cnt);
    
    CC_SAFE_RELEASE(ttf_bonus_time);
    CC_SAFE_RELEASE(sp_coinshort);
    
    CC_SAFE_RELEASE(sp_exp_double);
    CC_SAFE_RELEASE(sp_power_count);
    
    CC_SAFE_RELEASE(ttf_player_level);
    
//    CC_SAFE_RELEASE(m_pHelp);
//    CC_SAFE_RELEASE(m_SeaMonsterHelp);
//    CC_SAFE_RELEASE(m_pMiiHelpLeft);
//    CC_SAFE_RELEASE(m_pMiiHelpRight);
    
//    CC_SAFE_RELEASE(ly_task);
//    CC_SAFE_RELEASE(m_sTaskIcon);
//    CC_SAFE_RELEASE(m_pMiiTask);
//    CC_SAFE_RELEASE(bmf_taskprogress);
//    CC_SAFE_RELEASE(bmf_tasktime);
//    CC_SAFE_RELEASE(ly_relief);
//    CC_SAFE_RELEASE(bmf_reliefCoin);
//    CC_SAFE_RELEASE(ly_seamonster);
//    CC_SAFE_RELEASE(sp_seamonster_blood);
//    CC_SAFE_RELEASE(sp_seamonster_time_bg);
//    CC_SAFE_RELEASE(ttf_seamonster_time);
//    CC_SAFE_RELEASE(sp_seamonster_result);
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
void GameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{
    
    //ttf_hidebullect_cnt = (CCLabelBMFont*)sp_hidebullet->getChildByTag(1);
    //bn_power= (CCMenuItemImage*)cb_menu->getChildByTag(9);
    cur_bg = sp_bg;
    bak_bg = sp_bg1;
    
    this->loadBcakground();
    this->initFrames();
    this->initCannon();
    this->initBackground();
    this->initFishes();
    this->initUnlockItems();
    
    fillUIElements();
    
    //????•¬???????∞¬?¬™???¬∞????????????¬∫???∞‚????????¬£???¬µ???????????????∞‚??¬™??????¬¢??????¬±¬∫???√∏??????????????????????????????????????????
    this->schedule(schedule_selector(GameLayer::updateFish), 0.5f, kCCRepeatForever, 2.0f);
    //????•¬???????∞¬?¬™???¬∞????????????¬∫???∞‚????????¬£???¬µ?????????¬∫?????????¬±¬∫???√∏??????¬¢???????
    this->schedule(schedule_selector(GameLayer::updateGame), 0.05f);
    //
    this->schedule(schedule_selector(GameLayer::updateBonus), 1.0f);
    // ???????∞‚???????????¬∫????¬±? ??¬µ?????????¬Æ¬∞??????∞‚?????∞‚??????
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        //??∞‚??¬ß???¬¢??????????
        this->scheduleOnce(schedule_selector(GameLayer::prepareSwitchBg), 4*60.0f);
        this->scheduleOnce(schedule_selector(GameLayer::generateBombFish), arc4random()%60+60);
    }
    else if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
    {
//        this->schedule(schedule_selector(GameLayer::addSeaMonsterBlood), 10);
    }
    
//    cb_btnInitRecharge->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.5, 0.9),CCScaleTo::create(0.5, 1.0),NULL)));
//    // ??¬∂?????????¬µ?????????¬Æ¬∞????????????√¶??¬Æ¬∞??¬∫? ???????¬∞????
//    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
//    {
//        this->schedule(schedule_selector(GameLayer::updateSeaMonsterTime), 1);
//    }
    
//    checkTask();
   // PlatformHandler::getInstance()->initPay();
    
}

bool GameLayer::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_switch", CCLayer*, this->ly_switch);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_fish", CCLayer*, this->ly_fish);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_bg", CCLayer*, this->ly_bg);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_water", CCSprite*, this->sp_water);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_switch", CCSprite*, this->sp_switch);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_bg", CCSprite*, this->sp_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_bg1", CCSprite*, this->sp_bg1);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_power", CCSprite*, this->sp_power);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_power_active", CCSprite*, this->sp_power_active);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_user_exp_active", CCSprite*, this->sp_user_exp_active);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_cannon", CCSprite*, this->sp_cannon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_scoreboard", CCSprite*, this->sp_scoreboard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_cannonTop", CCSprite*, this->sp_cannonTop);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_topCannonBg", CCSprite*, this->sp_topCannonBg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_fire2", CCSprite*, this->sp_fire2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menu", CCMenu*, this->cb_menu);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBnAdd", CCMenuItemImage*, this->m_pBnAdd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBnReduce", CCMenuItemImage*, this->m_pBnReduce);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_mine", CCMenuItemImage*, this->bn_mine);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_mine_ele", CCMenuItemImage*, this->bn_mine_ele);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_set", CCMenuItemImage*, this->bn_set);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_sound", CCMenuItemImage*, this->bn_sound);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_power", CCMenuItemImage*, this->bn_power);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_help", CCMenuItemImage*, this->bn_help);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_exit", CCMenuItemImage*, this->bn_exit);
    
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_btnInitRecharge", CCMenuItemImage*, this->cb_btnInitRecharge);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_cannon_score", CCLabelBMFont*, this->ttf_cannon_score);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_wheel", CCLayer*, this->ly_wheel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_guide", CCLayerColor*, this->ly_guide);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_wheel", CCSprite*, this->sp_wheel);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_user_exp", CCSprite*, this->sp_user_exp);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_hidebullet", CCSprite*, this->sp_hidebullet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_hidebullect_cnt", CCLabelBMFont*, this->ttf_hidebullect_cnt);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_laserbullet", CCSprite*, this->sp_laserbullet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_laserbullet_cnt", CCLabelTTF*, this->ttf_laserbullet_cnt);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_bonus_time", CCLabelBMFont*, this->ttf_bonus_time);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_coinshort", CCSprite *, this->sp_coinshort);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_exp_double", CCSprite*, this->sp_exp_double);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_power_count", CCSprite*, this->sp_power_count);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_player_level", CCSprite*, this->ttf_player_level);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pHelp", CCSprite*, this->m_pHelp);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_SeaMonsterHelp", CCSprite *, this->m_SeaMonsterHelp);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiHelpLeft", CCMenuItemImage *, this->m_pMiiHelpLeft);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiHelpRight", CCMenuItemImage *, this->m_pMiiHelpRight);
    
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_task", CCLayer*, this->ly_task);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sTaskIcon", CCSprite*, this->m_sTaskIcon);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiTask", CCMenuItemImage *, this->m_pMiiTask);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bmf_taskprogress", CCLabelBMFont*, this->bmf_taskprogress);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bmf_tasktime", CCLabelBMFont*, this->bmf_tasktime);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_relief", CCLayer*, this->ly_relief);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bmf_reliefCoin", CCLabelBMFont *, this->bmf_reliefCoin);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_seamonster", CCLayer *, this->ly_seamonster);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_seamonster_blood", CCSprite *, this->sp_seamonster_blood);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_seamonster_time_bg", CCSprite *, this->sp_seamonster_time_bg);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_seamonster_time", CCLabelTTF *, this->ttf_seamonster_time);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_seamonster_result", CCSprite *, this->sp_seamonster_result);
	return true;
    
}

SEL_MenuHandler GameLayer::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "addCannonSize", GameLayer::addCannonSize);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "reduceCannonSize", GameLayer::reduceCannonSize);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "exitGameLayerSel", GameLayer::exitGameLayerSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "setGameLayerSel", GameLayer::setGameLayerSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "soundGameLayerSel", GameLayer::soundGameLayerSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "helpGameLayerSel", GameLayer::helpGameLayerSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "storeGameLayerSel", GameLayer::storeGameLayerSel);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onInitRechargeClicked", GameLayer::onInitRechargeClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "mineSel", GameLayer::mineSel);
     CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "enterGameLayerTip", GameLayer::enterGameLayerTip);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "buyPower", GameLayer::buyPower);
     CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "cancleGameLayerTip", GameLayer::cancleGameLayerTip);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "helpExitSel", GameLayer::helpExitSel);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "leftCallback", GameLayer::leftCallback);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "rightCallback", GameLayer::rightCallback);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "taskCallback", GameLayer::taskCallback);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "reliefCallback", GameLayer::reliefCallback);
	return NULL;
}

SEL_CCControlHandler GameLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void GameLayer::onEnter()
{
    //ttf_hidebullect_cnt = (CCLabelBMFont*)sp_hidebullet->getChildByTag(1);
    
    GameData::getSharedGameData()->setDataPoint(DT_Game, this);
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
	CCLayer::onEnter();
    
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayer::syncScoreUI), "Game_Global_Score_Change", NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayer::syncHideUI), "Game_Global_Hide_Change", NULL);

    
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayer::onInitRechargeNotify), kInitRechargeNotifiction, NULL);	
 
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayer::onBoughtResultNotify), kInitRechargResultNotification, NULL);
    
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayer::onFlipCardBonusNotify), kFlipCardBonusNotification, NULL);

    
    Sound::Instance()->playMusic("BGMusic1.ogg");
    if (GameData::getSharedGameData()->hideBulletCount() >0) {
        m_pCannon->isHideBullet =true;
    }
    updateScoreUI(0);
//    GameData::getSharedGameData()->addGameDiamond(Diamond_Yellow, 7);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    
    
}

void GameLayer::onExit()
{
    GameData::getSharedGameData()->setDataPoint(DT_Game, NULL);
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	CCLayer::onExit();

}



void GameLayer::onEnterTransitionDidFinish() {
    if (!SeqLoginBonusManager::sharedSeqLoginBonusManager()->isSameDay()) {
        addChild(SeqLoginBonusLayer::scene());
    }
    else
    {
        GameData* pData = GameData::getSharedGameData();
        pData->addTodayLoginCount();
        
        if (task_index == -1 && !pData->getIsHaveVipCard()) {
            task_index = 2;
            setTaskInfoPanle(task_index);
        }
    }
}


void GameLayer::loadBcakground()
{
    cur_background_index = arc4random()%3+1;
    
    Scene s = GameData::getSharedGameData()->currentScene();
    DF_LOG("GameLayer::loadBcakground Scene = %d",s);
    switch (s) {
        case SceneMystical:  //?????????????¬µ???????
        {
            bgFileNamePrefix = "bg";
			//edit by lqg jpg->png
            CCString* str = CCString::createWithFormat("%s0%d.jpg",bgFileNamePrefix,cur_background_index);
            
//            CCSpriteFrame* spFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
//            cur_bg->setDisplayFrame(spFrame);
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(str->getCString());
            DF_LOG("GameLayer::loadBcakground SceneMystical str=%s,texture=%x",str->getCString(),texture);
            cur_bg->setTexture(texture);
        }
            break;
            
            case SceneDream:  //??¬¢?????¬™??¬µ??????
        {
            bgFileNamePrefix = "bf";
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg2.plist");
//            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bf01.jpg");
//            sp_bg->setDisplayFrame(frame);
//            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bf02.jpg");
//            sp_bg1->setDisplayFrame(frame);
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bg.plist");
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bf01.jpg");
            DF_LOG("GameLayer::loadBcakground SceneDream texture1=%x",texture);
            sp_bg->setTexture(texture);
            texture = CCTextureCache::sharedTextureCache()->addImage("bf02.jpg");
            DF_LOG("GameLayer::loadBcakground SceneDream texture2=%x",texture);

            sp_bg1->setTexture(texture);
        }
            break;
            
            case SceneProfusion:  //??¬∫¬ß??????????¬µ???????
        {
            bgFileNamePrefix = "be";
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg3.plist");
//            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("be01.jpg");
//            sp_bg->setDisplayFrame(frame);
//            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("be02.jpg");
//            sp_bg1->setDisplayFrame(frame);
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bg.plist");
            
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("be01.jpg");
            DF_LOG("GameLayer::loadBcakground SceneProfusion texture1=%x",texture);
            sp_bg->setTexture(texture);
            texture = CCTextureCache::sharedTextureCache()->addImage("be02.jpg");
            DF_LOG("GameLayer::loadBcakground SceneProfusion texture2=%x",texture);
            sp_bg1->setTexture(texture);
        }
            break;
        case SceneHistoric:  //???????§√?¬µ??????
        {
            bgFileNamePrefix = "bd";
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg4.plist");
//            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bd01.jpg");
//            sp_bg->setDisplayFrame(frame);
//            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bd02.jpg");
//            sp_bg1->setDisplayFrame(frame);
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bg.plist");
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bd01.jpg");
            DF_LOG("GameLayer::loadBcakground SceneHistoric texture1=%x",texture);
            sp_bg->setTexture(texture);
            texture = CCTextureCache::sharedTextureCache()->addImage("bd02.jpg");
            DF_LOG("GameLayer::loadBcakground SceneHistoric texture2=%x",texture);
            sp_bg1->setTexture(texture);
        }
            break;
        case SceneSeaMonsterNormal:
        {
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("hgeasy.jpg");
            DF_LOG("GameLayer::loadBcakground SceneSeaMonsterNormal texture=%x",texture);

            cur_bg->setTexture(texture);
            break;
        }
            
        case SceneSeaMonsterDifficulty:
        {
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("hghard.jpg");
            DF_LOG("GameLayer::loadBcakground SceneSeaMonsterDifficulty texture=%x",texture);
            cur_bg->setTexture(texture);
            break;
        }
        default:
            break;
    }
}


void GameLayer::initFrames(){
    //?????Œ©Œ©?????????????????????¬∫???????[G2]
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pao.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tool.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("card.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("light.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("net01.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("net02.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("net03.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("help.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zha.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("addGold.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("number.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("quan.plist");
    
}

void GameLayer::initBackground(){
    
    this->setRollNumGroup(RollNumGroup::createWithGameLayer(this, 8));
    //edit by andy 2015-03-26
    m_pRollNumGroup->setPosition(sp_scoreboard->getPosition());
    updateScoreUI(0);
    
    DF_LOG("sp_scoreboard Z = %d",sp_scoreboard->getZOrder());
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
//    ly_bg->setContentSize(winSize);
    
//    float sp_water_w = sp_water->getContentSize().width;
//    float sp_water_h = sp_water->getContentSize().height;
    
//    int x_cnt = ly_bg->getContentSize().width / sp_water_w;
//    int y_cnt = ly_bg->getContentSize().height / sp_water_h;
    
    
    //water frame action
//    int frameCnt = WaterWaveFrameCount;
//    CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
//    
//    water_wave_arr = CCArray::create();
//    water_wave_arr->retain();
//    for(int i=0;i <frameCnt;i++){
//        CCString *frameName=CCString::createWithFormat("%d.png",i);
//        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
//        aniframe->addObject(frame);//?????????????∞‚??????????????§√???¬µ???¬Æ???¬™?????¬™?????????????????????
//    }
    
//    CCAnimation* t_Animation = CCAnimation::createWithSpriteFrames(aniframe,0.15);//?????√∏????????????¬™??????¬Æ????
    
    
//    for (int i = 0; i < x_cnt + 1; i ++) {
//        for (int j = 0; j < y_cnt + 1; j ++) {
//            if (i == 0 && j == 0) {
//                CCAnimate *animate=CCAnimate::create(t_Animation);
//                sp_water->runAction(CCRepeat::create(animate, 1000));
//                water_wave_arr->addObject(sp_water);
//                continue;
//            }
//            CCSprite* sp = CCSprite::createWithSpriteFrameName("0.png");
//            sp->setAnchorPoint(CCPointZero);
//            CCPoint pos = CCPoint((sp_water_w-0.5) * i , (sp_water_h-0.5) * j);
//            sp->setPosition(pos);
//            ly_bg->addChild(sp);
//            water_wave_arr->addObject(sp);
//            CCAnimate *animate=CCAnimate::create(t_Animation);
//            sp->runAction(CCRepeat::create(animate, 1000));
//        }
//    }
    
    updateUIExp();
    
    //edit by andy 2015-03-31
//    NumSprite *p = NumSprite::create(60, GameNumberGameLayerTime);
 //   NumSprite *p = NumSprite::create(60, GameNumberGameLayerTime);

 //   p->setPosition(ttf_bonus_time->getPosition());
//    p->setScale(0.5f);
//    p->setAnchorPoint(CCPoint(0.5,0));
  //  addChild(p,ttf_bonus_time->getZOrder(),BonusTimeNumberTag);
   // DF_LOG("ttf_bonus_time Z = %d",ttf_bonus_time->getZOrder());
    ttf_bonus_time->setVisible(true);
    ttf_bonus_time->setString(CCString::createWithFormat("%d",60)->getCString());
    
    
    bn_exit->setPosition(ccp(bn_set->getPositionX() + bn_set->getContentSize().width, bn_set->getContentSize().height * 1));
    bn_sound->setPosition(ccp(bn_set->getPositionX() + bn_set->getContentSize().width, bn_set->getContentSize().height * 2));
    bn_help->setPosition(ccp(bn_set->getPositionX() + bn_set->getContentSize().width, bn_set->getContentSize().height * 3));
    
    bn_exit->setAnchorPoint(ccp(0.5,0));
    bn_sound->setAnchorPoint(ccp(0.5,0));
    if (Sound::Instance()->getIsCloseSound() == false)
    {
        bn_sound->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_song_on.png"));
    } else {
        bn_sound->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_song_off.png"));
    }
    bn_help->setAnchorPoint(ccp(0.5,0));
    
    // sea monster
    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Normal || GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
    {
//        ly_seamonster->setVisible(true);
        if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Normal)
        {
//            sp_seamonster_time_bg->setVisible(false);
//            ttf_seamonster_time->setVisible(false);
        }
        else
        {
//            sp_seamonster_time_bg->setVisible(true);
//            ttf_seamonster_time->setVisible(true);
        }
    }
    else
    {
//        ly_seamonster->setVisible(false);
    }
}

//void GameLayer::hideWaterWave()
//{
//    for(int i = 0; i < water_wave_arr->count(); i++)
//    {
//        CCSprite* sp = (CCSprite*)water_wave_arr->objectAtIndex(i);
//        CCFadeOut* fout = CCFadeOut::create(0.5f);
//        sp->runAction(fout);
//    }
//    
//    CCObject *pFishObj = NULL;
//    CCARRAY_FOREACH_REVERSE(m_pFishes, pFishObj)
//    {
//        Fish *pFish = (Fish *)pFishObj;
//        if (pFish == NULL) {
//            continue;
//        }
//        pFish->stopAllActions();
//        CCFiniteTimeAction *callFunc = CCCallFunc::create(pFish, callfunc_selector(Fish::removeFromParent));
//        pFish->runAction(CCSequence::create(CCFadeOut::create(0.5f), callFunc,NULL));
//    }
//    m_pFishes->removeAllObjects();
//}

//void GameLayer::showWaterWave()
//{
//    for(int i = 0; i < water_wave_arr->count(); i++)
//    {
//        CCSprite* sp = (CCSprite*)water_wave_arr->objectAtIndex(i);
//        CCFadeIn* fout = CCFadeIn::create(0.5f);
//        sp->runAction(fout);
//    }
//    
////    CCObject *pFishObj = NULL;
////    CCARRAY_FOREACH(m_pFishes, pFishObj)
////    {
////        Fish *pFish = (Fish *)pFishObj;
////        if (pFish == NULL) {
////            continue;
////        }
////        pFish->runAction(CCFadeIn::create(0.5f));
////        
////    }
//}



void GameLayer::changeBg()
{
    //swap bg sprite
    CCSprite* sp_tmp = bak_bg;
    
    bak_bg = cur_bg;
    cur_bg = sp_tmp;
    
    bak_bg->setOpacity(255);
    bak_bg->setPositionX(CCDirector::sharedDirector()->getWinSize().width * 1.15);
    
    FishMatrix *p = FishMatrix::create(this);
    ly_fish->addChild(p);
    p->goFishMatrix();
    
    CCObject* pObj;
    CCARRAY_FOREACH(p->m_fishes,pObj)
    {
        Fish* pf=(Fish*)pObj;
//        ly_fish->addChild(pf);
        getBatchNodeFish()->addChild(pf);
        pf->goFish();
        
        m_pFishes->addObject(pf);
    }

}

void GameLayer::prepareSwitchBg()
{
    //stop fish generator
    isFishGeneratorStarted = false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* sp = CCSprite::createWithSpriteFrameName("fishtide.png");
    ly_fish->addChild(sp);
    sp->setAnchorPoint(ccp(0,0.5));
    sp->setPosition(ccp(winSize.width,winSize.height/2));
    sp->runAction(CCSequence::create(CCDelayTime::create(10),CCMoveBy::create(10,ccp(-winSize.width-sp->getContentSize().width,0)),NULL));
    this->scheduleOnce(schedule_selector(GameLayer::switchBg), 20.0f);
}



void GameLayer::switchBg()
{
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    float changeTime = 3.0f;
    
    float waterTime = changeTime + sp_switch->getContentSize().width * changeTime / winSize.width;
    
    CCMoveTo* swMove = CCMoveTo::create(waterTime, CCPoint(-(sp_switch->getContentSize().width), sp_switch->getPosition().y));
    CCPlace* swRest = CCPlace::create(CCPoint(winSize.width, sp_switch->getPosition().y));
    CCSequence* swSeq = CCSequence::create(CCDelayTime::create(changeTime/4),swMove,swRest,NULL);
    sp_switch->runAction(swSeq);
    
    int frameCnt = 1;
    CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
    
    for(int i=0;i <frameCnt;i++){
        CCString *frameName=CCString::createWithFormat("switch%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        aniframe->addObject(frame);//?????????????∞‚??????????????§√???¬µ???¬Æ???¬™?????¬™?????????????????????
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(aniframe,0.2);//?????√∏????????????¬™??????¬Æ????
    CCAnimate *animate=CCAnimate::create(animation);
    sp_switch->runAction(CCRepeat::create(animate, 50));
    
    Sound::Instance()->playEffect("WaveEnter.mp3");
    
    cur_background_index++;
    cur_background_index = cur_background_index > 3 ? 1: cur_background_index;
    DF_LOG("GameLayer::switchBg bgFileNamePrefix = %s",bgFileNamePrefix);
	//edit by lqg jpg->png
    CCString* str = CCString::createWithFormat("%s0%d.jpg",bgFileNamePrefix,cur_background_index);
    
//    CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
//    bak_bg->setDisplayFrame(spFram);
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(str->getCString());
    bak_bg->setTexture(texture);
    
    float newBgTime = changeTime + 0.15 * changeTime;
    
    CCMoveTo* bgMove = CCMoveTo::create(newBgTime, CCPointZero);
//    CCFiniteTimeAction *newBgFunc = CCCallFunc::create(this, callfunc_selector(GameLayer::showWaterWave));
    CCSequence* newBgSeq = CCSequence::create(CCDelayTime::create(changeTime/4),bgMove,NULL);
    bak_bg->runAction(newBgSeq);
    
    CCFiniteTimeAction *bgFout = CCFadeOut::create(changeTime);
    CCFiniteTimeAction *bgFunc = CCCallFunc::create(this, callfunc_selector(GameLayer::changeBg));
    CCCallFunc *taskFunc = CCCallFunc::create(this, callfunc_selector(GameLayer::showGoodSixGift));
    CCSequence* bgSeq = CCSequence::create(bgFout,bgFunc,taskFunc,NULL);
    cur_bg->runAction(bgSeq);
    
//    this->hideWaterWave();
    
    this->scheduleOnce(schedule_selector(GameLayer::generateBombFish), arc4random()%60+60);
}


void GameLayer::initFishes()
{
    this->setBatchNodeFish(CCSpriteBatchNode::create("Fish1.pvr.ccz"));
    ly_fish->addChild(this->m_pBatchNodeFish);
    
    this->setFishes(CCArray::create());
}


void GameLayer::initUnlockItems()
{
    
    for (int i = 0; i <= GameData::getSharedGameData()->currentLevel(); i++) {
        switch (i) {
            case 2:
                m_pCannon->cannon_score_max = 400;
//                m_pCannonTop->cannon_score_max = 350;
                break;
            case 3:
                GameData::getSharedGameData()->unlockFish(Fish::FISH_FEIYU);
                break;
            case 4:
                m_pCannon->cannon_score_max = 500;
//                m_pCannonTop->cannon_score_max = 400;
                break;
            case 5:
                m_pCannon->cannon_score_max = 600;
//                m_pCannonTop->cannon_score_max = 450;
                break;
            case 6:
                m_pCannon->cannon_score_max = 700;
//                m_pCannonTop->cannon_score_max = 500;
                break;
            case 8:
                m_pCannon->cannon_score_max = 800;
//                m_pCannonTop->cannon_score_max = 600;
                break;
            case 10:
                break;
            case 12:
                GameData::getSharedGameData()->unlockFish(Fish::FISH_LONGXIA);
                break;
            case 15:
                m_pCannon->cannon_score_max = 900;
//                m_pCannonTop->cannon_score_max = 700;
                break;
            case 18:
                GameData::getSharedGameData()->unlockFish(Fish::FISH_ZHADANFISH);
                break;
            case 20:
                m_pCannon->cannon_score_max = 1000;
//                m_pCannonTop->cannon_score_max = 800;
                break;
            case 22:
                GameData::getSharedGameData()->unlockFish(Fish::FISH_HAITUN);
                break;
            case 24:
                m_pCannon->cannon_score_max = 1100;
//                m_pCannonTop->cannon_score_max = 900;
                break;
            case 26:
                GameData::getSharedGameData()->unlockFish(Fish::FISH_DAYINSHA);
                break;
            case 28:
                m_pCannon->cannon_score_max = 1200;
//                m_pCannonTop->cannon_score_max = 1000;
                break;
            case 30:
                GameData::getSharedGameData()->unlockFish(Fish::FISH_LANJING);
                break;
            default:
                break;
        }
    }
    
    //add by andy 2015-03-23
    if (GameData::getSharedGameData()->getUnLockMaxConnon()) {
        m_pCannon->cannon_score_max = 1200;
    }
    //add end by andy
    switch(GameData::getSharedGameData()->currentScene()) {
        case SceneMystical:  //?????????????¬µ???????
            Fish::lockFishRing(Fish::SPEC_HLYQ, true);
            if(GameData::getSharedGameData()->currentLevel() >= 10){
                Fish::lockFishRing(Fish::SPEC_HYLL, false);
            } else {
                Fish::lockFishRing(Fish::SPEC_HYLL, true);
            }
            Fish::lockFishRing(Fish::SPEC_TLYQ, true);
            Fish::lockFishRing(Fish::SPEC_DASIXI, true);
            Fish::lockFishRing(Fish::SPEC_ZDYQ, true);
            Fish::lockFishRing(Fish::SPEC_YWYQ, false);
            break;
        case SceneDream:  //??¬¢?????¬™??¬µ??????
            Fish::lockFishRing(Fish::SPEC_HLYQ, true);
            if(GameData::getSharedGameData()->currentLevel() >= 10){
                Fish::lockFishRing(Fish::SPEC_HYLL, false);
            } else {
                Fish::lockFishRing(Fish::SPEC_HYLL, true);
            }
            Fish::lockFishRing(Fish::SPEC_TLYQ, false);
            Fish::lockFishRing(Fish::SPEC_DASIXI, true);
            Fish::lockFishRing(Fish::SPEC_ZDYQ, true);
            Fish::lockFishRing(Fish::SPEC_YWYQ, true);
            break;
        case SceneProfusion:  //??¬∫¬ß??????????¬µ???????
            Fish::lockFishRing(Fish::SPEC_HLYQ, true);
            if(GameData::getSharedGameData()->currentLevel() >= 10){
                Fish::lockFishRing(Fish::SPEC_HYLL, false);
            } else {
                Fish::lockFishRing(Fish::SPEC_HYLL, true);
            }
            Fish::lockFishRing(Fish::SPEC_TLYQ, true);
            Fish::lockFishRing(Fish::SPEC_DASIXI, false);
            Fish::lockFishRing(Fish::SPEC_ZDYQ, true);
            Fish::lockFishRing(Fish::SPEC_YWYQ, true);
            break;
        case SceneHistoric:  //???????§√?¬µ??????
            Fish::lockFishRing(Fish::SPEC_HLYQ, false);
            if(GameData::getSharedGameData()->currentLevel() >= 10){
                Fish::lockFishRing(Fish::SPEC_HYLL, false);
            } else {
                Fish::lockFishRing(Fish::SPEC_HYLL, true);
            }
            Fish::lockFishRing(Fish::SPEC_TLYQ, true);
            Fish::lockFishRing(Fish::SPEC_DASIXI, true);
            Fish::lockFishRing(Fish::SPEC_ZDYQ, true);
            Fish::lockFishRing(Fish::SPEC_YWYQ, true);
            break;
        case SceneSeaMonsterNormal:
            Fish::lockFishRing(Fish::SPEC_HLYQ, false);
            Fish::lockFishRing(Fish::SPEC_HYLL, false);
            Fish::lockFishRing(Fish::SPEC_TLYQ, false);
            Fish::lockFishRing(Fish::SPEC_DASIXI, false);
            Fish::lockFishRing(Fish::SPEC_ZDYQ, false);
            Fish::lockFishRing(Fish::SPEC_YWYQ, false);
            break;
        case SceneSeaMonsterDifficulty:
            Fish::lockFishRing(Fish::SPEC_HLYQ, false);
            Fish::lockFishRing(Fish::SPEC_HYLL, false);
            Fish::lockFishRing(Fish::SPEC_TLYQ, false);
            Fish::lockFishRing(Fish::SPEC_DASIXI, false);
            Fish::lockFishRing(Fish::SPEC_ZDYQ, false);
            Fish::lockFishRing(Fish::SPEC_YWYQ, false);
            break;
        default:
            break;
    }
}


void GameLayer::initCannon(){
    this->setBullets(CCArray::create());
    
    this->setBatchNodePao(CCSpriteBatchNode::create("pao.pvr.ccz"));
    ly_switch->addChild(this->m_pBatchNodePao, 101, SP_TAG_CANNON);
    this->setBatchNodeCoin(CCSpriteBatchNode::create("addGold.pvr.ccz"));
    ly_fish->addChild(this->m_pBatchNodeCoin);
//    CCSpriteBatchNode *pBatchNode=CCSpriteBatchNode::create("pao.png");
//    ly_switch->addChild(pBatchNode,101,SP_TAG_CANNON);
    this->setCannon(Cannon::createWithCannonType(this, m_pBatchNodePao,sp_cannon));
//    this->setCannon(Cannon::createWithCannonType(Laser_Cannon, this, pBatchNode,sp_cannon));
    
    // top cannon fire
//    this->setCannonTop(Cannon::createWithCannonType(this, pBatchNode, sp_cannonTop));
//    sp_topCannonBg->setVisible(false);
    sp_cannonTop->setVisible(false);
    
    NumSprite *p = NumSprite::create(m_pCannon->cannon_score);
    p->setPosition(CCPoint(m_pCannon->m_pSprite->getPosition().x,2));
//    p->setScale(0.5f);
    p->setAnchorPoint(CCPoint(0.5,0));
    addChild(p,m_pCannon->m_pSprite->getZOrder(),CannonScoreNumberTag);
    DF_LOG("Cannon init p=%d",p->getZOrder());
//    this->setBatchNodeNet1(CCSpriteBatchNode::create("net01.png"));
//    ly_switch->addChild(this->m_pBatchNodeNet1);
//    this->setBatchNodeNet2(CCSpriteBatchNode::create("net02.pvr.ccz"));
//    ly_switch->addChild(this->m_pBatchNodeNet2);
//    this->setBatchNodeNet3(CCSpriteBatchNode::create("net03.png"));
//    ly_switch->addChild(this->m_pBatchNodeNet3);
    //    this->addChild(this->m_pBatchNodeFish4);
//    
//    this->m_pBatchNodeBullets=CCSpriteBatchNode::create("pao.pvr.ccz");
//    this->addChild(this->m_pBatchNodeBullets);
//    CCSpriteBatchNode *pMineBatchNode=CCSpriteBatchNode::create("zha.pvr.ccz");
//    ly_switch->addChild(pMineBatchNode, 101 + 1, SP_TAG_CANNON + 1);
    m_pMine = Mine::create(m_pBatchNodePao);
    m_pMine->hit_rate = 10000;
    
}


void GameLayer::helpExitSel(CCObject *pSender)
{
    ly_guide->setVisible(false);
    Sound::Instance()->playEffect("btn.mp3");
}


void GameLayer::mineSel(CCObject *pSender)
{
//    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
//    {
//        GameData::getSharedGameData()->setCurrentPower(0);
//        GameData::getSharedGameData()->save();
//    }
//    else
//    {
//        GameData::getSharedGameData()->setSeaMonsterPower(0);
//    }
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
    hit_count = 0;
    if (((CCNode*)pSender)->getTag() == Ele_Cannon)
    {
        m_pMine->startEle(this);
    }
    else
    {
        m_pMine->startKnife(CCPoint(0, 0), this);
    }
    updateUIExp();
    // ??∞¬?¬™???¬∞?????????? ??∞Œ©√∏√??¬Æ??????Œ©???????
    //del by andy 2015-04-27
   // GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_USESPECIALWEAPON, 0, 1);
//    isMineSelected = true;
    bn_mine->setVisible(false);
    bn_mine->setPositionY(-bn_mine->getContentSize().height/2);
    bn_mine_ele->setVisible(false);
    bn_mine_ele->setPositionY(bn_mine->getPositionY());
//    sp_power->stopAllActions();
//    sp_power->setScaleX(0);
    updateMinePower(0);
}

void GameLayer::addCannonSize(CCObject *pSender){
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
    if (m_pCannon->getConnonType() == Power_Cannon)
        return ;
        if(m_pCannon ->cannon_score == m_pCannon ->cannon_score_max && m_pCannon ->cannon_score_max != 1200)
        {
            if (task_index == -1) {
                task_index =1;
                setTaskInfoPanle(task_index);
            }
        }
        else
        {
            m_pCannon->incCannonScore();
            
            
            //    CCString* str = CCString::createWithFormat("%d",m_pCannon->cannon_score);
            //    ttf_cannon_score->setString(str->getCString());
            
            Sound::Instance()->playEffect("SwitchSilo.mp3");
            
            removeChildByTag(CannonScoreNumberTag);
            NumSprite *p = NumSprite::create(m_pCannon->cannon_score);
            p->setPosition(CCPoint(m_pCannon->m_pSprite->getPosition().x,2));
            //    p->setScale(0.5f);
            p->setAnchorPoint(CCPoint(0.5,0));
            addChild(p,m_pCannon->m_pSprite->getZOrder(),CannonScoreNumberTag);
            DF_LOG("Cannon add p=%d",p->getZOrder());
        }


}

void GameLayer::reduceCannonSize(CCObject *pSender){
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
    if (m_pCannon->getConnonType() == Power_Cannon)
        return ;
    m_pCannon->decCannonScore();
    
    removeChildByTag(CannonScoreNumberTag);
    NumSprite *p = NumSprite::create(m_pCannon->cannon_score);
    p->setPosition(CCPoint(m_pCannon->m_pSprite->getPosition().x,2));
//    p->setScale(0.5f);
    p->setAnchorPoint(CCPoint(0.5,0));
    addChild(p,m_pCannon->m_pSprite->getZOrder(),CannonScoreNumberTag);
    DF_LOG("Cannon inc p=%d",p->getZOrder());
    Sound::Instance()->playEffect("SwitchSilo.mp3");
}


void GameLayer::exitGameLayerSel(CCObject *pSender)
{
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
    //??¬Æ??∞¬??????¬Æ???????????????????????,??∞Œ???????????????????????????????∞‚?????¬ß¬©???¬ß??????¬ß¬±??¬•????????????????¬ß????
    SeqLoginBonusManager::sharedSeqLoginBonusManager()->setIsSameDay();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(SceneReplaceTime, IntroLayer::scene(), ccBLACK));
    Sound::Instance()->playEffect("btn.mp3");
}


void GameLayer::enableGameSet()
{
    bn_set->setEnabled(true);
}

void GameLayer::hideMenu()
{
    showMenu(false);
}

void GameLayer::showMenu(bool show)
{
    float distance = bn_set->getContentSize().height;
    float moveTime = 0.5f;
    bn_set->setEnabled(false);
    if(show) {
        CCMoveTo* exitMove = CCMoveTo::create(moveTime, CCPoint(bn_set->getPositionX(),distance*1+20));
        CCMoveTo* soundMove = CCMoveTo::create(moveTime, CCPoint(bn_set->getPositionX(),distance*2+20));
        CCMoveTo* helpMove = CCMoveTo::create(moveTime, CCPoint(bn_set->getPositionX(),distance*3+20));
        bn_exit->setVisible(true);
        bn_sound->setVisible(true);
        bn_help->setVisible(true);
        bn_exit->runAction(exitMove);
        bn_sound->runAction(soundMove);
        bn_help->runAction(helpMove);
        bn_set->runAction(CCRotateBy::create(0.5, -150));
        this->scheduleOnce(schedule_selector(GameLayer::hideMenu), 15);
    } else {
        CCMoveTo* exitMove = CCMoveTo::create(moveTime, CCPoint(bn_set->getPositionX() + bn_set->getContentSize().width,distance*1+20));
        CCMoveTo* soundMove = CCMoveTo::create(moveTime, CCPoint(bn_set->getPositionX() + bn_set->getContentSize().width,distance*2+20));
        CCMoveTo* helpMove = CCMoveTo::create(moveTime, CCPoint(bn_set->getPositionX() + bn_set->getContentSize().width,distance*3+20));
        CCSequence* exitSeq = CCSequence::create(exitMove,CCHide::create(),NULL);
        CCSequence* soundSeq = CCSequence::create(soundMove,CCHide::create(),NULL);
        CCSequence* helpSeq = CCSequence::create(helpMove,CCHide::create(),NULL);
        bn_exit->runAction(exitSeq);
        bn_sound->runAction(soundSeq);
        bn_help->runAction(helpSeq);
        bn_set->runAction(CCRotateBy::create(0.5, 150));
    }
    this->scheduleOnce(schedule_selector(GameLayer::enableGameSet), moveTime+0.1f);
}

void GameLayer::setMenuEnable(bool pEnable)
{
    cb_menu->setEnabled(pEnable);
    setTouchEnabled(pEnable);
}

void GameLayer::setGameLayerSel(CCObject *pSender)
{
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
//    CCDirector::sharedDirector()->pushScene(GameAwardLayer::scene());
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(SceneReplaceTime, FlipCardBonusLayer::scene(), ccBLACK));
    
//    startRollLottery();??
    
    if (bn_exit->isVisible() == false) {
        showMenu(true);
    } else {
        showMenu(false);
    }
    Sound::Instance()->playEffect("btn.mp3");
}

void GameLayer::soundGameLayerSel(CCObject *pSender)
{
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
    Sound::Instance()->switchSound();
    
    if (Sound::Instance()->getIsCloseSound() == false)
    {
        bn_sound->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_song_on.png"));
    } else {
        bn_sound->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_song_off.png"));
    }
    
    Sound::Instance()->playEffect("btn.mp3");
}

void GameLayer::helpGameLayerSel(CCObject *pSender)
{
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
    Sound::Instance()->playEffect("btn.mp3");
    ly_guide->setZOrder(10);
    ly_guide->setVisible(true);
//    switch (GameData::getSharedGameData()->getGameType())
//    {
//        case GameType_Normal:
//            m_pHelp->setVisible(true);
//            m_SeaMonsterHelp->setVisible(false);
//            m_pMiiHelpLeft->setVisible(true);
//            m_pMiiHelpRight->setVisible(true);
//            break;
//        case GameType_SeaMonster_Normal:
//        case GameType_SeaMonster_Difficulty:
//            m_pHelp->setVisible(false);
//            m_SeaMonsterHelp->setVisible(true);
//            m_pMiiHelpLeft->setVisible(false);
//            m_pMiiHelpRight->setVisible(false);
//            break;
//        default:
//            break;
//    }
}

void GameLayer::storeGameLayerSel(CCObject *pSender)
{
    DF_LOG("storeGameLayerSel  isTaskVisable= %d",isTaskVisable);
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return ;
    }
    if(isTaskVisable)
        return;
        
    CCScene* sc = GameStoreLayer::scene(true);
    //    addChild(sc,10);
    addChild(sc, 10, 888);
    if (sc->getChildByTag(888))
    {
        ((GameStoreLayer*)(sc->getChildByTag(888)))->setFastBuyVisible(false);
    }
   Sound::Instance()->playEffect("btn.mp3");
}
void GameLayer::enterGameLayerTip(CCObject *pSender)
{
    DF_LOG("GameLayer::enterGameLayerTip ");
    isTaskVisable =false;
    
    hit_count =0;
    int pToken = arc4random() % 9999;
    setToken(pToken);
    setTaskIndex(task_index);
//    buyTaskSuccess(pToken);
    ProductType id =(ProductType)(task_index+1010);
    buyTask(id);
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS) 
    buyTaskSuccess((ProductType)id);
#endif
//   if(task_index == 1)
//    {
//        CCNotificationCenter::sharedNotificationCenter()->postNotification("Game_Task_Buy_Info",CCInteger::create(id));
//    }
    
    task_index =-1;
    this->getChildByTag(1)->setVisible(false);
}
void GameLayer::cancleGameLayerTip(CCObject *pSender)
{
     DF_LOG("GameLayer::enterGameLayerTip ");
    isTaskVisable = false;
    
    hit_count =0;
//    if (task_index ==0 && lost_count <= 2048) {
//        lost_count*=2;
//    }
    task_index =-1;
    this->getChildByTag(1)->setVisible(false);
    
}
 void GameLayer::buyPower(CCObject *pSender)
{
    //this->getChildByTag(1)->setVisible(true);
    if (task_index ==-1  ) {
    if(!GameData::getSharedGameData()->isBuyFishKnife())
    {
        if (m_pMine->m_power_max > GameData::getSharedGameData()->currentPower()) {
                    task_index = 0;
                    setTaskInfoPanle(task_index);
            }
    }
    else
    {
        if (GameData::getSharedGameData()->currentPowerCount()<1) {
                    task_index = 0;
                    setTaskInfoPanle(task_index);
        }
        else if(m_pMine->m_power_max > GameData::getSharedGameData()->currentPower())
        {
                    task_index = 0;
                    setTaskInfoPanle(task_index);
        }
    }
    }
//    task_index = 0;
//    setTaskInfoPanle(task_index);
}
void GameLayer::buySuperPower()
{
    //GameData::getSharedGameData()->setCurrentPower(m_pMine->m_power_max);
    //GameData::getSharedGameData()->setCurrentPowerCount(GameData::getSharedGameData()->currentPowerCount()+1);
   
       // lost_count = LOSE_COUNT;
   
    int pPower = GameData::getSharedGameData()->currentPower();
    if(GameData::getSharedGameData()->isBuyFishKnife())
    {
        if(GameData::getSharedGameData()->currentPowerCount()<1)
        GameData::getSharedGameData()->setCurrentPowerCount(1);
        else
        {
           //updateMinePower(m_pMine->m_power_max - pPower);
            GameData::getSharedGameData()->setCurrentPower(m_pMine->m_power_max);
        }
       // updateMinePower(0);
    }
   
    
    //buyGoodSixGift();
    else
    {
        DF_LOG("GameLayer::buySuperPower()1 pPower = %d",pPower);
        
        GameData::getSharedGameData()->setCurrentPower(m_pMine->m_power_max);
        DF_LOG("GameLayer::buySuperPower()2 pPower = %d",pPower);
    }
    updateMinePower(0);
    
}
void GameLayer::buyMaxPower()
{
    GameData* pData= GameData::getSharedGameData();
    pData->addUnLockMaxConnon(true);
    initUnlockItems();
    m_pCannon->incCannonScore();
    
    
    //    CCString* str = CCString::createWithFormat("%d",m_pCannon->cannon_score);
    //    ttf_cannon_score->setString(str->getCString());
    
    Sound::Instance()->playEffect("SwitchSilo.mp3");
    
    removeChildByTag(CannonScoreNumberTag);
    NumSprite *p = NumSprite::create(m_pCannon->cannon_score);
    p->setPosition(CCPoint(m_pCannon->m_pSprite->getPosition().x,2));
    //    p->setScale(0.5f);
    p->setAnchorPoint(CCPoint(0.5,0));
    addChild(p,m_pCannon->m_pSprite->getZOrder(),CannonScoreNumberTag);
    DF_LOG("Cannon buy p=%d",p->getZOrder());
}
void GameLayer::buyVipCard()
{
    DF_LOG("GameLayer::buyVipCard()");
    GameData* pData = GameData::getSharedGameData();
    if (!pData->getIsHaveVipCard()) {
        pData->addVipCard(true);
    }
    //if(pData->getTodayLoginCount() == 2)
    {
        //Sound::Instance()->playEffect("ffcoin.mp3");
        GameData::getSharedGameData()->changeScore(20000);
    }
    
}
void GameLayer::buyUpGradGift()
{
    DF_LOG("GameLayer::buyUpGradGift()");
    GameData* pData = GameData::getSharedGameData();
    pData->provideProduct(Product_UpGradGift);
    m_pCannon->isHideBullet =true;
    updateScoreUI(0);
}
void GameLayer::showUpGradGift()
{
    DF_LOG("GameLayer::showUpGradGift()");
    //add by andy 2015-03-24
    if(task_index == -1)
    {
        task_index = 3;
        setTaskInfoPanle(task_index);
    }
}
void GameLayer::showGoodSixGift()
{
    DF_LOG("GameLayer::showGoodSixGift()");
    //add by andy 2015-03-24
    if(task_index == -1)
    {
        task_index = 5;
        setTaskInfoPanle(task_index);
    }
}
void GameLayer::buyGoodSixGift()
{
    DF_LOG("GameLayer::buyGoodSixGift()");
    //add by andy 2015-03-30
    GameData* pData = GameData::getSharedGameData();
    pData->provideProduct(Product_GoodSixGift);
    m_pCannon->isHideBullet =true;
    updateScoreUI(0);

}
void GameLayer::buyDragonGift()
{
    DF_LOG("GameLayer::buyDragonGift()");
    //add by andy 2015-03-24
    GameData* pData = GameData::getSharedGameData();
    pData->provideProduct(Product_DragonGift);
//    int pToken = arc4random() % 9999;
//    setToken(pToken);
//    setProductType(Product_Fb_Coin10);
//    buyGoods(Product_Fb_Coin10, GameData::getSharedGameData()->genOrderId(Product_Fb_Coin10, pToken).c_str(), pToken);
}
void GameLayer::buyMermaidGift()
{
    DF_LOG("GameLayer::buymMermaidGift()");
    //add by andy 2015-03-24
    GameData* pData = GameData::getSharedGameData();
    pData->provideProduct(Product_MermaidGift);
   updateScoreUI(0);
}
void GameLayer::buyXihaGift()
{
    DF_LOG("GameLayer::buyXihaGift()");
    GameData* pData = GameData::getSharedGameData();
    pData->provideProduct(Product_XihaGift);
}
void GameLayer::setTaskInfoPanle(int index)
{
    DF_LOG("GameLayer::setTaskInfoPanle isLightAnimation=%d",isLightAnimation);
    if (isLightAnimation) {
        return ;
    }
    //ÂΩ????‰ªªÂ?°‰∏∫index
    DF_LOG("GameLayer::setTaskInfoPanle(%d)",index);
    //add by lqg 2015-04-07
    isTaskVisable = true;
    
    CCDictionary* pDict = CCDictionary::createWithContentsOfFile("TaskInfo.plist");
    if (index < 0 || index >6) {
        return ;
    }
    char key[10];
    memset(key, 0, 10);
    sprintf(key, "task_%d",index);
    CCDictionary* pDict_item = (CCDictionary*)pDict->objectForKey(key);
    if (pDict_item) {
        const CCString* describe = pDict_item->valueForKey("describe");
        const CCString* price = pDict_item->valueForKey("price");
        const CCString* title = pDict_item->valueForKey("title");
        const CCString* goods = pDict_item->valueForKey("goods");
        DF_LOG("GameLayer::setTaskInfoPanle describe =%s,price =%s,title=%s",describe->getCString(),price->getCString(),title->getCString());
        CCNode* node = (CCNode*)this->getChildByTag(1);
        ((CCSprite*)node->getChildByTag(1)->getChildByTag(1))->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(title->getCString()));
       ((CCSprite*)node->getChildByTag(1)->getChildByTag(2))->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(describe->getCString()));
        ((CCSprite*)node->getChildByTag(1)->getChildByTag(3))->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(goods->getCString()));
        ((CCLabelTTF*)node->getChildByTag(1)->getChildByTag(4))->setString(price->getCString());
        node->setVisible(true);
        
    }
    
}
void GameLayer::buyTaskSuccess(int id)
{
    isTaskVisable =false;
    //int returnType = ((CCInteger*)ref)->getValue();
    ProductType  GoodsID = (ProductType)id;
        switch (GoodsID) {
            case Product_PowerGift:
            {
                buySuperPower();
            }
                break;
            case Product_MaxCannonGift:
            {
                buyMaxPower();
            }
                break;
            case Product_VIPGift:
            {
                buyVipCard();
            }
                break;
            case Product_UpGradGift:
            {
                buyUpGradGift();
            }
                break;
//            case Product_DragonGift:
//            {
//                buyDragonGift();
//            }
//                break;
//            case Product_MermaidGift:
//            {
//                buyMermaidGift();
//            }
//                break;
            case Product_XihaGift:
            {
                buyXihaGift();
            }
                break;
            case Product_GoodSixGift:
            {
                buyGoodSixGift();
            }
                break;
            default:
                break;
        }
    //首次充值奖励
    if (!(GameData::getSharedGameData()->isInitRecharged())) {
        GameData::getSharedGameData()->doInitRechargedBonus();
        //购买结果通知
        this->onBoughtResultNotify();
        GameData::getSharedGameData()->changeHide(0);
    }
    
}
void GameLayer::buyTask(ProductType id )
{
#ifndef TEST_BAIBAO
    PlatformHandler::getInstance()->pay(id);
#else
    buyTaskSuccess(id);
#endif
}
//void GameLayer::onInitRechargeClicked(CCObject *pSender) {
//    CCScene* sc = InitRechargeLayer::scene();
//    addChild(sc,10, TAG_INIT_RECHARGE_LAYER);
//    
//    GameData::getSharedGameData()->setBootFromInitRecharge(true);
//    Sound::Instance()->playEffect("btn.mp3");
//}

//void GameLayer::leftCallback(cocos2d::CCObject *pSender)
//{
//    Sound::Instance()->playEffect("btn.mp3");
//    m_iHelpIndex--;
//    if (m_iHelpIndex < 0)
//    {
//        m_iHelpIndex = 3;
//    }
//    
//    CCSpriteFrame* pNewFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_HelpFrame[m_iHelpIndex]);
//    m_pHelp->setDisplayFrame(pNewFrame);
//}

//void GameLayer::rightCallback(cocos2d::CCObject *pSender)
//{
//    Sound::Instance()->playEffect("btn.mp3");
//    m_iHelpIndex++;
//    if (m_iHelpIndex >= 4)
//    {
//        m_iHelpIndex = 0;
//    }
//    
//    CCSpriteFrame* pNewFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_HelpFrame[m_iHelpIndex]);
//    m_pHelp->setDisplayFrame(pNewFrame);
//}

//void GameLayer::taskCallback(cocos2d::CCObject *pSender)
//{
//    setMenuEnable(false);
//    TaskDetailLayer::layer(this, m_pMiiTask->getTag());
//}

//void GameLayer::reliefCallback(cocos2d::CCObject *pSender)
//{
//    // ??¬¢?????????????
//    ly_relief->setVisible(false);
//    int pRelief = 10000;
//    if (GameData::getSharedGameData()->currentLevel() > 10)
//    {
//        pRelief = pRelief + GameData::getSharedGameData()->currentLevel() * 1000;
//    }
//    pRelief = pRelief > 99000 ? 99000 : pRelief;
//    // save
//    time_t tt;
//    time(&tt);
//    struct tm *p;
//    p = localtime(&tt);
//    char achTemp[32] = {0};
//    memset(achTemp, 0, sizeof(achTemp));
//    sprintf(achTemp, "%d%d", p->tm_year, p->tm_yday);
//    GameData::getSharedGameData()->saveGameRecordInfo(GameRecordType_Relief, achTemp, 1, new vector<int>());
//
//    updateScoreUI(pRelief);
//}

bool  GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
        //cocos2d??∞‚????????¬±????????????????•¬?????OPenGL??????????•¬???Œ©¬®??? ??????[G7]
        CCPoint pt = pTouch->getLocation();
    isShot = false;
    // ????•√???????????¬©???????????¬∞?
    if (ly_guide->isVisible())
    {
        helpExitSel(NULL);
        return true;
    }
//    sp_gold->AddGold(arc4random()%13 + 2);
    
    if (isMineSelected) {
        m_pMine->startKnife(pt, this);
//        m_pMine->start(pt,ly_fish);
        isMineSelected = false;
        updateUIExp();
        // ??∞¬?¬™???¬∞?????????? ??∞Œ©√∏√??¬Æ??????Œ©???????
        //del by andy 2015-04-27
       // GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_USESPECIALWEAPON, 0, 1);
        return true;
    }
    
    if (pt.y < CCDirector::sharedDirector()->getWinSize().height/10) {
        return false;
    }
        
        //??????????????????????Œ©¬®???????????¬Æ????????????????????????
    isShot = true;
    
    return true;
//    }
}


void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void GameLayer::ccTouchEnded(CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    if (isShot == false || this->getChildByTag(1)->isVisible()) {
        return;
    }
//    this->m_pCannonTop->rotationAndFire(pTouch->getLocation());
    
        bool res = this->m_pCannon->rotationAndFire(pTouch->getLocation());
    if (!res)
    {
//        m_bShowFastBuy += 1;
        if (GameData::getSharedGameData()->score() < 100)
        {
            CCScene* sc = GameStoreLayer::scene(true);
            //    addChild(sc,10);
            addChild(sc, 10, 888);
            if (sc->getChildByTag(888))
            {
                ((GameStoreLayer*)(sc->getChildByTag(888)))->setFastBuyVisible(true);
            }
        }
        else
        {
            while (GameData::getSharedGameData()->score() < m_pCannon->cannon_score && m_pCannon->cannon_score >= 100)
            {
                reduceCannonSize(NULL);
            }
        }
    }
        if (res) {
            if(GameData::getSharedGameData()->getGameType() == GameType_Normal && GameData::getSharedGameData()->addExp(m_pCannon->cannon_score) == true)
            {
                               //add end by andy 2015-03-24
                if (isLightAnimation) {
                    return ;
                }
                addChild(GameUpgradeLayer::scene(),10);
                
                scheduleOnce(schedule_selector(GameLayer::showUpGradGift), 3.0f);
                initUnlockItems();
            }
            updateScoreUI(-m_pCannon->cannon_score);
            updateUIExp();
            if (m_pCannon->m_nCannonType == Laser_Cannon) {
                Sound::Instance()->playEffect("Laser.mp3");
            }else if (m_pCannon->m_nCannonType == Power_Cannon) {
                Sound::Instance()->playEffect("Silo3.mp3");
            }else if (m_pCannon->m_nCannonType == Gold_Cannon2 ||
                      m_pCannon->m_nCannonType == Gold_Cannon3 || m_pCannon->m_nCannonType == Gold_Cannon4) {
                Sound::Instance()->playEffect("Silo2.mp3");
            } else {
                Sound::Instance()->playEffect("Silo1.mp3");
            }
        }
    
//    showMenu(false);
}


void GameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void GameLayer::keyBackClicked()
{
    SeqLoginBonusManager::sharedSeqLoginBonusManager()->setIsSameDay();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(SceneReplaceTime, IntroLayer::scene(), ccBLACK));
    Sound::Instance()->playEffect("btn.mp3");
}

void GameLayer::addFish(){
//    static int i = 0;
//    i++;
    
    /*
    Fish *pfish = Fish::create(this);
//    CCSpriteBatchNode* fishBatch = (CCSpriteBatchNode*)fish_batch_arr->objectAtIndex(pfish->getFishType());
    if (pfish->getFishType() == Fish::FISH_ZHENZHUBEI) {
//        fishBatch->addChild(pfish,-1);
        ly_fish->addChild(pfish,-1);
    } else {
//        fishBatch->addChild(pfish);
        ly_fish->addChild(pfish);
    }
     

    pfish->goFish();
    m_pFishes->addObject(pfish);
     */
    
//    if(i > 30) {
//        
//        Fish *pspec = Fish::createSpecFish(this);
//        ly_fish->addChild(pspec);
//        pspec->goFish();
//        m_pFishes->addObject(pspec);
//        i = 0;
//         
//    }
    
    CCArray *p = NULL;
    // ??¬µ?????????¬Æ¬∞??????¬£?????¢√???????????¬µ???????
//    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Normal || GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
//    {
//        bool pHaveSeaMonster = false;
//        CCObject *pFishObj = NULL;
//        CCARRAY_FOREACH(m_pFishes, pFishObj)
//        {
//            Fish *pFish = (Fish*)pFishObj;
//            if (pFish == NULL)
//            {
//                continue;
//            }
//            if (pFish->getFishType() == Fish::FISH_HAIGUAI)
//            {
//                pHaveSeaMonster = true;
//            }
//        }
//        if (!pHaveSeaMonster)
//        {
//            p = FishGroup::createFishGroup(this, (arc4random()%2)?FishGroup::FishGroupRand:FishGroup::FishGroupLine, Fish::FISH_HAIGUAI);
//        }
//        else
//        {
//            p = FishGroup::createFishGroup(this, (arc4random()%2)?FishGroup::FishGroupRand:FishGroup::FishGroupLine, Fish::FISH_All_TYPEMAX);
//        }
//    }
//    else
//    {
    p = FishGroup::createFishGroup(this, (arc4random()%2)?FishGroup::FishGroupRand:FishGroup::FishGroupLine);
//    }
    
    for(int x=0; x < p->count();x++){
        Fish *pf = (Fish*)(p->objectAtIndex(x));
        if(pf->getFishType() == Fish::FISH_ZHENZHUBEI){
//            ly_fish->addChild(pf,-1);
            getBatchNodeFish()->addChild(pf, -1);
        } else {
//            ly_fish->addChild(pf);
            //edit by lqg 2015-04-09   assert(pf)
            if (NULL != pf) {
                getBatchNodeFish()->addChild(pf);
            }
            
        }
        //edit by lqg 2015-04-09    assert(pf)
        if (NULL != pf) {
            pf->goFish();
            m_pFishes->addObject(pf);
        }
        
    }

}

void GameLayer::updateFish(cocos2d::CCTime dt){
    static int i = 0;
    static int rt[3] = {0,0,0};
    
    if(isFishGeneratorStarted)
    {
        if(i == 0) {
            rt[0] = 20 + arc4random()%20;
            rt[1] = 70 + arc4random()%20;
            rt[2] = 130 + arc4random()%20;
        }
        
//        if(i++ == 4*60*10/7) {
        if (i++ == 150)
        {
            i = 0;
        }
        
        //for special fish
        if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
        {
            if(i == rt[0] || i == rt[1] || i == rt[2]) {
                Fish *pspec = Fish::createSpecFish(this);
                if (pspec->m_spec == Fish::SPEC_YWYQ) {
                    if(lost_count <= 0 )
                    {
                        meiren_count*=2;
                        lost_count = (LOSE_COUNT+1)*meiren_count;
                        //                ly_fish->addChild(pspec);
                        getBatchNodeFish()->addChild(pspec);
                        pspec->goFish();
                        m_pFishes->addObject(pspec);
                    }
                    else
                    {
                        lost_count--;
                    }
                }
                else
                {
                    getBatchNodeFish()->addChild(pspec);
                    pspec->goFish();
                    m_pFishes->addObject(pspec);
                }
                
            }
        }
        //
        if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Normal || GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
        {
            // ??¬£?????¢√????????¬µ??????? ?????¬µ?????????¬™?????¬ß?????????∞‚?????? ??¬∂????????§¬∞√??????????¬∫?? ?????¬™???????????¬∫??
            bool pHaveSeaMonster = false;
            bool pHaveSeaMonsterBomb = false;
            CCObject *pFishObj = NULL;
            CCARRAY_FOREACH(m_pFishes, pFishObj)
            {
                Fish *pFish = (Fish*)pFishObj;
                if (pFish == NULL)
                {
                    continue;
                }
                if (pFish->getFishType() == Fish::FISH_HAIGUAI)
                {
                    pHaveSeaMonster = true;
                }
                if (pFish->getFishType() == Fish::FISH_HGZHADAN)
                {
                    pHaveSeaMonsterBomb = true;
                }
            }
            if (!pHaveSeaMonster)
            {
                Fish *p = Fish::createSpecificFish(this,Fish::FISH_HAIGUAI);
//                ly_fish->addChild(p);
                getBatchNodeFish()->addChild(p);
                p->goFish();
                m_pFishes->addObject(p);
//                CCLog("?????¬™?????¬µ????????¬∫?");
            }
            if (!pHaveSeaMonsterBomb)
            {
//                scheduleOnce(schedule_selector(GameLayer::addSeaMonsterBomb), (arc4random() % 15 + 4));
            }
        }
        if(m_pFishes->count() < MAX_FISH_COUNT)
            addFish();
//        int n = MAX_FISH_COUNT - m_pFishes->count();
//        int nAdd = rand() % n + 1;
//        //??∞√???????∞‚??¬™?????????∞‚?????¬±¬∫???√∏???????????????????
//        for(int i = 0; i < nAdd; i++)
//        {
//            this->addFish();
//        }
    }
}

//??¬∫¬©??????¬¢???¬™??∞‚???????¬±¬∫???√∏??????¬£???¬µ???????
CCRect shrinkRect(CCRect rc, float xr, float yr)
{
    float w = rc.size.width * xr;
    float h = rc.size.height * yr;
    CCPoint pt = ccp(rc.origin.x + rc.size.width * (1.0f - xr) / 2,
                     rc.origin.y + rc.size.height * (1.0f - yr) / 2);
    return CCRectMake(pt.x, pt.y, w, h);
}


void GameLayer::updateScoreUI(int addScore)
{
    //add score
    GameData* gd = GameData::getSharedGameData();
    int score = 0;
    if (gd->getGameType() == GameType_Normal)
    {
        gd->changeScore(addScore);
        score = gd->score();
    }
    else
    {
        gd->addSeaMonsterScore(addScore);
        score = gd->getSeaMonsterScore();
    }
    // ??∞¬?¬™???¬∞?????????? ??????????????????
    //del by andy 2015-04-27
    //GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_GETCOIN, 0, addScore);
    
    m_pRollNumGroup->setValue(score);
//    CCLog("score %d", score);
    
    if (m_pCannon->isHideBullet) {
        sp_hidebullet->setVisible(true);
        
//        sp_hidebullet->removeChildByTag(69);
//        NumSprite *p = NumSprite::create(gd->hideBulletCount(),GameNumberYingxin);
//        p->setScale(0.6);
//        sp_hidebullet->addChild(p,1,69);
//       p->setAnchorPoint(ttf_hidebullect_cnt->getAnchorPoint());
//        p->setPosition(ttf_hidebullect_cnt->getPosition());
        ttf_hidebullect_cnt->setVisible(true);
        CCString* str  = CCString::createWithFormat("%d",gd->hideBulletCount());
        ttf_hidebullect_cnt->setString(str->getCString());
        //CCString* str = CCString::createWithFormat("%d",gd->hideBulletCount());
        //ttf_hidebullect_cnt->setString(str->getCString());
    } else {
        sp_hidebullet->setVisible(false);
    }
    
    //show add gold?
    if(sp_gold == NULL){
        sp_gold = GoldControl::create();
        
        sp_gold->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/7,CCDirector::sharedDirector()->getVisibleSize().height/17));
        getBatchNodeCoin()->addChild(sp_gold);
    }
    if(addScore >= 15000) {
        if (isLightAnimation) {
            CenterRoll *p = CenterRoll::create(addScore);
            addChild(p);
            p->goAnimation();
        }
        
    } else if(addScore > 5000 && addScore < 15000) {
        sp_gold->AddGold(addScore/1000);
    }
    
    if (score <= 50 && gd->getGameType() == GameType_Normal)
    {
        // ??¬∫???????????????? ???????????√¶??¬ß????????¬µ???????
//        time_t tt;
//        time(&tt);
//        struct tm *p;
//        p = localtime(&tt);
//        char achTemp[32] = {0};
//        memset(achTemp, 0, sizeof(achTemp));
//        sprintf(achTemp, "%d%d", p->tm_year, p->tm_yday);
        
        GameTimesRecord* pRecord = GameData::getSharedGameData()->getGameRecordInfo(GameRecordType_Relief, GameData::getSharedGameData()->genDayStamp());
        
        if (!pRecord || pRecord->times < 1)
        {
            // ??Œ©?????¢√????????¬¢?????????¬µ?
//            ly_relief->setVisible(true);
            // ?????????????????????????????????????
            int pRelief = 10000;
            if (GameData::getSharedGameData()->currentLevel() > 10)
            {
                pRelief = pRelief + GameData::getSharedGameData()->currentLevel() * 1000;
            }
            pRelief = pRelief > 99000 ? 99000 : pRelief;
            char achTemp[32] = {0};
            memset(achTemp, 0, sizeof(achTemp));
            sprintf(achTemp, "%d", pRelief);
//            bmf_reliefCoin->setString(achTemp);
        }
//        setFreezeing(true);
//        addChild(FlipCardBonusLayer::scene(ShortageCoins));
    }
    else if (score <= 50 && (gd->getGameType() == GameType_SeaMonster_Normal || gd->getGameType() == GameType_SeaMonster_Difficulty))
    {
        //TODO ??¬∫???????????¬™?????•√??????????????????????? ??∞‚????????¬¢??????????????????¬™????
    }
}

void GameLayer::syncScoreUI()
{
    GameData* gd = GameData::getSharedGameData();
    m_pRollNumGroup->setValue(gd->score());
}
void GameLayer::syncHideUI()
{
    GameData* gd = GameData::getSharedGameData();
    DF_LOG("gd->hideBulletCount() = %d",gd->hideBulletCount());
    if (gd->hideBulletCount() > 0) {
        if(!m_pCannon->isHideBullet)
         m_pCannon->isHideBullet= true;
        sp_hidebullet->setVisible(true);
        
//        sp_hidebullet->removeChildByTag(69);
//        NumSprite *p = NumSprite::create(gd->hideBulletCount(),GameNumberYingxin);
//        p->setScale(0.6);
//        sp_hidebullet->addChild(p,1,69);
//        p->setAnchorPoint(ttf_hidebullect_cnt->getAnchorPoint());
//        p->setPosition(ttf_hidebullect_cnt->getPosition());
        ttf_hidebullect_cnt->setVisible(true);
        CCString* str  = CCString::createWithFormat("%d",gd->hideBulletCount());
        ttf_hidebullect_cnt->setString(str->getCString());
        DF_LOG("gd->hideBulletCount()   end");
    }
}


void GameLayer::onInitRechargeNotify()
{
    removeChildByTag(TAG_INIT_RECHARGE_LAYER);
    storeGameLayerSel(NULL);
    
}

void GameLayer::onBoughtResultNotify()
{
    updateUIExp();
    updateScoreUI(0);
    
}


void GameLayer::updateMinePower(int addPower)
{
    if (isMineSelected == true) {
        return;
    }
    m_pMine->addPower(addPower);
    updateUIExp();
    int pPower = 0;
    int pCount = 0;
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        pPower = GameData::getSharedGameData()->currentPower();
        pCount = GameData::getSharedGameData()->currentPowerCount();
    }
    else
    {
        pPower = GameData::getSharedGameData()->getSeaMonsterPower();
        pCount = GameData::getSharedGameData()->getSeaMonsterPowerCount();
    }
    DF_LOG("pPower =%d, pCount =%d",pPower,pCount);
//    if (pPower >= m_pMine->m_power_max)
   if (GameData::getSharedGameData()->isBuyFishKnife())  //????????¬•???∞œ??????????????¬µ??????¬£?
    {
//        if(pCount == 0 && pPower >= m_pMine->m_power_max)
//        {
//            pCount =1;
//            pPower = 0;
//            GameData::getSharedGameData()->setCurrentPower(pPower);
//            //GameData::getSharedGameData()->setCurrentPowerCount(pCount);
//        }
        if (pCount > 0 )
        {
            if (!bn_mine->isVisible())
            {
                bn_mine->setVisible(true);
                bn_mine->runAction(CCMoveTo::create(0.5f, CCPoint(bn_mine->getPositionX(), bn_mine->getContentSize().height/2)));
                bn_mine_ele->setVisible(true);
                bn_mine_ele->runAction(CCMoveTo::create(1.0f, CCPoint(bn_mine_ele->getPositionX(), bn_mine_ele->getContentSize().height / 2 + bn_mine->getContentSize().height)));
            }
            DF_LOG("pPower =%d, pCount =%d",pPower,pCount);
            if (pPower >= m_pMine->m_power_max )
            {
//                int frameCnt = 6;
//                CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
//                DF_LOG("CCARRAY 1 aniframe =%d",aniframe);
//                for(int i=0;i <frameCnt;i++)
//                {
//                    CCString *frameName=CCString::createWithFormat("power_%d.png",i);
//                    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
//                    aniframe->addObject(frame);//?????????????∞‚??????????????§√???¬µ???¬Æ???¬™?????¬™?????????????????????
//                }
//                float frameIterval = 0.12f;
//                CCAnimation* pAnimation = CCAnimation::createWithSpriteFrames(aniframe,frameIterval);//?????√∏????????????¬™??????¬Æ????
//                CCAnimate *animate=CCAnimate::create(pAnimation);
//                sp_power->setScaleX(1);
//                sp_power->runAction(CCRepeat::create(animate, 1000));
                sp_scoreboard->getChildByTag(1)->setVisible(true);
                bn_power->setVisible(false);
            }
            else
            {
                CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_power.png");
                //sp_power->stopAllActions();
                sp_power->setDisplayFrame(spFram);
            }
        }
        else
        {
            bn_mine->setVisible(false);
            bn_mine->setPositionY(-bn_mine->getContentSize().height/2);
            bn_mine_ele->setVisible(false);
            bn_mine_ele->setPositionY(bn_mine->getPositionY());
            CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_power.png");
            //sp_power->stopAllActions();
            sp_power->setDisplayFrame(spFram);
            sp_scoreboard->getChildByTag(1)->setVisible(false);
            bn_power->setVisible(true);

        }
    }
    else
    {
        if (pPower >= m_pMine->m_power_max)
        {
            if (!bn_mine_ele->isVisible())
            {
                bn_mine_ele->setVisible(true);
                bn_mine_ele->runAction(CCMoveTo::create(1.0f, CCPoint(bn_mine_ele->getPositionX(), bn_mine_ele->getContentSize().height / 2)));
            }
//            int frameCnt = 6;
//            CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
//            DF_LOG("CCARRAY 2 aniframe =%d",aniframe);
//            for(int i=0;i <frameCnt;i++)
//            {
//                CCString *frameName=CCString::createWithFormat("power_%d.png",i);
//                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
//                aniframe->addObject(frame);//?????????????∞‚??????????????§√???¬µ???¬Æ???¬™?????¬™?????????????????????
//            }
//            float frameIterval = 0.12f;
//            CCAnimation* pAnimation = CCAnimation::createWithSpriteFrames(aniframe,frameIterval);//?????√∏????????????¬™??????¬Æ????
//            CCAnimate *animate=CCAnimate::create(pAnimation);
//            sp_power->setScaleX(1);
//            sp_power->runAction(CCRepeat::create(animate, 1000));
            sp_scoreboard->getChildByTag(1)->setVisible(true);
            bn_power->setVisible(false);
            
        }
        else
        {
            bn_mine_ele->setVisible(false);
            bn_mine_ele->setPositionY(-bn_mine_ele->getContentSize().height/2);
            CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_power.png");
           // sp_power->stopAllActions();
            sp_power->setDisplayFrame(spFram);
            sp_scoreboard->getChildByTag(1)->setVisible(false);
            bn_power->setVisible(true);
        }
    }
    float power = (float)pPower / m_pMine->m_power_max;
    //DF_LOG("float power(%d) = (float)pPower(%d) ",power,pPower);
    sp_power->setScaleX(power);
    sp_power_active->stopAllActions();
    sp_power_active->setVisible(false);
    sp_power_active->setPosition(CCPoint((sp_power->getPositionX() + sp_power->getContentSize().width * power), sp_power->getPositionY()));
    sp_power_active->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(0.5f),CCHide::create(),NULL));
}



void GameLayer::updateUIExp()
{
    static int lastLevel = 0;
    GameData* gd = GameData::getSharedGameData();
    CCString* str = CCString::createWithFormat("%d",gd->currentLevel());
    if(gd->currentLevel() != lastLevel)
    {
//        CCSprite *pc = (CCSprite*)CCSprite::create();
//        char str[32];
//        bzero(str,sizeof(str));
//        CCArray *aniframe = CCArray::createWithCapacity(11);
//        
//        for(int i=0;i <11;i++){
//            sprintf(str,"lihua_%d.png",i);  //?????√∏???∞‚????????¬Æ?????????¬™???????§√????
//            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//            aniframe->addObject(frame);
//        }
//        CCAnimation * pa = CCAnimation::createWithSpriteFrames(aniframe,0.1);//?????√∏????????????¬™??????¬Æ????
        
//        CCAnimate *animate=CCAnimate::create(pa);
//        CCFiniteTimeAction *callFunc = CCCallFunc::create(pc, callfunc_selector(CCSprite::removeFromParent));
//        CCFiniteTimeAction *action = CCSequence::create(animate,callFunc,NULL);
        //ttf_cannon_score->runAction(action);
//        ttf_cannon_score->addChild(pc,1,9999);
//        CCSize s = ttf_cannon_score->getContentSize();
//        pc->setPosition(ccp(s.width/2,s.height/2));
//        pc->setAnchorPoint(ccp(0.5,0.5));
//        pc->runAction(action);
        lastLevel = gd->currentLevel();
    }
//    removeChildByTag(ExpNumberTag);
//    NumSprite *_p = NumSprite::create(gd->currentLevel());
//    
//    _p->setPosition(ttf_cannon_score->getPosition());
//    //    p->setScale(0.5f);
//    _p->setAnchorPoint(CCPoint(0.5,0.5));
//    addChild(_p,ttf_cannon_score->getZOrder()+10,ExpNumberTag);
   // ttf_cannon_score->setVisible(false);
    ttf_cannon_score->setString(str->getCString());
    
    //ttf_player_level->setString(gd->getTitleForLevel(gd->currentLevel())->getCString());
    //ttf_player_level->setFontName("??√∏??????????????????¬Æ?");
    
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(gd->getPicForLevel(gd->currentLevel())->getCString());
    DF_LOG("updateUIExp   frame =%x, %s",frame,gd->getPicForLevel(gd->currentLevel())->getCString());
    ttf_player_level->setDisplayFrame(frame);
    
    if (gd->nextLevel() != NULL) {
        float rate = (float)gd->currentExp() / (float)gd->nextLevel()->m_expForUpgrade;
        sp_user_exp->setScaleX(rate);
        
        sp_user_exp_active->stopAllActions();
        sp_user_exp_active->setVisible(false);
        sp_user_exp_active->setPosition(CCPoint((sp_user_exp->getPositionX() + sp_user_exp->getContentSize().width * rate), sp_user_exp_active->getPositionY()));
        sp_user_exp_active->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(0.5f),CCHide::create(),NULL));
    } else {
        sp_user_exp->setScaleX(1.0);
    }
    
    if (GameData::getSharedGameData()->doubleTimeExp() > 0) {
        sp_exp_double->setVisible(true);
        sp_power_count->setPositionX(sp_exp_double->getPositionX() + sp_exp_double->getContentSize().width);
        GameData::getSharedGameData()->setDoubleTimeExp(GameData::getSharedGameData()->doubleTimeExp()-1);
    } else {
        sp_exp_double->setVisible(false);
        sp_power_count->setPosition(sp_exp_double->getPosition());
    }
    
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        sp_power_count->setVisible(GameData::getSharedGameData()->currentPowerCount() > 0);
    }
    else
    {
        sp_power_count->setVisible(GameData::getSharedGameData()->getSeaMonsterPowerCount() > 0);
    }
}


void GameLayer::catchFish(Fish *pFish, FatherBullet *p)
{
    
    //                pFish->showCaught();
    //pFish->removeFromParentAndCleanup(true);
    int earn_score = pFish->attackFish(p);
    //add by andy 2015-03-24
//    if(earn_score >0)
//    {
//        switch (pFish->m_fishType) {
//            //    case Fish::FISH_XIAOGUANGYU:
//            case Fish::FISH_HAITUN:     //Â§????Áæ?‰∫∫È±º
//            {
//                if(task_index == -1)
//                {
//                    task_index = 5;
//                    setTaskInfoPanle(task_index);
//                }
//            }
//                break;
//              //  case Fish::FISH_XIAOCAOYU:
//            case Fish::FISH_LANJING:     //Â§????Èæ????
//            {
//                if(task_index == -1)
//                {
//                    task_index = 4;
//                    setTaskInfoPanle(task_index);
//                }
//            }
//                break;
//                
//            default:
//                break;
//        }
//    }
    //del by andy 2015-04-14
    //add end by andy 2015-03-24
    p->totalGetScore += earn_score;
    //if(earn_score >= 0) {
    //    m_pFishes->removeObject(pFish);
    //}
}

void GameLayer::checkMine()
{
    if (m_pMine == NULL) {
        return;
    }
    CCObject *pFishObj = NULL;
    if (m_pMine->m_status == Mine_Ready) {
        CCARRAY_FOREACH(m_pFishes, pFishObj)
        {
            Fish *pFish = (Fish *)pFishObj;
            
            if (pFish == NULL) {
                continue;
            }
            //            if(pFish->getCaught())
            //                continue;
            
            CCRect hittestRect = shrinkRect(pFish->boundingBox(), HIT_PERCENTAGE*(1.6f), HIT_PERCENTAGE);
            //            CCRect hittestRect = pFish->boundingBox();
            
            if(hittestRect.intersectsRect(shrinkRect(m_pMine->m_sprite->boundingBox(),3,3)))
            {
                m_pMine->bomb();
                Sound::Instance()->playEffect("bomb0.mp3");
            }
        }
    }
    if (m_pMine->m_status == Mine_Bomb) {
        CCARRAY_FOREACH(m_pFishes, pFishObj)
        {
            Fish *pFish = (Fish *)pFishObj;
            
            if (pFish == NULL) {
                continue;
            }
            //            if(pFish->getCaught())
            //                continue;
            
            CCRect hittestRect = shrinkRect(pFish->boundingBox(), HIT_PERCENTAGE*(1.6f), HIT_PERCENTAGE);
            //            CCRect hittestRect = pFish->boundingBox();
            
            if(hittestRect.intersectsRect(shrinkRect(m_pMine->m_sprite->boundingBox(),3,3)))
            {
                if(pFish->m_spec == Fish::SPEC_NONE) {
                    this->catchFish(pFish,m_pMine);
                }
                
            }
        }
        
        m_pMine->m_status = Mine_End;
        
        updateScoreUI(m_pMine->totalGetScore);
        

    }

}

void GameLayer::checkBullet()
{
    CCObject *pFishObj = NULL;
    CCObject *pBulletObj = NULL;
    
    CCARRAY_FOREACH(m_pBullets, pBulletObj)
    {
        Bullet *pBullet = (Bullet *)pBulletObj;
        CCRect _bulletRect = pBullet->boundingBox();
        if (pBullet->m_status == Bullet_Fly) {
            CCARRAY_FOREACH(m_pFishes, pFishObj)
            {
                Fish *pFish = (Fish *)pFishObj;
                
                if (pFish == NULL) {
                    continue;
                }
                //            if(pFish->getCaught())
                //                continue;


                 CCRect hittestRect = shrinkRect(pFish->boundingBox(), HIT_PERCENTAGE, HIT_PERCENTAGE);

               
                //            CCRect hittestRect = pFish->boundingBox();
               CCRect bulletRect = shrinkRect(pBullet->boundingBox(), 0.5f, 0.5f);
                //CCRect bulletRect = pBullet->boundingBox();
                
                if(hittestRect.intersectsRect(bulletRect))     //??§Ê??????????ª‰∏≠È±?
                {
                    if (pBullet->getBulletType() == Laser_Cannon || pBullet->getBulletType() == Knife_Cannon || pBullet->isAP())
                    {
                        if(isCCSpriteInterset(pBullet, pFish))
                        {
                            this->catchFish(pFish, pBullet);
                            updateScoreUI(pBullet->totalGetScore);
                            if (pBullet->getBulletType() != Knife_Cannon)
                            {
                                if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
                                {
                                    updateMinePower(pBullet->totalGetScore/m_pCannon->cannon_score);
                                }
                                else
                                {
                                    updateMinePower(pBullet->totalGetScore/m_pCannon->cannon_score * 5);
                                }
                            }
                            pBullet->totalGetScore = 0;
                            
                        }
                    }
                    else      //??ª‰∏≠
                    {
                        pBullet->showNet();
                    }
                }
                
            }
        }
        
        if(pBullet->m_status == Bullet_Net)
        {
            CCARRAY_FOREACH(m_pFishes, pFishObj)
            {
                Fish *pFish = (Fish *)pFishObj;
                //            if(pFish->getCaught())
                //                continue;
                //test by andy 2015-04-09
               // CCRect hittestRect = shrinkRect(pFish->boundingBox(), 0.5f, 0.5f);
                //            CCRect hittestRect = pFish->boundingBox();
               // CCRect netRect = shrinkRect(pBullet->getSpriteNet()->boundingBox(), 0.5f, 0.5f);
                 CCRect hittestRect = shrinkRect(pFish->boundingBox(), HIT_PERCENTAGE, HIT_PERCENTAGE);
               
                 CCRect netRect = shrinkRect(pBullet->getSpriteNet()->boundingBox(), HIT_PERCENTAGE, HIT_PERCENTAGE);
                if(hittestRect.intersectsRect(netRect))
                {
                    this->catchFish(pFish,pBullet);
                }
            }
            
            
            pBullet->m_status = Bullet_End;
            
            updateScoreUI(pBullet->totalGetScore);
            
            
            if (pBullet->getBulletType() != Ele_Cannon)
            {
                updateMinePower(pBullet->totalGetScore/m_pCannon->cannon_score);
                //add by andy 2015-03-23
                if (0 == pBullet->totalGetScore)   //not catch Fish
                {
                    hit_count++;
                    DF_LOG("GameLayer::checkBullet() hit_count = %d",hit_count);
                }
                else
                {
                    hit_count =0;
                    DF_LOG("GameLayer::checkBullet() hit_count = %d",hit_count);
                }
                
               // if (hit_count >lost_count)   //is long time not catch fish
                //{
                    //DF_LOG("LOSE_COUNT = %d",lost_count);
                    //this->getChildByTag(1)->setVisible(true);
                    //del by andy 2015-04-17
//                    if (task_index ==-1  ) {
//                        if(!GameData::getSharedGameData()->isBuyFishKnife())
//                        {
//                            if (m_pMine->m_power_max > GameData::getSharedGameData()->currentPower()) {
//                                task_index = 0;
//                                setTaskInfoPanle(task_index);
//                            }
//                        }
//                        else
//                        {
//                            if (GameData::getSharedGameData()->currentPowerCount()<2) {
//                                task_index = 0;
//                                setTaskInfoPanle(task_index);
//                            }
//                            else if(m_pMine->m_power_max > GameData::getSharedGameData()->currentPower())
//                            {
//                                task_index = 0;
//                                setTaskInfoPanle(task_index);
//                            }
//                        }
//                        
//
//                    }

               // }
            }
            
        }
    }

}


void GameLayer::updateGame(cocos2d::CCTime dt){
    
    this->checkMine();
    
    this->checkBullet();
}



void GameLayer::startRollLottery ()
{
    int _roll[10] = {
        8,// ?????¬¢???????
        16,// ?????Œ©¬¢????
        12,// ?????¬•????
        8,// ??¬™√∏???????
        4,// 50000
        8,// ??¬™?????????
        10,// 30000
        14,// 1????????????????????¬™???????
        8,// ???????????
        12,// 15000
    };
    int total = 4+8*4+10+12*2+14+16;
    
    CCMoveTo* wheelMove = CCMoveTo::create(1.0f, CCPointZero);
    
    ly_wheel->runAction(wheelMove);
    
    int prizeCount = 10;
    //int index = arc4random()%prizeCount;
    
    int cur = arc4random()%total;
    int index = 0;
    for(index=0; index < 10; index++) {
        if(cur < _roll[index]){
            break;
        }
        cur -= _roll[index];
    }
    
    float rotateAngle =  index * (360.0f/prizeCount) + 360.0f*5;
    
    CCRotateBy *rotate = CCRotateBy::create(4, rotateAngle);
    CCEaseInOut *next = CCEaseInOut::create(rotate, 3);
    Sound::Instance()->playEffect("Lunpan.mp3");
    
    CCRotateTo *rotateTo = CCRotateTo::create(0.001f, 0.0f);
    // CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(LotteryLayer::rollLotteryResult));
    
    CCCallFuncND *callFunc = CCCallFuncND::create((CCObject*)this, callfuncND_selector(GameLayer::endRollLottery), (void*)index);
    CCCallFuncN *endSound = CCCallFuncN::create((CCObject*)this, callfuncN_selector(GameLayer::lotteryEndSound));
    
    
    CCFiniteTimeAction *seq = CCSequence::create(rotateTo, CCDelayTime::create(1.2f),next,endSound,CCDelayTime::create(0.1f), callFunc, NULL);
    sp_wheel->runAction(seq);
}

void GameLayer::lotteryEndSound()
{
    Sound::Instance()->playEffect("Lunpanover.mp3");
}


void GameLayer::endRollLottery (CCNode* aObj, void* index)
{
    CCMoveBy* wheelMove = CCMoveBy::create(1.0f,CCPoint(0, -ly_wheel->getContentSize().height/4));
    ly_wheel->runAction(wheelMove);
    
//    GameAwardType awardType;
    
    int PrizeIndex = (int)index;
    switch (PrizeIndex)
    {
        case 0:
            //red diamond 1
        {
            GameDiamond* dia = GameData::getSharedGameData()->getGameDiamond(Diamond_Red);
            dia->m_cnt++;
            GameData::getSharedGameData()->saveGameDiamond(dia->m_type);
            
            showAward(GameAwardOneDiamondRed);
        }
            break;
        case 1:
            //hide bullets 100
            GameData::getSharedGameData()->setHideBulletCount(GameData::getSharedGameData()->hideBulletCount()+100);
            updateScoreUI(0);
            
//            awardType = GameAwardHideBullet;
            break;
        case 2:
            //mine power max
            if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
            {
//                GameData::getSharedGameData()->setCurrentPower(m_pMine->m_power_max);
            	bool pAddSuccess = GameData::getSharedGameData()->setCurrentPowerCount(GameData::getSharedGameData()->currentPowerCount() + 1);
            	if (!pAddSuccess)
            	{
            		GameData::getSharedGameData()->setCurrentPower(m_pMine->m_power_max);
            	}
            	GameData::getSharedGameData()->save();
            }
            else
            {
            	bool pAddSuccess = GameData::getSharedGameData()->setSeaMonsterPowerCount(GameData::getSharedGameData()->getSeaMonsterPowerCount() + 1);
            	if (!pAddSuccess)
            	{
            		GameData::getSharedGameData()->setSeaMonsterPower(m_pMine->m_power_max);
            	}
            }
            updateMinePower(0);
            
//            awardType = GameAwardOneMine;
            break;
        case 3:
            //green diamond 1
        {
            GameDiamond* dia = GameData::getSharedGameData()->getGameDiamond(Diamond_Green);
            dia->m_cnt++;
            GameData::getSharedGameData()->saveGameDiamond(dia->m_type);
            
            showAward(GameAwardOneDiamondGreen);
        }
            break;
        case 4:
            //coins 50000
        {
            updateScoreUI(50000);
//            awardType = GameAwardCoin50000;
        }
            break;
        case 5:
            //yellow diamond 1
        {
            GameDiamond* dia = GameData::getSharedGameData()->getGameDiamond(Diamond_Yellow);
            dia->m_cnt++;
            GameData::getSharedGameData()->saveGameDiamond(dia->m_type);
            
            showAward(GameAwardOneDiamondYellow);
        }
            break;
        case 6:
            //coins 30000
        {
            updateScoreUI(30000);
//            awardType = GameAwardCoin30000;
        }
            break;
        case 7:
            //exp double for an hour
            GameData::getSharedGameData()->setDoubleTimeExp(GameData::getSharedGameData()->doubleTimeExp() + 3600);
            updateUIExp();
            
//            awardType = GameAwardDoubleExp;
            break;
        case 8:
            //blue diamond 1
        {
            GameDiamond* dia = GameData::getSharedGameData()->getGameDiamond(Diamond_Blue);
            dia->m_cnt++;
            GameData::getSharedGameData()->saveGameDiamond(dia->m_type);
            
            showAward(GameAwardOneDiamondBlue);
        }
            break;
        case 9:
            //coins 15000
        {
            updateScoreUI(15000);
//            awardType = GameAwardCoin15000;
        }
            break;
        default:
            break;
    }
}


void GameLayer::showAward(GameAwardType aType)
{
    CCScene* sc = GameAwardLayer::scene();
    GameAwardLayer* aLayer = (GameAwardLayer*)sc->getChildByTag(DefaultLayerTag);
    aLayer->setAwardType(aType);
    
    Sound::Instance()->playEffect("addYB.mp3");
    
    addChild(sc,10);
}

void GameLayer::startLaser(bool isForce)
{
    if (cd_cannon == 0 && !isForce) {
        CCLog("Laser is in CD");
        return;
    }
    m_pCannon->startSpecCannon(Laser_Cannon);
    
    sp_laserbullet->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jiguangpao.png"));
        sp_laserbullet->setVisible(true);
    sp_laserbullet->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.4),CCFadeIn::create(0.4),NULL)));
    
    CCString* str = CCString::createWithFormat("%d",m_pCannon->SpecLeftTime);
    ttf_laserbullet_cnt->setString(str->getCString());
    ttf_laserbullet_cnt->setVisible(true);
    
    this->schedule(schedule_selector(GameLayer::updateLaserOrPower), 1.0f);
    this->scheduleOnce(schedule_selector(GameLayer::updateCannonCD), cd_cannon);
    cd_cannon = 0;
}


void GameLayer::startPower(bool isForce)
{
    if (cd_cannon == 0 && !isForce) {
        CCLog("Power is in CD");
        return;
    }
        m_pCannon->startSpecCannon(Power_Cannon);
    
    sp_laserbullet->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("nenglianpao.png"));
        sp_laserbullet->setVisible(true);
    sp_laserbullet->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.4),CCFadeIn::create(0.4),NULL)));
    CCString* str = CCString::createWithFormat("%d",m_pCannon->SpecLeftTime);
    ttf_laserbullet_cnt->setString(str->getCString());
    ttf_laserbullet_cnt->setVisible(true);
        this->schedule(schedule_selector(GameLayer::updateLaserOrPower), 1.0f);
        this->scheduleOnce(schedule_selector(GameLayer::updateCannonCD), cd_cannon);
        cd_cannon = 0;
    
}


void GameLayer::updateLaserOrPower()
{
    //??∞¬?¬£??????¬ß???∞‚?????¬™??????∞‚???
    if( isFreezeing() ) {
        CCLog("freeze!!");
        return;
    }
    m_pCannon->SpecLeftTime--;
    
    if (m_pCannon->SpecLeftTime <= 0) {
        this->unschedule(schedule_selector(GameLayer::updateLaserOrPower));
        m_pCannon->endSpecCannon();
        sp_laserbullet->setVisible(false);
    } else {
        CCString* str = CCString::createWithFormat("%d",m_pCannon->SpecLeftTime);
        ttf_laserbullet_cnt->setString(str->getCString());
    }
}


void GameLayer::updateBonus()
{
    // ??¬£?????¢√??????????????????????•√???
    if (GameData::getSharedGameData()->score() < 100)
    {
        sp_coinshort->setVisible(true);
    }
    else
    {
        sp_coinshort->setVisible(false);
    }
    static int leftTime = 60;
    GameCard* pCard = GameData::getSharedGameData()->getGameCard(Card_Shiziyu);
    if (pCard->m_count == 0) {
        return;
    }
    
//    CCString* str = CCString::createWithFormat("%d %d",leftTime/10, leftTime%10);
//    ttf_bonus_time->setString(str->getCString());
   // removeChildByTag(BonusTimeNumberTag);
   // NumSprite *p = NumSprite::create(leftTime,GameNumberGameLayerTime);
   // p->setPosition(ttf_bonus_time->getPosition());
    //    p->setScale(0.5f);
    //    p->setAnchorPoint(CCPoint(0.5,0));
   // addChild(p,ttf_bonus_time->getZOrder()+1,BonusTimeNumberTag);
    ttf_bonus_time->setString(CCString::createWithFormat("%02d",leftTime)->getCString());
    leftTime--;
    if (leftTime <= 0) {
        leftTime = 60;
        int add = 0;
        add = pCard->m_count * 100;
        updateScoreUI(add);
    }
}

void GameLayer::updateGemstoneCD()
{
    cd_gemstone = 15;
}

void GameLayer::updateCannonCD()
{
    cd_cannon = 3 * 50;
}

void GameLayer::dropGemstone(DiamondType type)
{
    if (cd_gemstone) {
        showAward((GameAwardType)type);
        GameData::getSharedGameData()->addGameDiamond(type, 1);
        // ??∞¬?¬™???¬∞?????????? ?????????????????
        //del by andy 2015-04-27
        //GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_GETGEMSTONE, (int)type, 1);
        
        this->schedule(schedule_selector(GameLayer::updateGemstoneCD), cd_gemstone, 1, 0);
        cd_gemstone = 0;
    }
}


void GameLayer::fillUIElements() {

//    isInitRecharged = GameData::getSharedGameData()->isInitRecharged();
    
    //??¬∂????????§¬∞√????????????????¬ß??∞¬?¬™??¬∞?????¬±??∞Œ©√∏√???,?????∞œ????????
//    cb_btnInitRecharge->setVisible(!isInitRecharged);
//    cb_btnInitRecharge->setEnabled(!isInitRecharged);
    
    CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tool_power.png");
    sp_power->stopAllActions();
    sp_power->setDisplayFrame(spFram);
    float power = 0;
    int pCount = 0;
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        power = (float)GameData::getSharedGameData()->currentPower()/m_pMine->m_power_max;
        pCount = GameData::getSharedGameData()->currentPowerCount();
    }
    else
    {
        // ??¬µ?????????¬Æ¬∞??????∞Œ©√∏√??¬Æ???????????????????Œ©????
        power = (float)GameData::getSharedGameData()->getSeaMonsterPower() / m_pMine->m_power_max;
        pCount = GameData::getSharedGameData()->getSeaMonsterPowerCount();
    }
    sp_power->setScaleX(power);
    if(pCount >= 1 || power >= 1) {
        updateMinePower(0);
    }
    sp_power_active->stopAllActions();
    sp_power_active->setVisible(false);
    sp_power_active->setPosition(CCPoint((sp_power->getPositionX() + sp_power->getContentSize().width * power), sp_power->getPositionY()));
    sp_power_active->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(0.5f),CCHide::create(),NULL));
}


void GameLayer::generateBombFish() {
    if(Fish::isFishLocked(Fish::FISH_ZHADANFISH))
       return;
    Fish *p = Fish::createSpecificFish(this,Fish::FISH_ZHADANFISH);
//    ly_fish->addChild(p);
    getBatchNodeFish()->addChild(p);
    p->goFish();
    m_pFishes->addObject(p);
}

void GameLayer::startEle()
{
    this->unschedule(schedule_selector(GameLayer::addEle));
    this->schedule(schedule_selector(GameLayer::addEle), 0.25, 36, 0);
}

void GameLayer::addEle()
{
    m_pMine->addEle();
}



//void GameLayer::updateSeaMonsterTime(float delta)
//{
//    //??¬•???????????????? ??¬£????Boss?????????
//    if (GameData::getSharedGameData()->getSeaMonsterTime() > 0)
//    {
//        GameData::getSharedGameData()->addSeaMonsterTime(-1);
//        char achTemp[32] = {0};
//        memset(achTemp, 0, sizeof(achTemp));
//        sprintf(achTemp, "%d", GameData::getSharedGameData()->getSeaMonsterTime());
//        ttf_seamonster_time->setString(achTemp);
//    }
//    else
//    {
//        setMenuEnable(false);
//        // ??√¶??¬ß?????¬™??????????
//        if (GameData::getSharedGameData()->getSeaMonsterBlood() > 0)
//        {
//            sp_seamonster_result->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("haiguailose.png"));
//            sp_seamonster_result->setVisible(true);
//        }
//        else
//        {
//            sp_seamonster_result->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("haiguaiwin.png"));
//            sp_seamonster_result->cocos2d::CCNode::setVisible(true);
//        }
//        scheduleOnce(schedule_selector(GameLayer::exitGameLayerSel), 3);
//    }
//}

//void GameLayer::addSeaMonsterBlood(float delta)
//{
//    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
//    {
//        if ((GameData::getSharedGameData()->getSeaMonsterBlood() + 100) < 15000)
//        {
//            GameData::getSharedGameData()->addSeaMonsterBlood(100);
//            CCLog("??¬µ????????????¬∞?");
//        }
//    }
//}

//void GameLayer::addSeaMonsterBomb(float delta)
//{
//    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
//    {
//        Fish *p = Fish::createSpecificFish(this, Fish::FISH_HGZHADAN);
//        ly_fish->addChild(p);
//        p->goFish();
//        m_pFishes->addObject(p);
//        CCLog("?????¬™???????????¬∫??");
//    }
//}

//void GameLayer::onGetDamage()
//{
//    float pProgress = 1.0;
//    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Normal)
//    {
//        pProgress = (float)GameData::getSharedGameData()->getSeaMonsterBlood() / (float)120000;
//    }
//    else if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
//    {
//        pProgress = (float)GameData::getSharedGameData()->getSeaMonsterBlood() / (float)150000;
//    }
//    //
//    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Normal || GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
//    {
//        if (GameData::getSharedGameData()->getSeaMonsterBlood() <= 0)
//        {
//            setMenuEnable(false);
//            sp_seamonster_result->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("haiguaiwin.png"));
//            sp_seamonster_result->cocos2d::CCNode::setVisible(true);
//            scheduleOnce(schedule_selector(GameLayer::exitGameLayerSel), 3);
//        }
//    }
//    sp_seamonster_blood->setScaleX(pProgress);
////    CCLog(" blood progress %f", pProgress);
//}

//void GameLayer::checkTask()
//{
//    // ??¬£?????¢√???????????∞¬?¬™???¬∞???√¶??¬ß???
//    GameTask* pTask = GameData::getSharedGameData()->getGameTaskIn();
//    if (pTask)
//    {
//        // updateUi
//        const TaskCfg* pTaskCfg = CConfig::sharedConfig()->getTask(pTask->m_id);
//        if (pTaskCfg)
//        {
//            char achTemp[32] = {0};
//            memset(achTemp, 0, sizeof(achTemp));
//            //icon
//            sprintf(achTemp, "%s.png", pTaskCfg->icon.c_str());
//            m_sTaskIcon->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(achTemp));
//            m_pMiiTask->setTag(pTaskCfg->id);
//            //progress
//            if (pTaskCfg->require.size() > 0)
//            {
//                TaskRequire* pRequire = pTaskCfg->require.at(0);
//                sprintf(achTemp, "%d/%d", pTask->m_progress, pRequire->quantity);
//                bmf_taskprogress->setString(achTemp);
//            }
//            else
//            {
//                bmf_taskprogress->setString("0/0");
//            }
//            //countDown
//            schedule(schedule_selector(GameLayer::taskCountDown), 1);
//            ly_task->setVisible(true);
//        }
//    }
//    else
//    {
//        ly_task->setVisible(false);
//        srand(time(NULL));
//        int pRefreshTime = rand() % 12 + 24;
//        CCLog("refresh task time !");
//        this->scheduleOnce(schedule_selector(GameLayer::checkAddTask), pRefreshTime);
//    }
//}

//void GameLayer::checkAddTask(float delta)
//{
//    GameData::getSharedGameData()->checkAddTask(0);
//    // ??√¶??¬ß?????∞¬?¬™????
//    checkTask();
//}

//void GameLayer::checkAddSpecifiedTask(int difficulty)
//{
//    GameData::getSharedGameData()->checkAddTask(difficulty);
//    // ??√¶??¬ß?????∞¬?¬™????
//    checkTask();
//}

//void GameLayer::taskCountDown(float delta)
//{
//    GameTask* pTask = GameData::getSharedGameData()->getGameTaskIn();
//    if (pTask)
//    {
//        const TaskCfg* pTaskCfg = CConfig::sharedConfig()->getTask(pTask->m_id);
//        if (pTaskCfg)
//        {
//            // ??¬£?????¢‚?∞¬?¬™??¬∞?????????????
//            if (pTaskCfg->require.size() > 0 && pTask->m_progress < pTaskCfg->require.at(0)->quantity)
//            {
//                // ??∞¬?¬™???¬∞????????????
//                int pRemainTime = pTaskCfg->time - (CConfig::secondNow() - pTask->m_time);
//                if (pRemainTime > 0)
//                {
//                    char achTemp[32] = {0};
//                    memset(achTemp, 0, sizeof(achTemp));
//                    // ??¬•??????????????????√¶??¬ß???
//                    if (pTaskCfg->require.size() > 0)
//                    {
//                        sprintf(achTemp, "%d/%d", pTask->m_progress, pTaskCfg->require.at(0)->quantity);
//                        bmf_taskprogress->setString(achTemp);
//                    }
//                    // ??¬•?????????√¶??¬ß??????????¬∞????????????????
//                    int pMinute = pRemainTime % 3600 / 60;
//                    int pSecond = pRemainTime % 3600 % 60;
//                    sprintf(achTemp, "%d:%d", pMinute, pSecond);
//                    bmf_tasktime->setString(achTemp);
//                    return;
//                }
//                else
//                {
//                    // ?????¬ß??∞¬?¬™???
//                    GameData::getSharedGameData()->saveGameTask(pTask->m_id, 0, 0, pTask->m_time);
//                }
//            }
//            else
//            {
//                // ??∞¬?¬™???¬∞??????? ??¬™???¬©?????????????
//                for (int i = 0; i < pTaskCfg->reward.size(); i++)
//                {
//                    switch (pTaskCfg->reward.at(i)->type)
//                    {
//                        case TASK_REWARD_EXPPER:
//                        {
//                            // ??¬¢??????√¶?????????
//                            if (GameData::getSharedGameData()->addExp((int)(GameData::getSharedGameData()->nextLevel()->m_expForUpgrade * pTaskCfg->reward.at(i)->quantity / 100)))
//                            {
//                                addChild(GameUpgradeLayer::scene(),10);
//                                initUnlockItems();
//                            }
//                            break;
//                        }
//                        case TASK_REWARD_EXP:
//                        {
//                            // ??¬¢??????¬™???????
//                            if (GameData::getSharedGameData()->addExp((int)pTaskCfg->reward.at(i)->quantity))
//                            {
//                                addChild(GameUpgradeLayer::scene(),10);
//                                initUnlockItems();
//                            }
//                            break;
//                        }
//                        case TASK_REWARD_COIN:
//                        {
//                            // ??¬¢?????????????
//                            updateScoreUI((int)pTaskCfg->reward.at(i)->quantity);
//                            break;
//                        }
//                        case TASK_REWARD_BLACKPEARL:
//                        {
//                            // ??¬¢??????¬™???????
//                            GameData::getSharedGameData()->addGameDiamond(Diamond_BlackPearl, (int)pTaskCfg->reward.at(i)->quantity);
//                            break;
//                        }
//                        case TASK_REWARD_DIAMOND:
//                        {
//                            // ??¬¢??????¬™????
//                            GameData::getSharedGameData()->addGameDiamond(Diamond_Diamond, (int)pTaskCfg->reward.at(i)->quantity);
//                            break;
//                        }
//                        default:
//                            break;
//                    }
//                }
//                // ?????¬ß??∞¬?¬™???
//                GameData::getSharedGameData()->saveGameTask(pTask->m_id, 0, 0, pTask->m_time);
//            }
//            // ??¬¢???????????????∞¬?¬™???¬∞???¬∞????
//            ly_task->setVisible(false);
//            srand(time(NULL));
//            int pRefreshTime = rand() % 24 + 36;
//            this->scheduleOnce(schedule_selector(GameLayer::checkAddTask), pRefreshTime);
//        }
//        else
//        {
//            ly_task->setVisible(false);
//            CCLog("ERRO: task id=%d cfg erro !", pTask->m_id);
//        }
//    }
//    unschedule(schedule_selector(GameLayer::taskCountDown));
//}

void GameLayer::onFlipCardBonusNotify(cocos2d::CCObject *pObj) {
    
    bool bUnFreeze = (bool)pObj;
    setFreezeing(!bUnFreeze);
}


void GameLayer::startFishGenerator(bool start)
{
    isFishGeneratorStarted = start;
    this->scheduleOnce(schedule_selector(GameLayer::prepareSwitchBg), 4*60.0f);
}


void GameLayer::removeFish(Fish *pf)
{
    if(getFishes()) {
        getFishes()->removeObject(pf);
    }
}
void GameLayer::fishdeadCallBack(cocos2d::CCPoint deadPoint)
{
    if (this->getChildByTag(1)->isVisible()) {
        this->getChildByTag(1)->setVisible(false);
        task_index = -1;
    }
    if (this->getChildByTag(10)&&this->getChildByTag(10)->isVisible()) {
        this->getChildByTag(10)->setVisible(false);
        
    }
    DF_LOG("GameLayer::fishdeadCallBack isLightAnimation 1=%d",isLightAnimation);
    isLightAnimation = true;
    DF_LOG("GameLayer::fishdeadCallBack isLightAnimation 2=%d",isLightAnimation);
    CCSprite *p_Sprite = CCSprite::create();
   // p_Sprite->initWithSpriteFrame(pframe_1);
    p_Sprite->setAnchorPoint(ccp(0.5,0.5));
    p_Sprite->setPosition(deadPoint);
    DF_LOG("light1EndCallBack deadPoint.x=%f deadPoint.y=%f",deadPoint.x,deadPoint.y);
    CCCallFuncN * funcall= CCCallFuncN::create(this, callfuncN_selector(GameLayer::light1EndCallBack));
    CCArray *aniframe = CCArray::create();
    for (int i = 0; i<5; i++) {
        CCString* str = CCString::createWithFormat("light1_%d.png",i);
        CCSpriteFrame* pframe_light= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
        if (i == 0) {
            p_Sprite->initWithSpriteFrame(pframe_light);
        }
        aniframe->addObject(pframe_light);
    }
   // aniframe->addObject(pframe_2);
    CCAnimation *animation= CCAnimation::createWithSpriteFrames(aniframe,0.5f);
    animation->setDelayPerUnit(0.5);
    CCFiniteTimeAction* animate = CCAnimate::create(animation);
    
    // CCRepeat::create(animate,1)
    CCFiniteTimeAction * seq= CCSequence::create(animate,funcall,NULL);
    
    
    this->addChild(p_Sprite);
    p_Sprite->setZOrder(this->getChildByTag(1)->getZOrder()+255);
    p_Sprite->runAction(seq);
}
void GameLayer::light1EndCallBack(CCNode* node)
{
    CCPoint point = node->getPosition();
    this->removeChild(node);
    DF_LOG("light1EndCallBack deadPoint.x=%f deadPoint.y=%f",point.x,point.y);
    CCSpriteFrame* pframe_1= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gemLocked.png");
    CCSpriteFrame* pframe_2= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gemUnLocked.png");
    CCSprite *p_Sprite = CCSprite::create();
     p_Sprite->initWithSpriteFrame(pframe_1);
    p_Sprite->setVisible(false);
    p_Sprite->setAnchorPoint(ccp(0.5,0.5));
    p_Sprite->setPosition(point);
    p_Sprite->setScale(0.3);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCActionInterval * move = CCMoveTo::create(1.0, ccp(visibleSize.width / 2, visibleSize.height / 2));
    CCActionInterval * scale = CCScaleTo::create(1.0, 1);
    CCCallFuncN * funcall= CCCallFuncN::create(this, callfuncN_selector(GameLayer::fishdeadEndCallBack));
    CCCallFuncN * funcall_2= CCCallFuncN::create(this, callfuncN_selector(GameLayer::delboxCallBack));
    CCArray *aniframe = CCArray::create();
    aniframe->addObject(pframe_1);
    aniframe->addObject(pframe_2);
 
    CCAnimation *animation= CCAnimation::createWithSpriteFrames(aniframe,0.5f);
    animation->setDelayPerUnit(0.5);
    CCFiniteTimeAction* animate = CCAnimate::create(animation);
    
    CCFiniteTimeAction * spa= CCSpawn::create(move,scale,NULL);
    p_Sprite->setVisible(true);
    // CCRepeat::create(animate,1)
    CCFiniteTimeAction * seq= CCSequence::create(CCDelayTime::create(0.8f),spa,animate,funcall,CCDelayTime::create(1.65f),funcall_2,NULL);
    
    
    this->addChild(p_Sprite);
    p_Sprite->setZOrder(this->getChildByTag(1)->getZOrder()+255);
    p_Sprite->runAction(seq);
}
void GameLayer::fishdeadEndCallBack(CCNode* node)
{
    DF_LOG("动画结束");
  //  this->removeChild(node);
    //this->getChildByTag(2)->setVisible(true);
  //  this->scheduleOnce(schedule_selector(GameLayer::showXihaGift),1);
//    if (task_index == -1) {
//        task_index = 4;
//        setTaskInfoPanle(task_index);
//    }
    CCSprite *p_Sprite = CCSprite::create();
    // p_Sprite->initWithSpriteFrame(pframe_1);
    
     CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    p_Sprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

    //CCCallFuncN * funcall= CCCallFuncN::create(this, callfuncN_selector(GameLayer::light1EndCallBack));
    CCArray *aniframe = CCArray::create();
    for (int i = 0; i<4; i++) {
        CCString* str = CCString::createWithFormat("light2_%d.png",i);
        CCSpriteFrame* pframe_light= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
        if (i == 0) {
            p_Sprite->initWithSpriteFrame(pframe_light);
        }
        aniframe->addObject(pframe_light);
    }
    // aniframe->addObject(pframe_2);
    CCAnimation *animation= CCAnimation::createWithSpriteFrames(aniframe,0.2f);
    
    CCFiniteTimeAction* animate = CCAnimate::create(animation);
    
    /*light 3
     */
    CCArray *aniframe_1 = CCArray::create();
    for (int i = 0; i<2; i++) {
        CCString* str = CCString::createWithFormat("light3_%d.png",i);
        CCSpriteFrame* pframe_light= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
        aniframe_1->addObject(pframe_light);
    }
    // aniframe->addObject(pframe_2);
    CCAnimation *animation_1= CCAnimation::createWithSpriteFrames(aniframe_1,0.2f);
    
    CCFiniteTimeAction* animate_1 = CCAnimate::create(animation_1);
    CCFiniteTimeAction * seq_loop= CCSequence::create(animate_1,NULL);
    // CCRepeat::create(animate,1)
    CCFiniteTimeAction * seq= CCSequence::create(animate,CCRepeat::create(seq_loop, 2),CCCallFuncN::create(this, callfuncN_selector(GameLayer::dellightCallBack)),NULL);
    
    
    this->addChild(p_Sprite);
    p_Sprite->setZOrder(this->getChildByTag(1)->getZOrder()+255);
    p_Sprite->runAction(seq);
    p_Sprite->setAnchorPoint(ccp(0.5,0.0));
    
}
void GameLayer::delboxCallBack(CCNode* node)
{
    this->removeChild(node);
}
void GameLayer::dellightCallBack(CCNode *node)
{
    this->removeChild(node);
    showXihaGift();
}
void GameLayer::showXihaGift()
{
    isLightAnimation = false;
    DF_LOG("GameLayer::showXihaGift isLightAnimation=%d",isLightAnimation);
   //this->getChildByTag(2)->setVisible(false);
       // if (task_index == -1) {
            task_index = 4;
            setTaskInfoPanle(task_index);
       // }
}