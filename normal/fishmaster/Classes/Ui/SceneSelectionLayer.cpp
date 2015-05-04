
#include "SceneSelectionLayer.h"
#include "GameData.h"
#include "GameLayer.h"
#include "introLayer.h"
#include "Sound.h"

#include "pgPlatformFactory.h"

using namespace cocos2d;


CCB_CLASS_NAME:: CCB_CLASS_NAME ()
:CCLayer()
{
    _tableView = NULL;
    
    cb_layerContainer = NULL;
    cb_layerSceneTemplate = NULL;
    cb_layerCellTemplate = NULL;
    
    
    cb_spSceneBG = NULL;
    cb_spScene = NULL;
    cb_spLockFlag = NULL;
    
    cb_lblTitle = NULL;
    cb_lblDesc = NULL;
    cb_lblExclusive = NULL;
    
    cb_menuAction = NULL;
    cb_btnAction = NULL;
    
    cb_menuReturn = NULL;
    cb_btnReturn = NULL;
    
    isTouchInMenu = false;
    isTouchInTableView = false;
    
    manger = SceneSelectionManager::sharedSceneSelectionManager();


}

CCB_CLASS_NAME:: ~ CCB_CLASS_NAME ()
{
    
    CC_SAFE_RELEASE(cb_layerContainer);
    CC_SAFE_RELEASE(cb_layerSceneTemplate);
    CC_SAFE_RELEASE(cb_layerCellTemplate);
    
    
    CC_SAFE_RELEASE(cb_spSceneBG);
    CC_SAFE_RELEASE(cb_spScene);
    CC_SAFE_RELEASE(cb_spLockFlag);
    
    CC_SAFE_RELEASE(cb_lblTitle);
    CC_SAFE_RELEASE(cb_lblDesc);
    CC_SAFE_RELEASE(cb_lblExclusive);
    
    CC_SAFE_RELEASE(cb_menuAction);
    CC_SAFE_RELEASE(cb_btnAction);
    
    CC_SAFE_RELEASE(cb_menuReturn);
    CC_SAFE_RELEASE(cb_btnReturn);
}


CCScene* CCB_CLASS_NAME::scene()
{
	CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader(XStr(CCB_CLASS_NAME), XConn(CCB_CLASS_NAME, BuilderLoad)::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("ios/ccbResources/" XStr(CCB_CLASS_NAME ) ".ccbi", sc);
    

	
    ccbReader->release();
    
	if (node) {
        sc->addChild(node);
    }
    
	return sc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void CCB_CLASS_NAME ::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPriorityStore, true);
    fillUIElements();

}

bool CCB_CLASS_NAME ::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuReturn", CCMenu*, this->cb_menuReturn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_btnReturn", CCMenuItemImage*, this->cb_btnReturn);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuAction", CCMenu*, this->cb_menuAction);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_btnAction", CCMenuItemImage*, this->cb_btnAction);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerContainer", CCLayer*, this->cb_layerContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerSceneTemplate", CCLayer*, this->cb_layerSceneTemplate);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerCellTemplate", CCLayer*, this->cb_layerCellTemplate);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_spSceneBG", CCSprite*, this->cb_spSceneBG);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_spScene", CCSprite*, this->cb_spScene);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_spLockFlag", CCSprite*, this->cb_spLockFlag);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblTitle", CCLabelTTF*, this->cb_lblTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblDesc", CCLabelTTF*, this->cb_lblDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblExclusive", CCLabelTTF*, this->cb_lblExclusive);


	return true;
}

SEL_MenuHandler CCB_CLASS_NAME::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{

 	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onReturnClicked", CCB_CLASS_NAME::onReturnClicked);
 	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onActionClicked", CCB_CLASS_NAME::onActionClicked);
    
	return NULL;
}

SEL_CCControlHandler CCB_CLASS_NAME::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void CCB_CLASS_NAME::onEnter()
{
    
	CCLayer::onEnter();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CCB_CLASS_NAME::onUnlockSceneNotify), kBoughtSceneResultNotification, NULL);
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    
}

void CCB_CLASS_NAME::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    //note by andy
    /*
     CCNotificationCenter::sharedNotificationCenter()->removeObserver(
     this,
     kXxxxName);  // æ¶???????ç§?          æ­¤å??ä¸????è¿?ä¸?ä¼????å­?æ³???²ï??
     */
	CCLayer::onExit();
    
}


bool CCB_CLASS_NAME::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    isTouchInMenu = cb_menuReturn->ccTouchBegan(pTouch, pEvent);
    if (isTouchInMenu) {
        return isTouchInMenu;
    }
    
    isTouchInTableView = _tableView->ccTouchBegan(pTouch, pEvent);
    return isTouchInTableView;
    //return true;
}

void CCB_CLASS_NAME::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        cb_menuReturn->ccTouchMoved(pTouch, pEvent);
    }
    
    if (isTouchInTableView) {
      _tableView->ccTouchMoved(pTouch, pEvent);
    }

}
void CCB_CLASS_NAME::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        cb_menuReturn->ccTouchEnded(pTouch, pEvent);
        isTouchInMenu =false;
    }
    
    if (isTouchInTableView) {
        _tableView->ccTouchEnded(pTouch, pEvent);
        isTouchInTableView =false;
    }

}
void CCB_CLASS_NAME::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
    if (isTouchInMenu) {
        cb_menuReturn->ccTouchCancelled(pTouch, pEvent);
        isTouchInMenu =false;
    }
    
    if (isTouchInTableView) {
        _tableView->ccTouchCancelled(pTouch, pEvent);
        isTouchInTableView =false;
    }
    
}



void CCB_CLASS_NAME::tableCellTouched(CCTableView* table, CCTableViewCell* cell) {
    
}

void CCB_CLASS_NAME::onReturnClicked(CCObject *pSender) {
    
    
    //å½????layer???parent???scene???scene???parent??????IntroLayer
    IntroLayer *parent =  (IntroLayer*)getParent()->getParent();
    
    parent ->setButtonStatus(true);
    
    removeFromParentAndCleanup(true);
    Sound::Instance()->playEffect("btn.mp3");
}

//å¡????ui???ç´?
void CCB_CLASS_NAME::fillUIElements() {
    

    _tableView = SceneTableView::create(this, cb_layerSceneTemplate->getContentSize());
    
    _tableView->setPosition(cb_layerSceneTemplate->getPosition());
 
    CCPoint anchorPoint = cb_layerSceneTemplate->getAnchorPoint();
    
    _tableView->setAnchorPoint(anchorPoint);

    
	_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    _tableView->setDirection(kCCScrollViewDirectionHorizontal);
	_tableView->setDelegate(this);
    _tableView->setDataSource(this);

    
    cb_layerContainer->addChild(_tableView);
    _tableView->reloadData();
    
    int index  = (int) GameData::getSharedGameData()->currentScene();
    
    int width =(int)CCDirector::sharedDirector()->getWinSize().width;
    
    float baseOffset = width * (1-0.7)/2;
    
    SceneTableView *tableImpl = (SceneTableView*)_tableView;
    if (tableImpl != NULL) {
        tableImpl->setOffsetInPixels(baseOffset);
    }
    
    //?????¨ç§»??¨å?°ä??ä¸?æ¬¡é????ºæ?¶æ????¨ç????ºæ??
    _tableView->setContentOffset(ccp( baseOffset + index  * width, 0));  //æ¨????ç¼©æ?? 0.15 = (1-0.7)/2
}



CCSize CCB_CLASS_NAME::cellSizeForTable(CCTableView *table)
{
    return cb_layerCellTemplate->getContentSize();

}

#if 0
CCSize CCB_CLASS_NAME::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCSize size;
    size = cb_layerCellTemplate->getContentSize();
    if (index == 0) {
        size = CCSize::CCSize(size.width * 0.8, size.height);
    }
    return size;
}
#endif


unsigned int CCB_CLASS_NAME::numberOfCellsInTableView(CCTableView *table)
{
    int count = manger->count();
    return count;
}


CCTableViewCell* CCB_CLASS_NAME::tableCellAtIndex(CCTableView *table, unsigned int idx) {
  
	SceneCell *cell = (SceneCell*)table->dequeueCell();
    
	if (!cell) {

		cell = SceneCell::create( cb_layerCellTemplate );
		      
	}
    
    cell->fill(idx, manger);
    return cell;

}



void CCB_CLASS_NAME::doEnterScene(Scene s) {
    GameData::getSharedGameData()->setGameType(GameType_Normal);
    GameData::getSharedGameData()->setCurrentScene(s);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(SceneReplaceTime, GameLayer::scene(), ccBLACK));
}

    
void CCB_CLASS_NAME::doUnlockScene(Scene s) {
    
    //???èµ·è´­ä¹°å?ºæ?????ä½?
    ProductType product;
    
    switch (s) {
        case SceneDream:
        {
            product = Product_DreamScene;
            goto BUY_SCENE_FLAG;
        }
            break;
            
        case SceneProfusion:
        {
            product = Product_ProfusionScene;
            goto BUY_SCENE_FLAG;
        }
            break;
            
        case SceneHistoric:
        {
            product = Product_HistoricScene;
            goto BUY_SCENE_FLAG;
        }
            break;
            
        default:
            return;
    }

    
BUY_SCENE_FLAG:

        IPlatformFactory::sharedPlatform()->beginPurchase(product);
}



void CCB_CLASS_NAME::onActionClicked(CCObject *pSender){
    CCMenuItemImage *btn = (CCMenuItemImage*)pSender;
    
    Sound::Instance()->playEffect("btn.mp3");
    
    Scene s = (Scene)(int)btn->getUserData();
    
    if (s < 0 || s >= SceneNum) {
        return;
    }
    
    
    SceneStatus status = SceneSelectionManager::sharedSceneSelectionManager()->sceneStatus(s);
    
    switch (status) {
        case SceneLocked:
        {
            //æ²¡é??ç½???????ä¹????ï¼?è§£é????ºæ??ä¼?crashï¼????ç½???????ä¹??????¾å??ä¸????ä»£ç??
            //doUnlockScene(s);
        }
        break;
        
        case SceneUnlocked:
        {
            doEnterScene(s);
        }
        break;
            
        default:
            break;
    }
}




int CCB_CLASS_NAME::calcTableOffset( int viewHeight, int cellHeight, int cellCount, int cellIndex ) {
    int tableTotalHeight = cellCount *cellHeight;
    if (tableTotalHeight > viewHeight) {
        return 0 - ( cellCount - (cellIndex + 1)) * cellHeight;
    }
    //return viewHeight - tableTotalHeight;
    return -200;
}

void CCB_CLASS_NAME::onUnlockSceneNotify(CCObject *pObj) {
    
    Scene s = (Scene)(int)pObj;
    
    //è®¾ç½®è´?ä¹°ç?¶æ??
    manger->setSceneStatus(s);
    
    //è´?ä¹°æ????? è¿????
    doEnterScene(s);
    
}
//===============================================================================

SceneCell::SceneCell()
{
    
}

SceneCell::~SceneCell()
{
}

void SceneCell::onEnter()
{
    
    CCTableViewCell::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPriorityStoreTable, false);
}

void SceneCell::onExit()
{
    CCTableViewCell::onExit();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool SceneCell::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    isActionClicked = menuAction->ccTouchBegan(pTouch, pEvent);
    return isActionClicked;
    //return true;
}

void SceneCell::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isActionClicked) {
        menuAction->ccTouchMoved(pTouch, pEvent);
    }
    
}
void SceneCell::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isActionClicked) {
        menuAction->ccTouchEnded(pTouch, pEvent);
        isActionClicked =false;
    }
    
}
void SceneCell::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isActionClicked) {
        menuAction->ccTouchCancelled(pTouch, pEvent);
        isActionClicked =false;
    }
    
}


void SceneCell::draw()
{
    CCTableViewCell::draw();
}


CCRect SceneCell::convertToWorldSpace(CCNode *pNode)
{
    CCRect rc;
	rc.origin = pNode->getPosition();
	rc.size = pNode->getContentSize();
 	rc.origin.x -= rc.size.width / 2;
	rc.origin.y -= rc.size.height / 2;
    return rc;
}

SceneCell* SceneCell::create( CCLayer *tmpl) {

    SceneCell *cell = new SceneCell();
    if (cell != NULL) {
        
        cell->initWithTemplate(tmpl);
        
        cell->autorelease();
        
        return cell;
    }
    return NULL;
}


void SceneCell::initWithTemplate(CCLayer *tmpl) {

    if(tmpl == NULL) {
        return;
    }

    //setAnchorPoint(ccp(1, tmpl->getAnchorPoint().y));
    setPosition(tmpl->getPosition());
    CCSprite *spBGTmpl = ( CCSprite *)tmpl->getChildByTag(TagBG);
    CCSprite *spSceneTmpl = ( CCSprite *)tmpl->getChildByTag(TagImage);
    CCSprite *spLockFlagTmpl = ( CCSprite *)tmpl->getChildByTag(TagLockTag);
    
    CCLabelTTF *lblTitleTmpl = (CCLabelTTF*)tmpl->getChildByTag(TagTitle);
    CCLabelTTF *lblDescTmpl = (CCLabelTTF*)tmpl->getChildByTag(TagDesc);
    CCLabelTTF *lblExTmpl = (CCLabelTTF*)tmpl->getChildByTag(TagExclusive);
    
    CCMenu *menuActionTmpl = (CCMenu*)tmpl->getChildByTag(TagMenu);

    
    if (!spBGTmpl || !spSceneTmpl || !spLockFlagTmpl || !lblDescTmpl || !lblExTmpl || !lblTitleTmpl || !menuActionTmpl) {
        return;
    }
    

    
    //??????
    CCSprite *spBG = CCSprite::create();
    spBG->setPosition(spBGTmpl->getPosition());
    spBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("scenechoose.png"));

    spBG->setTag(spBGTmpl->getTag());
    addChild(spBG);

    
    //???é¢?
    addLabel(lblTitleTmpl );
    
    //???è¿?
    addLabel( lblDescTmpl);
    
    //ä¸?å±?
    addLabel(lblExTmpl);
    
    //??ºæ??
    CCSprite *spImage = CCSprite::create();
    spImage->setPosition(spSceneTmpl->getPosition());
    spImage->setTag(spSceneTmpl->getTag());
    addChild(spImage);


    CCMenuItemImage *btnActionTmpl = (CCMenuItemImage*)menuActionTmpl->getChildByTag(TagMenu);
    if(btnActionTmpl == NULL) {
        return;
    }
    
    //è§£é??button.
    CCMenuItemImage *btnAction = CCMenuItemImage::create();
    btnAction->setTarget(this, menu_selector(CCB_CLASS_NAME::onActionClicked));
    btnAction->setPosition(btnActionTmpl->getPosition() );
    btnAction->setAnchorPoint(btnActionTmpl->getAnchorPoint());
    btnAction->setTag(TagMenu);
    btnAction->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Unlock.png"));
    
    menuAction = CCMenu::createWithItem(btnAction);
    menuAction->ignoreAnchorPointForPosition(false);
    menuAction->setContentSize(menuActionTmpl->getContentSize());
    menuAction->setPosition(menuActionTmpl->getPosition());
    menuAction->setTag(menuActionTmpl->getTag());
    addChild(menuAction);

    
    //è§£é?????è®?
    CCSprite *spLockFlag = CCSprite::create();
    spLockFlag->setPosition(spLockFlagTmpl->getPosition());
    spLockFlag->setTag(spLockFlagTmpl->getTag());
    spLockFlag->setAnchorPoint(spLockFlagTmpl->getAnchorPoint());
    spLockFlag->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("suo.png"));
    addChild(spLockFlag);

}

void SceneCell::addLabel( CCLabelTTF *tmpl  ) {
    if ( tmpl == NULL) {
        return;
    }
    CCLabelTTF* lbl = CCLabelTTF::create();
    
    lbl->setPosition(tmpl->getPosition());
    lbl->setAnchorPoint(tmpl->getAnchorPoint());
    
    //??????labelå­?ä½?ä¸????
    lbl->setColor(tmpl->getColor());
    lbl->setFontName("è¿·ä??ç®????å¨?");
    lbl->setFontSize(tmpl->getFontSize());
    lbl->setTag(tmpl->getTag());
    
    addChild(lbl);
    
}


void SceneCell::fill(int index, SceneSelectionManager *manager) {

    int count = manager->count();
    if( index >= count) {
        return;
    }
    
    CCDictionary *dict = manager->infoForScene(Scene(index));
    if (dict == NULL) {
        return;
    }
    
    CCSprite *sprite = NULL;
    

    CCMenuItemImage *btnAction = NULL;
    
    CCLabelTTF *label = NULL;
    
    CCString *str = NULL;
    CCInteger *interger = NULL;
    
    
    sprite = (CCSprite*)getChildByTag(TagImage);
    
    //??ºæ??
    if (sprite != NULL) {
        str =(CCString*)dict->objectForKey(SCENE_IMAGE);
        sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString()));
    }
    
    
    interger =(CCInteger*)dict->objectForKey(SCENE_LOCK_FLAG);
    int lockValue = interger->getValue();
    

    //è§£é?????è®?
    sprite = (CCSprite*)getChildByTag(TagLockTag);
    if (sprite != NULL) {
        if (lockValue == SceneLocked) {
            sprite->setVisible(true);
            
        } else {
            sprite->setVisible(false);
        }
    }

    
    btnAction = (CCMenuItemImage*)menuAction->getChildByTag(TagMenu);
    if (btnAction != NULL) {
        btnAction->setUserData((void*)index);
        if (lockValue == SceneLocked) {
            btnAction->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Unlock.png"));

            
        } else {
            btnAction->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("continue.png"));
        }
        
    }  // end of         if (btnAction != NULL) {

    
    //???é¢?
    label = (CCLabelTTF*)getChildByTag(TagTitle);
    str =(CCString*)dict->objectForKey(SCENE_NAME);
    if (label != NULL) {
        label->setString(str->getCString());
    }
    
    //ç®?ä»?
    label = (CCLabelTTF*)getChildByTag(TagDesc);
    str =(CCString*)dict->objectForKey(SCENE_DESC);
    if (label != NULL) {
        label->setString(str->getCString());
    }
    
    //ä¸?å±?
    label = (CCLabelTTF*)getChildByTag(TagExclusive);
    str =(CCString*)dict->objectForKey(SCENE_EXCLUSIVE);
    if (label != NULL) {
        label->setString(str->getCString());
    }
}



void SceneTableView::setOffsetInPixels(float theOffset ) {
    offset = theOffset;
}
void SceneTableView::relocateContainer(bool animated)
{
    CCPoint oldPoint, min, max;
    float newX, newY;
    
    min = this->minContainerOffset();
    max = this->maxContainerOffset();
    
    oldPoint = m_pContainer->getPosition();
    
    newX     = oldPoint.x;
    newY     = oldPoint.y;
    if (m_eDirection == kCCScrollViewDirectionBoth || m_eDirection == kCCScrollViewDirectionHorizontal)
    {
        newX     = MAX(newX, min.x);
        newX     = MIN(newX, max.x);
        if(newX >= -0.05  && newX <= 0.05 ) {
            newX = offset;
        }
        
        
    }
    
    if (m_eDirection == kCCScrollViewDirectionBoth || m_eDirection == kCCScrollViewDirectionVertical)
    {
        newY     = MIN(newY, max.y);
        newY     = MAX(newY, min.y);
    }
    
    if (newY != oldPoint.y || newX != oldPoint.x)
    {
        
        this->setContentOffset(ccp(newX, newY), animated);
    }
}


CCTableView* SceneTableView::create(CCTableViewDataSource* dataSource, CCSize size)
{
    SceneTableView *table = new SceneTableView();
    table->initWithViewSize(size, NULL);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateCellPositions();
    table->_updateContentSize();
    
    return table;
}


