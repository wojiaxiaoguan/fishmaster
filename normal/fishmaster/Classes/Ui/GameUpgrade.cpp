//
//  GameUpgrade.cpp
//  fish
//
//  
//
//

#include "GameUpgrade.h"
#include "GameData.h"
#include "Sound.h"

GameUpgradeLayer::GameUpgradeLayer()
:CCLayer()
{
    sp_bg = NULL;
}

GameUpgradeLayer::~GameUpgradeLayer()
{
    CC_SAFE_RELEASE(sp_bg);
}

CCScene* GameUpgradeLayer::scene()
{
    CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("GameUpgradeLayer", GameUpgradeLayerBuilderLoad::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("ios/ccbResources/GameUpgrade.ccbi", sc);
	
    ccbReader->release();
    
	if (node) {
        sc->addChild(node);
    }
    
	return sc;
}


void GameUpgradeLayer::exit()
{
    removeFromParent();
}

void GameUpgradeLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    fillUIElements();
    
    scheduleOnce(schedule_selector(GameUpgradeLayer::exit), 2.0f);
   
    Sound::Instance()->playEffect("level0.mp3");
}

bool GameUpgradeLayer::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_bg", CCSprite*, this->sp_bg);
    
    return true;
}

SEL_MenuHandler GameUpgradeLayer::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler GameUpgradeLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

//填充ui元素
void GameUpgradeLayer::fillUIElements()
{
    GameData* gd = GameData::getSharedGameData();
    GameUserExp* pExp = gd->getGameUserExpFroLevel(gd->currentLevel());
    
    CCLabelTTF* bonus_number = (CCLabelTTF*)sp_bg->getChildByTag(GameTTFBonusNumberTag);
    CCLabelTTF* ttf_bonus_number = CCLabelTTF::create(CCString::createWithFormat("奖励金币:  %d",pExp->m_bonus)->getCString(), "迷你简胖娃", 30);
    ttf_bonus_number->setPosition(bonus_number->getPosition());
    ttf_bonus_number->setAnchorPoint(bonus_number->getAnchorPoint());
    ttf_bonus_number->setColor(ccc3(251.0f,245.0f,169.0f));
    sp_bg->removeChildByTag(GameTTFBonusNumberTag);
    sp_bg->addChild(ttf_bonus_number,1,GameTTFBonusNumberTag);
    
//    CCLabelTTF* next_level = (CCLabelTTF*)sp_bg->getChildByTag(GameTTFNewLevelTag);
//    CCLabelTTF* ttf_next_level = CCLabelTTF::create(CCString::createWithFormat("恭喜升为%d级",pExp->m_level)->getCString(), "迷你简胖娃", 30);
//    ttf_next_level->setPosition(next_level->getPosition());
//    ttf_next_level->setAnchorPoint(next_level->getAnchorPoint());
//    ttf_next_level->setColor(ccc3(63.0f,47.0f,36.0f));
//    sp_bg->removeChildByTag(GameTTFNewLevelTag);
//    sp_bg->addChild(ttf_next_level,1,GameTTFNewLevelTag);
    
    CCLabelTTF* unlock_item = (CCLabelTTF*)sp_bg->getChildByTag(GameTTFUnlockItemTag);
    CCString* str = gd->getDespForLevel(pExp->m_level);
    CCLabelTTF* ttf_unlock_item = CCLabelTTF::create(str->getCString(), "迷你简胖娃", 30);
    ttf_unlock_item->setPosition(unlock_item->getPosition());
    ttf_unlock_item->setAnchorPoint(unlock_item->getAnchorPoint());
    ttf_unlock_item->setColor(ccc3(251.0f,245.0f,169.0f));
    sp_bg->removeChildByTag(GameTTFUnlockItemTag);
    sp_bg->addChild(ttf_unlock_item,1,GameTTFUnlockItemTag);
    
    CCLabelTTF* next_unlock = (CCLabelTTF*)sp_bg->getChildByTag(GameTTFNextUnlockTag);
    str = gd->getNextDespForLevel(pExp->m_level);
    CCLabelTTF* ttf_next_unlock = CCLabelTTF::create(str->getCString(), "迷你简胖娃", 30);
    ttf_next_unlock->setPosition(next_unlock->getPosition());
    ttf_next_unlock->setAnchorPoint(next_unlock->getAnchorPoint());
    ttf_next_unlock->setColor(ccc3(251.0f,245.0f,169.0f));
    ttf_next_unlock->setFontSize(25.0f);
    sp_bg->removeChildByTag(GameTTFNextUnlockTag);
    sp_bg->addChild(ttf_next_unlock,1,GameTTFNextUnlockTag);
    
    playParticleFireworks(0);
}

void GameUpgradeLayer::playParticleFireworks(float ct)
{
    static int count = 1;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCParticleSystem *emitter = CCParticleSystemQuad::create("lihua_g.plist");
    
    Sound::Instance()->playEffect("level1.mp3");
    
    emitter->setAnchorPoint(ccp(0.5, 0.5));
    emitter->setScale(0.5f);
    
    float delay = 0.1f;
    
    switch (count%4) {
        case 1:
        {
            emitter->setPosition(ccp(winSize.width / 4, winSize.height * 3 / 4 ));
            delay = 0.25f;
        }
            
            break;
        case 2:
        {
            emitter->setPosition(ccp(winSize.width * 3 / 4, winSize.height / 4));
            delay = 0.1f;
        }
            
            break;
        case 3:
        {
            emitter->setPosition(ccp(winSize.width * 3 / 4, winSize.height * 3 / 4));
            delay = 0.2f;
        }
            
            break;
        case 4:
        {
            emitter->setPosition(ccp(winSize.width * 1 /4 , winSize.height * 1 /4 ));
        }
            break;
        default:
            break;
            
    } // end of  switch (count) {
    
    emitter->setAutoRemoveOnFinish(true);
    addChild(emitter, 8);
    count++;
    
    if (count > 8) {
        count = 1;
        unschedule(schedule_selector(GameUpgradeLayer::playParticleFireworks));
        
    } else {
        schedule(schedule_selector(GameUpgradeLayer::playParticleFireworks), delay);
    }
    
}



