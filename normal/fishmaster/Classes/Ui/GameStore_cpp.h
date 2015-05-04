//
//  GameStore_cpp.h
//  fish
//
//  
//
//

#ifndef fish_GameStore_cpp_h
#define fish_GameStore_cpp_h

#include "GameStore.h"
#include "Helper.h"
#include "pgPlatformFactory.h"
#include "Sound.h"
#include "common.h"
#include "GameLayer.h"
tableCell::tableCell()
{
    m_root_layer = NULL;
}

tableCell::~tableCell()
{
    removeChildByTag(GameTableCellAddTag, false);
}


tableCell* tableCell::createGoldCell( CCLayer *cell)
{
    
    tableCell *newcell = new tableCell();
    if (newcell != NULL) {
        
        newcell->initGoldWithLayer(cell);
        newcell->retain();
        newcell->autorelease();
        
        return newcell;
    }
    return NULL;
    
}


tableCell* tableCell::createMarketCell( CCLayer *cell)
{
    
    tableCell *newcell = new tableCell();
    if (newcell != NULL) {
        
        newcell->initMarketWithLayer(cell);
        newcell->retain();
        newcell->autorelease();
        
        return newcell;
    }
    return NULL;
    
}


tableCell* tableCell::createExchangeCell( CCLayer *cell)
{
    
    tableCell *newcell = new tableCell();
    if (newcell != NULL) {
        
        newcell->initExchangeWithLayer(cell);
        newcell->retain();
        newcell->autorelease();
        
        return newcell;
    }
    return NULL;
    
}


void tableCell::initGoldWithLayer( CCLayer *cell)
{
    
    m_type = GameStoreLayerTableGold;
    
    if (cell == NULL) {
        return;
    }
    cell->setTag(GameTableCellAddTag);
    addChild(cell);
}


void tableCell::initMarketWithLayer( CCLayer *cell)
{
    
    m_type = GameStoreLayerTableMarket;
    
    if (cell == NULL) {
        return;
    }
    cell->setTag(GameTableCellAddTag);
    addChild(cell);
    
    int row = (int)cell->getUserData();
    
    if (row == 1) {
        CCSprite* sp = (CCSprite*)cell->getChildByTag(1); //yellow
        fillDiamondItem(sp, Diamond_Yellow);
        
        sp = (CCSprite*)cell->getChildByTag(2); //green
        fillDiamondItem(sp, Diamond_Green);
        
        sp = (CCSprite*)cell->getChildByTag(3); //red
        fillDiamondItem(sp, Diamond_Red);
        
        sp = (CCSprite*)cell->getChildByTag(4); //blue
        fillDiamondItem(sp, Diamond_Blue);
    } else if (row == 2){
        CCSprite* sp = (CCSprite*)cell->getChildByTag(1); //珍珠
        fillDiamondItem(sp, Diamond_Pearl);
        
//        sp = (CCSprite*)cell->getChildByTag(2); //
//        fillDiamondItem(sp, Diamond_BlackPearl);
        
//        sp = (CCSprite*)cell->getChildByTag(3);
//        fillDiamondItem(sp, Diamond_Diamond);
    }
}

void tableCell::fillDiamondItem(CCSprite *pDia,DiamondType pType)
{
    if (pDia == NULL) {
        return;
    }
    GameData* gd = GameData::getSharedGameData();
    GameDiamond* dia = gd->getGameDiamond(pType);
    
    
    
    CCSprite* number2 = (CCSprite*)pDia->getChildByTag(102);
    CCSprite* number1 = (CCSprite*)pDia->getChildByTag(101);
    
    CCString* num1_str = CCString::createWithFormat("bs%d.png",dia->m_cnt%10);
    CCString* num2_str = CCString::createWithFormat("bs%d.png",dia->m_cnt/10);
    
    CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num1_str->getCString());
    number1->setDisplayFrame(spFram);
    spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num2_str->getCString());
    number2->setDisplayFrame(spFram);
    if (dia->m_cnt == 0) {
        number2->setVisible(false);
    } else {
        number2->setVisible(true);
    }
    
    CCSprite* number_price = (CCSprite*)pDia->getChildByTag(110);
    number_price->setVisible(false);
    NumSprite* num = NumSprite::create(dia->m_price, GameNumberStoreLayerGold);
    num->setPosition(number_price->getPosition());
    num->setScale(0.7);
    pDia->addChild(num);
}


void tableCell::initExchangeWithLayer( CCLayer *cell)
{
    
    m_type = GameStoreLayerTableExchange;
    
    if (cell == NULL) {
        return;
    }
    cell->setTag(GameTableCellAddTag);
    if (cell->getParent())
    {
        cell->removeFromParentAndCleanup(false);
    }
    addChild(cell);
    
    int row = (int)cell->getUserData();
    
    if (row == 1) {
        CCSprite* sp = (CCSprite*)cell->getChildByTag(1);
        fillCardItem(sp, Card_Denglongyu);
        
        sp = (CCSprite*)cell->getChildByTag(2);
        fillCardItem(sp, Card_Shenxianyu);
        
    } else if (row == 2){
        CCSprite* sp = (CCSprite*)cell->getChildByTag(1);
        fillCardItem(sp, Card_Wuzhe);
        
        sp = (CCSprite*)cell->getChildByTag(2);
        fillCardItem(sp, Card_Shiziyu);
    } else if (row == 3){
        CCSprite* sp = (CCSprite*)cell->getChildByTag(1);
        fillCardItem(sp, Card_Dabaisha);
        
        sp = (CCSprite*)cell->getChildByTag(2);
        fillCardItem(sp, Card_Xiaochouyu);
    }else if (row == 4){
        CCSprite* sp = (CCSprite*)cell->getChildByTag(1);
        fillCardItem(sp, Card_LanAli);
    }
}

void tableCell::fillCardItem(CCSprite *pCard,CardType pType)
{
    if (pCard == NULL) {
        return;
    }
    GameData* gd = GameData::getSharedGameData();
    GameCard* card = gd->getGameCard(pType);
    
//    CCSprite* number1 = (CCSprite*)pCard->getChildByTag(101);
    
//    CCString* num1_str = CCString::createWithFormat("bs%d.png",card->m_count);
    for (int i = 1; i <= card->m_count; i++)
    {
        CCSprite* start = (CCSprite*)pCard->getChildByTag(i);
        if (start)
        {
            start->setVisible(true);
        }
    }
//    CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num1_str->getCString());
//    number1->setDisplayFrame(spFram);
}



void tableCell::onEnter()
{
    isTouchMove = false;
    
    CCTableViewCell::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPriorityStoreTable, false);
}

void tableCell::onExit()
{
    CCTableViewCell::onExit();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool tableCell::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    touchPoint = convertTouchToNodeSpace(pTouch);
    //    CCRect rect;
    touchIndex = 0;
    if (m_root_layer->getFastBuy())
    {
        return false;
    }
    //ignore     the touch out of the table view
    CCPoint lo_0 = pTouch->getLocationInView();
    CCLayer* parent = (CCLayer*)getParent()->getParent()->getParent();
    //edit by andy 2015-03-31
    CCPoint parent_point =parent->getPosition();
    CCSize parent_size = parent->getContentSize();
    //CCRect rec = (parent->boundingBox());
    CCRect rec(parent_point.x,parent_point.y,parent_size.width,parent_size.height);
   // DF_LOG("lo_0.x=%f, lo_0.y=%f",lo_0.x,lo_0.y);
    if (rec.containsPoint(lo_0) == false) {
        return false;
    }
    
    CCLayer* cell_ly = (CCLayer*)getChildByTag(GameTableCellAddTag);
    if (cell_ly == NULL) {
        return false;
    }
    for (int i = 1; i <= 4; i++) {
        CCSprite* sub_cell = (CCSprite*)cell_ly->getChildByTag(i);
        if (sub_cell == NULL) {
            continue;
        }
        CCRect rect = sub_cell->boundingBox();
        if (rect.containsPoint(touchPoint)) {
            touchIndex = i;
            return true;
        }
    }
    return true;
}

void tableCell::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    isTouchMove = true;
}

void tableCell::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
    
    CCPoint endTouchPoint = convertTouchToNodeSpace(pTouch);
    if (isTouchMove && ((endTouchPoint.x > (touchPoint.x + 10)) || (endTouchPoint.x < (touchPoint.x - 10)) || (endTouchPoint.y > (touchPoint.y + 10)) || (endTouchPoint.y < (touchPoint.y - 10))))
    {
        isTouchMove = false;
        CCLog("touch move cancel");
        return;
    }
    if (touchIndex == 0) {
        return;
    }
    CCLayer* ly = (CCLayer*)getChildByTag(GameTableCellAddTag);
    
    int row = (int)ly->getUserData();
    int col = touchIndex;
    DF_LOG("row = %d,col = %d",row,col);
    switch (m_type) {
        case GameStoreLayerTableGold:
            touchGoldCell(row, col);
            break;
        case GameStoreLayerTableMarket:
            touchMarketCell(row, col);
            break;
        case GameStoreLayerTableExchange:
            touchExchangeCell(row, col);
            break;
        default:
            break;
    }
    
    touchIndex = 0;
    
}

void tableCell::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

GameSubStoreLayer* tableCell::addDetailLayer()
{
    if (m_root_layer == NULL) {
        return NULL;
    }
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("GameSubStoreLayer", GameSubStoreLayerBuilderLoad::loader());
    CCBReader *ccbReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* sub_node = ccbReader->readNodeGraphFromFile("ios/ccbResources/GameSubStore.ccbi");
    ccbReader->release();
    
    m_root_layer->addChild(sub_node);
    
    return (GameSubStoreLayer*)sub_node;
}

void tableCell::touchGoldCell(int row, int col)
{
    bool isAddDetailLayer = false;
    CCString* detail_file_name = NULL;
    if (row == 1) {
        if (col == 1) {
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_Coin2);
            m_root_layer->buyGoods(Product_Coin2, GameData::getSharedGameData()->genOrderId(Product_Coin2, pToken).c_str(), pToken);
        } else if (col == 2){
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_Coin6);
            m_root_layer->buyGoods(Product_Coin6, GameData::getSharedGameData()->genOrderId(Product_Coin6, pToken).c_str(), pToken);
//            IPlatformFactory::sharedPlatform()->beginPurchase(Product_Coin6);
        }else if (col == 3){
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_Coin10);
            m_root_layer->buyGoods(Product_Coin10, GameData::getSharedGameData()->genOrderId(Product_Coin10, pToken).c_str(), pToken);
//            IPlatformFactory::sharedPlatform()->beginPurchase(Product_Coin18);
        }else if (col == 4){
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_HideBullet1000);
            m_root_layer->buyGoods(Product_HideBullet1000, GameData::getSharedGameData()->genOrderId(Product_HideBullet1000, pToken).c_str(), pToken);
//            IPlatformFactory::sharedPlatform()->beginPurchase(Product_Coin40);
        }
    } else if (row == 2) {
        if (col == 1) {
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_Diamond2);
            m_root_layer->buyGoods(Product_Diamond2, GameData::getSharedGameData()->genOrderId(Product_Diamond2, pToken).c_str(), pToken);
//            IPlatformFactory::sharedPlatform()->beginPurchase(Product_Coin78);
        } else if (col == 2){
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_PearlShell);
            m_root_layer->buyGoods(Product_PearlShell, GameData::getSharedGameData()->genOrderId(Product_PearlShell, pToken).c_str(), pToken);
//            IPlatformFactory::sharedPlatform()->beginPurchase(Product_Coin128);
        }else if (col == 3){
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_Coin15);
            m_root_layer->buyGoods(Product_Coin15, GameData::getSharedGameData()->genOrderId(Product_Coin15, pToken).c_str(), pToken);
//            IPlatformFactory::sharedPlatform()->beginPurchase(Product_Coin388);
        }else if (col == 4)
        {
            int pToken = arc4random() % 9999;
            m_root_layer->setToken(pToken);
            m_root_layer->setProductType(Product_FishKnife);
            m_root_layer->buyGoods(Product_FishKnife, GameData::getSharedGameData()->genOrderId(Product_FishKnife, pToken).c_str(), pToken);
        }
    }
//    else if (row == 3)
//    {
//        if (col == 1) {
//            isAddDetailLayer = true;
//            
//            detail_file_name = CCString::createWithFormat("bao2js.png");
//            
//        } else if (col == 2){
//            isAddDetailLayer = true;
//            detail_file_name = CCString::createWithFormat("bao1js.png");
//            
//        }else if (col == 3){
//            isAddDetailLayer = true;
//            detail_file_name = CCString::createWithFormat("baoxianjs.png");
//        }else if (col == 4){
//            isAddDetailLayer = true;
//            detail_file_name = CCString::createWithFormat("mhxldtjs.png");
//        }
//    }
    //isAddDetailLayer =true;
    if (isAddDetailLayer) {
        GameSubStoreLayer* sl = addDetailLayer();
        
        sl->m_item_index = col + (row - 1) * 4;
        
        CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(detail_file_name->getCString());
        sl->sp_gift_detail->setDisplayFrame(spFram);
        sl->ly_gift_detail->setVisible(true);
        //del by andy 2015-04-02
        //sl->sub_menu->setVisible(false);
        
    }
}


void tableCell::touchMarketCell(int row,int col)
{
    bool isAddDetailLayer = false;
    CCString* detail_file_name = NULL;
    if (row == 1) {
        if (col == 1) {
            isAddDetailLayer = true;
            detail_file_name = CCString::createWithFormat("pack_10007.png");
            
        } else if (col == 2){
            isAddDetailLayer = true;
            detail_file_name = CCString::createWithFormat("pack_10006.png");
        }else if (col == 3){
            isAddDetailLayer = true;
            detail_file_name = CCString::createWithFormat("pack_10009.png");
        }else if (col == 4){
            isAddDetailLayer = true;
            detail_file_name = CCString::createWithFormat("pack_10008.png");
        }
    } else if (row == 2) {
        if (col == 1) {
            isAddDetailLayer = true;
            detail_file_name = CCString::createWithFormat("pack_85.png");
        }
    }
   
    if (isAddDetailLayer) {
        int index_2_type = col + (row - 1) * 4;
        
        GameDiamond* pDia = GameData::getSharedGameData()->getGameDiamond((DiamondType)index_2_type);
        
        if (pDia->m_cnt == 0) {
            CCLog("You don't have any diamond.");
            return;
        }
        
        GameSubStoreLayer* sl = addDetailLayer();
        
        //index is as the same as enum
        sl->m_item_index = index_2_type;
        
        CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(detail_file_name->getCString());
        sl->sp_dia_detail->setDisplayFrame(spFram);
        sl->ly_diamond_detail->setVisible(true);
        //del by andy 2015-04-02
        //sl->sub_menu->setVisible(true);
        
        sl->reFresh();
        
        NumSprite* num_single = NumSprite::create(pDia->m_price, GameNumberStoreLayerGold);
        num_single->setAnchorPoint(sl->sp_num_single->getAnchorPoint());
        num_single->setPosition(sl->sp_num_single->getPosition());
        num_single->setScale(0.6);
        sl->sp_num_single->setVisible(false);
        sl->ly_diamond_detail_bg->addChild(num_single);
    }
    
}


void tableCell::touchExchangeCell(int row, int col)
{
    bool isAddDetailLayer = true;
    CCString* detail_file_name = NULL;
    if (row == 1) {
        if (col == 1) {
            detail_file_name = CCString::createWithFormat("crasyflash_wz.png");
        } else if (col == 2){
            detail_file_name = CCString::createWithFormat("moneyflash_wz.png");
            
        }
    } else if (row == 2) {
        if (col == 1) {
            detail_file_name = CCString::createWithFormat("darkflash_wz.png");
            
        } else if (col == 2){
            detail_file_name = CCString::createWithFormat("lionflash_wz.png");
            
        }
    } else if (row == 3) {
        if (col == 1) {
            detail_file_name = CCString::createWithFormat("jawsflash_wz.png");
        } else if (col == 2){
            detail_file_name = CCString::createWithFormat("clownfish_wz.png");
        }
    } else if (row == 4) {
        if (col == 1){
            detail_file_name = CCString::createWithFormat("stunnedflash_wz.png");
        }
    }
    if (isAddDetailLayer) {
        GameSubStoreLayer* sl = addDetailLayer();
        //the index as the same as the card type enum
        sl->m_item_index = col + (row - 1) * 2;
        GameCard* pCard = GameData::getSharedGameData()->getGameCard((CardType)sl->m_item_index);
        
        CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(detail_file_name->getCString());
        sl->sp_exc_detail->setDisplayFrame(spFram);
        sl->ly_exchange_detail->setVisible(true);
        //del by andy 2015-04-02
        //sl->sub_menu->setVisible(true);
        
        int lack_diamond = 0;
        
        int num_total = pCard->price_yellow_diamond;
        CCString* num_str = CCString::createWithFormat("bs%d.png",num_total);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_yellow_total->setDisplayFrame(spFram);
        int num_single = GameData::getSharedGameData()->getGameDiamond(Diamond_Yellow)->m_cnt;
        num_single = num_single > num_total ? num_total : num_single;
        num_str = CCString::createWithFormat("bs%d.png",num_single);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_yellow_single->setDisplayFrame(spFram);
        if (num_single < num_total) {
            lack_diamond += num_total - num_single;
        }
        
        num_total = pCard->price_blue_diamond;
        num_str = CCString::createWithFormat("bs%d.png",num_total);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_blue_total->setDisplayFrame(spFram);
        num_single = GameData::getSharedGameData()->getGameDiamond(Diamond_Blue)->m_cnt;
        num_single = num_single > num_total ? num_total : num_single;
        num_str = CCString::createWithFormat("bs%d.png",num_single);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_blue_single->setDisplayFrame(spFram);
        if (num_single < num_total) {
            lack_diamond += num_total - num_single;
        }
        
        num_total = pCard->price_green_diamond;
        num_str = CCString::createWithFormat("bs%d.png",num_total);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_green_total->setDisplayFrame(spFram);
        num_single = GameData::getSharedGameData()->getGameDiamond(Diamond_Green)->m_cnt;
        num_single = num_single > num_total ? num_total : num_single;
        num_str = CCString::createWithFormat("bs%d.png",num_single);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_green_single->setDisplayFrame(spFram);
        if (num_single < num_total) {
            lack_diamond += num_total - num_single;
        }
        
        
        num_total = pCard->price_red_diamond;
        num_str = CCString::createWithFormat("bs%d.png",num_total);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_red_total->setDisplayFrame(spFram);
        num_single = GameData::getSharedGameData()->getGameDiamond(Diamond_Red)->m_cnt;
        num_single = num_single > num_total ? num_total : num_single;
        num_str = CCString::createWithFormat("bs%d.png",num_single);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_red_single->setDisplayFrame(spFram);
        if (num_single < num_total) {
            lack_diamond += num_total - num_single;
        }
        
        num_total = lack_diamond > 9 ? 9 : lack_diamond;
        num_str = CCString::createWithFormat("bs%d.png",num_total);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_pearl_total->setDisplayFrame(spFram);
        num_single = GameData::getSharedGameData()->getGameDiamond(Diamond_Pearl)->m_cnt;
        num_single = num_single > num_total ? num_total : num_single;
        num_str = CCString::createWithFormat("bs%d.png",num_single);
        spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(num_str->getCString());
        sl->sp_pearl_single->setDisplayFrame(spFram);
        
        //diamond enough
        if (num_single >= num_total) {
            //spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ok.png");
            //sl->sp_exc_prompt->setDisplayFrame(spFram);
            sl->sp_exchange->setEnabled(true);
            sl->m_exchange_enter->setEnabled(true);
            sl->sp_exc_prompt->setVisible(false);
            
        }
        else
        {
            sl->m_exchange_enter->setEnabled(false);
            sl->sp_exc_prompt->setVisible(true);
        }
    }
}




void tableCell::draw()
{
    CCTableViewCell::draw();
}


CCRect tableCell::convertToWorldSpace(CCNode *pNode)
{
    CCRect rc;
	rc.origin = pNode->getPosition();
	rc.size = pNode->getContentSize();
 	rc.origin.x -= rc.size.width / 2;
	rc.origin.y -= rc.size.height / 2;
    return rc;
}


////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

GameSubStoreLayer::GameSubStoreLayer()
:CCLayer(),
ly_gift_detail(NULL),
sp_gift_detail(NULL),
//sp_gf_buy(NULL),
//sub_menu(NULL),
ly_diamond_detail(NULL),
ly_diamond_detail_bg(NULL),
sp_dia_detail(NULL),
//sp_dia_buy(NULL),
sp_num_single(NULL),
sp_num_total(NULL),
sp_num_cnt(NULL),
ly_exchange_detail(NULL),
sp_exc_detail(NULL),
sp_exc_prompt(NULL),
//sp_exc_buy(NULL),
sp_yellow_single(NULL),
sp_yellow_total(NULL),
sp_blue_single(NULL),
sp_blue_total(NULL),
sp_red_single(NULL),
sp_red_total(NULL),
sp_green_single(NULL),
sp_green_total(NULL),
sp_pearl_single(NULL),
sp_pearl_total(NULL),
sp_sale(NULL),
sp_exchange(NULL),
m_bTouchedMenu(false),
m_dia_sell_cnt(0),
_num_dia_sell_cnt(NULL),
_num_dia_total_price(NULL),
subBuyMenu(NULL),
subSaleMenu(NULL),
subExchangeMenu(NULL),
m_dim_add(NULL),
m_dim_dec(NULL),
m_gif_exit(NULL),
m_gif_enter(NULL),
m_exchange_exit(NULL),
m_exchange_enter(NULL),
m_dim_exit(NULL),
m_dim_enter(NULL)
{
    
}
GameSubStoreLayer::~GameSubStoreLayer()
{
    CC_SAFE_RELEASE(ly_gift_detail);
    CC_SAFE_RELEASE(sp_gift_detail);
    //    CC_SAFE_RELEASE(sp_gf_buy);
    //del by andy 2015-04-02
    //CC_SAFE_RELEASE(sub_menu);
    CC_SAFE_RELEASE(subBuyMenu);
    CC_SAFE_RELEASE(subSaleMenu);
    CC_SAFE_RELEASE(subExchangeMenu);
    
    CC_SAFE_RELEASE(ly_diamond_detail);
    CC_SAFE_RELEASE(ly_diamond_detail_bg);
    CC_SAFE_RELEASE(sp_dia_detail);
    //    CC_SAFE_RELEASE(sp_dia_buy);
    CC_SAFE_RELEASE(sp_num_single);
    CC_SAFE_RELEASE(sp_num_total);
    CC_SAFE_RELEASE(sp_num_cnt);

    CC_SAFE_RELEASE(sp_sale);
    CC_SAFE_RELEASE(sp_exchange);
    
    
    CC_SAFE_RELEASE(ly_exchange_detail);
    CC_SAFE_RELEASE(sp_exc_detail);
    CC_SAFE_RELEASE(sp_exc_prompt);
    //    CC_SAFE_RELEASE(sp_exc_buy);
    CC_SAFE_RELEASE(sp_yellow_single);
    CC_SAFE_RELEASE(sp_yellow_total);
    CC_SAFE_RELEASE(sp_blue_single);
    CC_SAFE_RELEASE(sp_blue_total);
    CC_SAFE_RELEASE(sp_red_single);
    CC_SAFE_RELEASE(sp_red_total);
    CC_SAFE_RELEASE(sp_green_single);
    CC_SAFE_RELEASE(sp_green_total);
    CC_SAFE_RELEASE(sp_pearl_single);
    CC_SAFE_RELEASE(sp_pearl_total);
    
    CC_SAFE_RELEASE(m_dim_add);
    CC_SAFE_RELEASE(m_dim_dec);
    CC_SAFE_RELEASE(m_gif_exit);
    CC_SAFE_RELEASE(m_gif_enter);
    CC_SAFE_RELEASE(m_exchange_exit);
    CC_SAFE_RELEASE(m_exchange_enter);
    CC_SAFE_RELEASE(m_dim_exit);
    CC_SAFE_RELEASE(m_dim_enter);
    
}

void GameSubStoreLayer::reFresh()
{
    if (ly_diamond_detail->isVisible() == true) {
        GameDiamond* pDia = GameData::getSharedGameData()->getGameDiamond((DiamondType)m_item_index);
        if (m_dia_sell_cnt == 0) {
//            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("reduce_h.png");
//            sp_dia_dec->setDisplayFrame(frame);
            (m_dim_dec)->setEnabled(false);
            m_dim_enter->setEnabled(false);
        } else {
            
            (m_dim_dec)->setEnabled(true);
        }
        if (m_dia_sell_cnt >= pDia->m_cnt) {
            
            (m_dim_add)->setEnabled(false);
        } else {
            
            (m_dim_add)->setEnabled(true);
        }
    }
    
}

void GameSubStoreLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    
    setTouchEnabled(false);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPrioritySubStoreLayer, true);
    
    //notice  by andy 2015-04-02 because ccb  assign is fail.
    m_dim_add = (CCControlButton*)ly_diamond_detail_bg->getChildByTag(22);
    
    m_dim_dec =(CCControlButton*)ly_diamond_detail_bg->getChildByTag(21) ;
    (m_gif_exit)=(CCControlButton*)ly_gift_detail->getChildByTag(1);
    (m_gif_enter)=(CCControlButton*)ly_gift_detail->getChildByTag(2);
    (m_exchange_exit)=(CCControlButton*)ly_exchange_detail->getChildByTag(1)->getChildByTag(1);
    (m_exchange_enter)=(CCControlButton*)ly_exchange_detail->getChildByTag(1)->getChildByTag(4);
    (m_dim_exit)=(CCControlButton*)ly_diamond_detail_bg->getChildByTag(1);
    (m_dim_enter)=(CCControlButton*)ly_diamond_detail_bg->getChildByTag(3);
    
     m_dim_add->retain();
     m_dim_dec->retain();
    
     m_gif_exit->retain();
     m_gif_enter->retain();
    
     m_exchange_exit->retain();
     m_exchange_enter->retain();
    
     m_dim_exit->retain();
     m_dim_enter->retain();
    
    
}

bool GameSubStoreLayer::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_gift_detail", CCLayer*, this->ly_gift_detail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_diamond_detail", CCLayer*, this->ly_diamond_detail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_diamond_detail_bg", CCSprite *, this->ly_diamond_detail_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_exchange_detail", CCLayer*, this->ly_exchange_detail);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_gift_detail", CCSprite*, this->sp_gift_detail);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_gf_buy", CCSprite*, this->sp_gf_buy);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_dia_detail", CCSprite*, this->sp_dia_detail);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_dia_buy", CCSprite*, this->sp_dia_buy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_num_single", CCSprite*, this->sp_num_single);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_num_total", CCSprite*, this->sp_num_total);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_num_cnt", CCSprite*, this->sp_num_cnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_sale", CCMenuItem*, this->sp_sale);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_exchange", CCMenuItem*, this->sp_exchange);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_exc_detail", CCSprite*, this->sp_exc_detail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_exc_prompt", CCSprite*, this->sp_exc_prompt);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_exc_buy", CCSprite*, this->sp_exc_buy);
    //del by andy 2015-04-02
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sub_menu", CCMenu*, this->sub_menu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_yellow_single", CCSprite*, this->sp_yellow_single);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_yellow_total", CCSprite*, this->sp_yellow_total);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_blue_single", CCSprite*, this->sp_blue_single);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_blue_total", CCSprite*, this->sp_blue_total);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_red_single", CCSprite*, this->sp_red_single);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_red_total", CCSprite*, this->sp_red_total);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_green_single", CCSprite*, this->sp_green_single);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_green_total", CCSprite*, this->sp_green_total);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_pearl_single", CCSprite*, this->sp_pearl_single);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_pearl_total", CCSprite*, this->sp_pearl_total);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "subBuyMenu", CCMenu*, this->subBuyMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "subSaleMenu", CCMenu*, this->subSaleMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "subExchangeMenu", CCMenu*, this->subExchangeMenu);
    
    
	return true;
}


SEL_MenuHandler GameSubStoreLayer::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "exitSel", GameSubStoreLayer::exitSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSpGfBuy", GameSubStoreLayer::onSpGfBuy);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSpGfSale", GameSubStoreLayer::onSpGfSale);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSpGfExchange", GameSubStoreLayer::onSpGfExchange);
    
    return NULL;
}


SEL_CCControlHandler GameSubStoreLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonClick", GameSubStoreLayer::onButtonClick)
    return NULL;
}
void GameSubStoreLayer::onButtonClick(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    int tag = ((CCNode*)pSender)->getTag();
    switch (tag) {
        case 1:
        {
            DF_LOG("1");
            Sound::Instance()->playEffect("btn.mp3");
            removeFromParent();
        }
            break;
        case 2:
        {
            DF_LOG("2 buyGift enter m_item_index = %d",m_item_index);
            buyGift(m_item_index);
        }
            break;
        case 3:
        {
            DF_LOG("3  sellDiamond enter m_item_index = %d",m_item_index);
            sellDiamond((DiamondType)m_item_index);
        }
            break;
        case 4:
        {
            DF_LOG("4  onSpGfExchange enter  m_item_index = %d",m_item_index);
            onSpGfExchange(NULL);
        }
            break;
            case 21:
        {
            addOrReduceDiamondSellCount(false);
            Sound::Instance()->playEffect("btn.mp3");
            
            if(m_dia_sell_cnt > 0){
                m_dim_enter->setEnabled(true);
            } else {
                m_dim_enter->setEnabled(false);
            }
        }
            break;
        case 22:
        {
            addOrReduceDiamondSellCount(true);
            Sound::Instance()->playEffect("btn.mp3");
            
            
            if(m_dia_sell_cnt > 0){
                m_dim_enter->setEnabled(true);
            } else {
                m_dim_enter->setEnabled(false);
            }
        }
            break;
        default:
            break;
    }
}
 bool GameSubStoreLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    

    if(m_gif_exit->isEnabled()&&ly_gift_detail->isVisible())
          m_gif_exit->ccTouchBegan(pTouch,pEvent);
    if(m_gif_enter->isEnabled()&&ly_gift_detail->isVisible())
       m_gif_enter->ccTouchBegan(pTouch,pEvent);
    
    if(m_dim_exit->isEnabled()&&ly_diamond_detail->isVisible())
       m_dim_exit->ccTouchBegan(pTouch,pEvent);
    if(m_dim_enter->isEnabled()&&ly_diamond_detail->isVisible())
       m_dim_enter->ccTouchBegan(pTouch,pEvent);
    
    if(m_dim_dec->isEnabled()&&ly_diamond_detail->isVisible())
       (m_dim_dec)->ccTouchBegan(pTouch,pEvent);
    if(m_dim_add->isEnabled()&&ly_diamond_detail->isVisible())
       (m_dim_add)->ccTouchBegan(pTouch,pEvent);
    
    if(m_exchange_exit->isEnabled()&&ly_exchange_detail->isVisible())
        m_exchange_exit->ccTouchBegan(pTouch,pEvent);
    if(m_exchange_enter->isEnabled()&&ly_exchange_detail->isVisible())
        m_exchange_enter->ccTouchBegan(pTouch,pEvent);
    return true;

}
void GameSubStoreLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void GameSubStoreLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
    if(m_gif_exit->isEnabled()&&ly_gift_detail->isVisible())
        m_gif_exit->ccTouchEnded(pTouch,pEvent);
    if(m_gif_enter->isEnabled()&&ly_gift_detail->isVisible())
        m_gif_enter->ccTouchEnded(pTouch,pEvent);
    if(m_dim_exit->isEnabled()&&ly_diamond_detail->isVisible())
        m_dim_exit->ccTouchEnded(pTouch,pEvent);
    if(m_dim_enter->isEnabled()&&ly_diamond_detail->isVisible())
        m_dim_enter->ccTouchEnded(pTouch,pEvent);
    if(m_dim_dec->isEnabled()&&ly_diamond_detail->isVisible())
        (m_dim_dec)->ccTouchEnded(pTouch,pEvent);
    if(m_dim_add->isEnabled()&&ly_diamond_detail->isVisible())
        (m_dim_add)->ccTouchEnded(pTouch,pEvent);
    
    if(m_exchange_exit->isEnabled()&&ly_exchange_detail->isVisible())
        m_exchange_exit->ccTouchEnded(pTouch,pEvent);
    if(m_exchange_enter->isEnabled()&&ly_exchange_detail->isVisible())
        m_exchange_enter->ccTouchEnded(pTouch,pEvent);
}
void GameSubStoreLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_gif_exit->isEnabled())
        m_gif_exit->ccTouchCancelled(pTouch,pEvent);
    if(m_gif_enter->isEnabled())
        m_gif_enter->ccTouchCancelled(pTouch,pEvent);
    if(m_dim_exit->isEnabled())
        m_dim_exit->ccTouchCancelled(pTouch,pEvent);
    if(m_dim_enter->isEnabled())
        m_dim_enter->ccTouchCancelled(pTouch,pEvent);
    if(m_dim_dec->isEnabled())
        (m_dim_dec)->ccTouchCancelled(pTouch,pEvent);
    if(m_dim_add->isEnabled())
        (m_dim_add)->ccTouchCancelled(pTouch,pEvent);
    
    if(m_exchange_exit->isEnabled())
        m_exchange_exit->ccTouchCancelled(pTouch,pEvent);
    if(m_exchange_enter->isEnabled())
        m_exchange_enter->ccTouchCancelled(pTouch,pEvent);

}
bool GameSubStoreLayer::addOrReduceDiamondSellCount(bool isAdd)
{
    GameDiamond* pDia = GameData::getSharedGameData()->getGameDiamond((DiamondType)m_item_index);
    if (isAdd) {
        if (pDia->m_cnt <= m_dia_sell_cnt) {
            return false;
        } else {
            m_dia_sell_cnt++;
        }
    } else {
        if (m_dia_sell_cnt <= 0) {
            return false;
        } else {
            m_dia_sell_cnt--;
        }
    }
    if(_num_dia_sell_cnt != NULL) {
        _num_dia_sell_cnt->removeFromParent();
    }
    _num_dia_sell_cnt = NumSprite::create(m_dia_sell_cnt,GameNumberStoreSubLayerGold);
    _num_dia_sell_cnt->setPosition(sp_num_cnt->getPosition());
    sp_num_cnt->setVisible(false);
    ly_diamond_detail_bg->addChild(_num_dia_sell_cnt);
    if(_num_dia_total_price != NULL) {
        _num_dia_total_price->removeFromParent();
    }
    int totalPrice = pDia->m_price * m_dia_sell_cnt;
    _num_dia_total_price = NumSprite::create(totalPrice,GameNumberStoreLayerGold);
    _num_dia_total_price->setAnchorPoint(sp_num_total->getAnchorPoint());
    _num_dia_total_price->setPosition(sp_num_total->getPosition());
    sp_num_total->setVisible(false);
    _num_dia_total_price->setScale(0.6);
    ly_diamond_detail_bg->addChild(_num_dia_total_price);
    reFresh();
    return true;
}


void GameSubStoreLayer::sellDiamond(DiamondType pType)
{
    if(GameData::getSharedGameData()->sellGameDiamond(pType, m_dia_sell_cnt))
    {
        Sound::Instance()->playEffect("ffcoin.mp3");
    }
    removeFromParent();
}

void GameSubStoreLayer::buyGift(int pIndex)
{
    //add code here
    if (pIndex == 8) {
        
//        IPlatformFactory::sharedPlatform()->beginPurchase(Product_Gift25);
    } else if (pIndex == 9) {
        
//        IPlatformFactory::sharedPlatform()->beginPurchase(Product_Gift18);
    } else if (pIndex == 10) {
        
//        IPlatformFactory::sharedPlatform()->beginPurchase(Product_Gift12);
    } else if (pIndex == 11) {
        
//        IPlatformFactory::sharedPlatform()->beginPurchase(Product_Pearl);
    } else if (pIndex == 12) {
        
//        IPlatformFactory::sharedPlatform()->beginPurchase(Product_Gift25);
    }
}

bool GameSubStoreLayer::buyCard(CardType pType)
{
    return GameData::getSharedGameData()->buyGameCard(pType);
}

/*bool GameSubStoreLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
    
    m_bTouchedMenu = sub_menu->ccTouchBegan(pTouch, pEvent);
    
    //    if (ly_gift_detail->isVisible() == true && sp_gf_buy->boundingBox().containsPoint(point) == true) {
    //        buyGift(m_item_index);
    //        return true;
    //    }
    
    if(ly_gift_detail->isVisible() == true){
        m_bTouchedInBuyMenu = subBuyMenu->ccTouchBegan(pTouch, pEvent);
        if (m_bTouchedInBuyMenu) {
            return m_bTouchedInBuyMenu;
        }
    }
    
    
    if (ly_diamond_detail->isVisible() == true) {
        //        if (sp_dia_buy->boundingBox().containsPoint(point) == true) {
        //            sellDiamond((DiamondType)m_item_index);
        //            return true;
        //        }
        m_bTouchedInSaleMenu = subSaleMenu->ccTouchBegan(pTouch, pEvent);
        if (m_bTouchedInSaleMenu) {
            return m_bTouchedInSaleMenu;
        }
        if (sp_dia_add->boundingBox().containsPoint(point) == true) {
            addOrReduceDiamondSellCount(true);
            Sound::Instance()->playEffect("btn.mp3");
            
            if(m_dia_sell_cnt > 0){
                sp_sale->setEnabled(true);
            } else {
                sp_sale->setEnabled(false);
            }
            return true;
        }
        if (sp_dia_dec->boundingBox().containsPoint(point) == true) {
            addOrReduceDiamondSellCount(false);
            Sound::Instance()->playEffect("btn.mp3");
            
            if(m_dia_sell_cnt > 0){
                sp_sale->setEnabled(true);
            } else {
                sp_sale->setEnabled(false);
            }
            return true;
        }
    }
    
    //    if (ly_exchange_detail->isVisible() == true && sp_exc_buy->boundingBox().containsPoint(point) == true) {
    //        buyCard((CardType)m_item_index);
    //    }
    if(ly_exchange_detail->isVisible() == true){
        m_bTouchedInExchangeMenu = subExchangeMenu->ccTouchBegan(pTouch, pEvent);
        if (m_bTouchedInExchangeMenu) {
            return m_bTouchedInExchangeMenu;
        }
    }
    
    return true;
}


void GameSubStoreLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
    if (m_bTouchedInBuyMenu) {
        subBuyMenu->ccTouchMoved(pTouch, pEvent);
    }
    
    if (m_bTouchedInSaleMenu) {
        subSaleMenu->ccTouchMoved(pTouch, pEvent);
    }
    
    if (m_bTouchedInExchangeMenu) {
        subExchangeMenu->ccTouchMoved(pTouch, pEvent);
    }
    
    if (m_bTouchedMenu) {
        sub_menu->ccTouchMoved(pTouch, pEvent);
    }
}
void GameSubStoreLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        sub_menu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
    
    if (m_bTouchedInBuyMenu) {
        subBuyMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedInBuyMenu = false;
    }
    
    if (m_bTouchedInSaleMenu) {
        subSaleMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedInSaleMenu = false;
    }
    
    if (m_bTouchedInExchangeMenu) {
        subExchangeMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedInExchangeMenu = false;
    }
}

void GameSubStoreLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        sub_menu->ccTouchCancelled(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
    
    if (m_bTouchedInBuyMenu) {
        subBuyMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedInBuyMenu = false;
    }
    
    if (m_bTouchedInSaleMenu) {
        subSaleMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedInSaleMenu = false;
    }
    
    if (m_bTouchedInExchangeMenu) {
        subExchangeMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedInExchangeMenu = false;
    }
}
*/
void GameSubStoreLayer::onEnter()
{
    CCLayer::onEnter();
    DF_LOG("button=%x, button=%x",ly_gift_detail->getChildByTag(1),ly_gift_detail->getChildByTag(2));
}

void GameSubStoreLayer::onExit()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void GameSubStoreLayer::exitSel(CCObject *pSender)
{
    Sound::Instance()->playEffect("btn.mp3");
    //del by lqg 2015-04-07
    removeFromParent();
}


void GameSubStoreLayer::onSpGfBuy(CCObject *pSender)
{
    buyGift(m_item_index);
}

void GameSubStoreLayer::onSpGfSale(CCObject *pSender)
{
    sellDiamond((DiamondType)m_item_index);
}

void GameSubStoreLayer::onSpGfExchange(CCObject *pSender)
{
    bool buyResult = buyCard((CardType)m_item_index);
    if (buyResult)
    {
        if (dynamic_cast<GameStoreLayer*>(getParent()))
        {
            // 更新数据
            ((GameStoreLayer*)getParent())->exchangeSwSel(NULL);
        }
        exitSel(NULL);
    }
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

GameStoreLayer::GameStoreLayer()
:CCLayer(),
ly_tableView(NULL),
menu_store(NULL),
menu_first(NULL),
m_pGoldCells(NULL),
m_pMarketCells(NULL),
m_pExhangeCells(NULL),
_tableType(GameStoreLayerTableGold),
_tableView(NULL),
m_bTouchedTable(false),
m_bTouchedMenu(false),
m_bTouchedFirst(false),
bn_gold(NULL),
bn_market(NULL),
bn_exchange(NULL),
bn_exit(NULL),
sp_playerGold(NULL),
sp_text(NULL),
ly_ui(NULL),
m_sFastBuyBg(NULL),
bn_fastBuy(NULL),
bn_fastBuyClose(NULL)
{
    m_iToken = -1;
    m_bFastBuy = false;
}

GameStoreLayer::~GameStoreLayer()
{
    CC_SAFE_RELEASE(ly_tableView);
    CC_SAFE_RELEASE(menu_store);
    CC_SAFE_RELEASE(menu_first);

    
    
    CC_SAFE_RELEASE(m_pGoldCells);
    CC_SAFE_RELEASE(m_pMarketCells);
    CC_SAFE_RELEASE(m_pExhangeCells);
    
    CC_SAFE_RELEASE(_tableView);
    
    CC_SAFE_RELEASE(bn_gold);
    CC_SAFE_RELEASE(bn_market);
    CC_SAFE_RELEASE(bn_exchange);
    
    CC_SAFE_RELEASE(sp_playerGold);
    CC_SAFE_RELEASE(sp_text);
    
    CC_SAFE_RELEASE(ly_ui);
    CC_SAFE_RELEASE(m_sFastBuyBg);
    CC_SAFE_RELEASE(bn_fastBuy);
    CC_SAFE_RELEASE(bn_fastBuyClose);
}

CCScene* GameStoreLayer::scene(bool pFastVisible)
{
	CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("GameStoreLayer", GameStoreLayerBuilderLoad::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	GameStoreLayer* node = (GameStoreLayer*)ccbReader->readNodeGraphFromFile("ios/ccbResources/GameStore.ccbi", sc);
    ccbReader->release();
    
	if (node){
		sc->addChild(node);
        node->setTag(888);
    }
	return sc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void GameStoreLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{
    setTouchEnabled(false);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPriorityStore, true);
    //    this->scheduleUpdate();
    
    sp_playerGold->setVisible(false);
    
}

bool GameStoreLayer::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_tableView", CCLayer*, this->ly_tableView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu_store", CCMenu*, this->menu_store);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu_first", CCMenu*, this->menu_first);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_gold", CCMenuItemImage*, this->bn_gold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_market", CCMenuItemImage*, this->bn_market);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_exchange", CCMenuItemImage*, this->bn_exchange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_exit", CCMenuItemImage *, this->bn_exit);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_playerGold", CCSprite*, this->sp_playerGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_text", CCSprite*, this->sp_text);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_ui", CCLayer *, this->ly_ui);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sFastBuyBg", CCSprite *, this->m_sFastBuyBg);


    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_fastBuy", CCMenuItemImage *, this->bn_fastBuy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bn_fastBuyClose", CCMenuItemImage *, this->bn_fastBuyClose);
	return true;
}

SEL_MenuHandler GameStoreLayer::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "goldSwSel", GameStoreLayer::goldSwSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "marketSwSel", GameStoreLayer::marketSwSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "exchangeSwSel", GameStoreLayer::exchangeSwSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "exitSel", GameStoreLayer::exitSel);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "fastBuyCallback", GameStoreLayer::fastBuyCallback);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "fastCloseCallback", GameStoreLayer::fastCloseCallback);
	return NULL;
}

SEL_CCControlHandler GameStoreLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

bool GameStoreLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    DF_LOG("GameStoreLayer::ccTouchBegan enter");
    DF_LOG("GameStoreLayer::ccTouchBegan menu_store enter");
    m_bTouchedMenu = menu_store->ccTouchBegan(pTouch, pEvent);
    DF_LOG("GameStoreLayer::ccTouchBegan menu_store exit   m_bTouchedMenu =%d",m_bTouchedMenu);
    if (m_bTouchedMenu == false) {
        
        m_bTouchedFirst = menu_first->ccTouchBegan(pTouch, pEvent);
        DF_LOG("GameStoreLayer::ccTouchBegan menu_first exit   m_bTouchedFirst =%d",m_bTouchedFirst);
    }
    if (m_bTouchedFirst == false) {
        
        m_bTouchedTable = _tableView->ccTouchBegan(pTouch, pEvent);
        DF_LOG("GameStoreLayer::ccTouchBegan _tableView exit   m_bTouchedTable =%d",m_bTouchedTable);
    }
    
    return true;
}

void GameStoreLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    if (m_bTouchedMenu) {
        menu_store->ccTouchMoved(pTouch, pEvent);
    }
    
    if (m_bTouchedTable) {
        _tableView->ccTouchMoved(pTouch, pEvent);
    }
    if (m_bTouchedFirst) {
        
       menu_first->ccTouchMoved(pTouch, pEvent);
    }
    
}
void GameStoreLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        menu_store->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
        DF_LOG("GameStoreLayer::ccTouchEnded menu_store exit   m_bTouchedMenu =%d",m_bTouchedMenu);
    }
    
    if (m_bTouchedTable) {
        _tableView->ccTouchEnded(pTouch, pEvent);
        m_bTouchedTable = false;
        DF_LOG("GameStoreLayer::ccTouchEnded _tableView exit   m_bTouchedTable =%d",m_bTouchedTable);
    }
    if (m_bTouchedFirst) {
        
        menu_first->ccTouchEnded(pTouch, pEvent);
        m_bTouchedFirst = false;
        DF_LOG("GameStoreLayer::ccTouchEnded menu_first exit   m_bTouchedFirst =%d",m_bTouchedFirst);
    }
}

void GameStoreLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        menu_store->ccTouchCancelled(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
    
    if (m_bTouchedTable) {
        _tableView->ccTouchEnded(pTouch, pEvent);
        m_bTouchedTable = false;
    }
    if (m_bTouchedFirst) {
        
        menu_first->ccTouchCancelled(pTouch, pEvent);
        m_bTouchedFirst = false;
    }
    
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
void GameStoreLayer::onEnter()
{
	CCLayer::onEnter();
    
    GameData::getSharedGameData()->setDataPoint(DT_Shop, this);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameStoreLayer::renewTableView), "Game_Global_Score_Change", NULL);
    
    bn_gold->setEnabled(false);
    
    fillUIElements();
    
}

void GameStoreLayer::onExit()
{
    GameData::getSharedGameData()->setDataPoint(DT_Shop, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
    
}

void GameStoreLayer::goldSwSel(CCObject *pSender)
{
    _tableType = GameStoreLayerTableGold;
    //    _tableView->reloadData();
    
    bn_gold->setEnabled(false);
    bn_market->setEnabled(true);
    bn_exchange->setEnabled(true);
    
    renewTableView();
    
    CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("txt0.png");
    sp_text->setDisplayFrame(frame);
    Sound::Instance()->playEffect("btn.mp3");
}

void GameStoreLayer::marketSwSel(CCObject *pSender)
{
    
    _tableType = GameStoreLayerTableMarket;
    
    bn_gold->setEnabled(true);
    bn_market->setEnabled(false);
    bn_exchange->setEnabled(true);
    
    renewTableView();
    CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("txt1.png");
    sp_text->setDisplayFrame(frame);
    Sound::Instance()->playEffect("btn.mp3");
    
}

void GameStoreLayer::exchangeSwSel(CCObject *pSender)
{
    _tableType = GameStoreLayerTableExchange;
    //    _tableView->reloadData();
    
    
    bn_gold->setEnabled(true);
    bn_market->setEnabled(true);
    bn_exchange->setEnabled(false);
    
    renewTableView();
    CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("txt2.png");
    sp_text->setDisplayFrame(frame);
    Sound::Instance()->playEffect("btn.mp3");
}

void GameStoreLayer::exitSel(CCObject *pSender)
{
    DF_LOG("GameStoreLayer::exitSel enter");
    removeFromParentAndCleanup(true);
    
    Sound::Instance()->playEffect("btn.mp3");
    DF_LOG("GameStoreLayer::exitSel exit");
}

void GameStoreLayer::fastBuyCallback(cocos2d::CCObject *pSender)
{
    int pToken = arc4random() % 9999;
    setToken(pToken);
    setProductType(Product_Fb_Coin10);
    buyGoods(Product_Fb_Coin10, GameData::getSharedGameData()->genOrderId(Product_Fb_Coin10, pToken).c_str(), pToken);
    
}

void GameStoreLayer::fastCloseCallback(cocos2d::CCObject *pSender)
{
    setFastBuyVisible(false);
    exitSel(NULL);
}

/**
 * cell size for a given index
 *
 * @param idx the index of a cell to get a size
 * @return size of a cell at given index
 */
CCSize GameStoreLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx) {
    return cellSizeForTable(table);
};


/**
 * cell height for a given table.
 *
 * @param table table to hold the instances of Class
 * @return cell size
 */
CCSize GameStoreLayer::cellSizeForTable(CCTableView *table) {
    CCLayer* ly = NULL;
    switch (_tableType)
    {
        case GameStoreLayerTableGold:
            ly = (CCLayer*)m_pGoldCells->objectAtIndex(0);
            break;
        case GameStoreLayerTableMarket:
            ly = (CCLayer*)m_pMarketCells->objectAtIndex(0);
            break;
        case GameStoreLayerTableExchange:
            ly = (CCLayer*)m_pExhangeCells->objectAtIndex(0);
            break;
        default:
            break;
    }
    
    if (ly != NULL) {
        return ly->getContentSize();
    }
    return CCSizeZero;
}


/**
 * a cell instance at a given index
 *
 * @param idx index to search for a cell
 * @return cell found at idx
 */
CCTableViewCell* GameStoreLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    tableCell *cell =(tableCell*) table->dequeueCell();
    
    switch (_tableType) {
        case GameStoreLayerTableGold:
            
        {
            CCLayer* ly = (CCLayer*)m_pGoldCells->objectAtIndex(idx);
            if (ly == NULL) {
                return NULL;
            }
            ly->setVisible(true);
            ly->setPosition(CCPointZero);
            ly->setAnchorPoint(CCPointZero);
            ly->setUserData((void*)(idx+1));
            if (cell != NULL) {
                ly->removeFromParentAndCleanup(false);
            }
            cell = tableCell::createGoldCell(ly);
        }
            break;
            
        case GameStoreLayerTableMarket:
            
        {
            CCLayer* ly = (CCLayer*)m_pMarketCells->objectAtIndex(idx);
            if (ly == NULL) {
                return NULL;
            }
            ly->setVisible(true);
            ly->setPosition(CCPointZero);
            ly->setAnchorPoint(CCPointZero);
            ly->setUserData((void*)(idx+1));
            if (cell != NULL) {
                ly->removeFromParentAndCleanup(false);
            }
            cell = tableCell::createMarketCell(ly);
        }
            break;
            
        case GameStoreLayerTableExchange:
            
        {
            CCLayer* ly = (CCLayer*)m_pExhangeCells->objectAtIndex(idx);
            if (ly == NULL) {
                return NULL;
            }
            ly->setVisible(true);
            ly->setPosition(CCPointZero);
            ly->setAnchorPoint(CCPointZero);
            ly->setUserData((void*)(idx+1));
            if (cell != NULL) {
                ly->removeFromParentAndCleanup(false);
            }
            cell = tableCell::createExchangeCell(ly);
        }
            break;
            
        default:
            break;
    }
    
    
    cell->m_root_layer = this;
    return cell;
}


/**
 * Returns number of cells in a given table view.
 *
 * @return number of cells
 */
unsigned int GameStoreLayer::numberOfCellsInTableView(CCTableView *table)
{
    int cntRow = 0;
    switch (_tableType) {
        case GameStoreLayerTableGold:
            cntRow = m_pGoldCells->count();
            break;
        case GameStoreLayerTableMarket:
            cntRow = m_pMarketCells->count();
            break;
        case GameStoreLayerTableExchange:
            cntRow = m_pExhangeCells->count();
            break;
            
        default:
            break;
    }
    return cntRow;
}



void GameStoreLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    int tag =cell->getTag();
    DF_LOG("tag = %d",tag);
}


void GameStoreLayer::fillUIElements()
{
    
    if (m_pGoldCells == NULL) {
        this->setGoldCells(CCArray::createWithCapacity(GameGoldCellRowTag2));
    }
    for (int i = GameGoldCellRowTag1; i <= GameGoldCellRowTag2; i++) {
        CCLayer* ly = (CCLayer*)ly_tableView->getChildByTag(i);
        if (ly != NULL) {
            m_pGoldCells->addObject(ly);
            ly->removeFromParentAndCleanup(false);
        }
        
    }
    
    if (m_pMarketCells == NULL) {
        this->setMarketCells(CCArray::createWithCapacity(GameMarketCellRowTag2));
    }
    for (int i = GameMarketCellRowTag1; i <= GameMarketCellRowTag2; i++) {
        CCLayer* ly = (CCLayer*)ly_tableView->getChildByTag(i);
        if (ly != NULL) {
            m_pMarketCells->addObject(ly);
            ly->removeFromParentAndCleanup(false);
        }
        
    }
    
    if (m_pExhangeCells == NULL) {
        this->setExhangeCells(CCArray::createWithCapacity(GameExchangeCellRowTag4));
    }
    for (int i = GameExchangeCellRowTag1; i <= GameExchangeCellRowTag4; i++) {
        CCLayer* ly = (CCLayer*)ly_tableView->getChildByTag(i);
        if (ly != NULL) {
            m_pExhangeCells->addObject(ly);
            ly->removeFromParentAndCleanup(false);
        }
        
    }
    renewTableView();
    
}


void GameStoreLayer::renewTableView()
{
 //   removeChildByTag(GameScoreNumberTag);
    //del by lqg 2015-04-07
//    NumSprite* sp_num = NumSprite::create(GameData::getSharedGameData()->score(), GameNumberSotreUp);
//    sp_num->setPosition(sp_playerGold->getPosition());
//    sp_num->setScale(sp_playerGold->getScale());
//    addChild(sp_num,sp_playerGold->getZOrder(),GameScoreNumberTag);
    
    if (_tableView != NULL)
    {
        _tableView->removeFromParent();
        _tableView = NULL;
        CCArray* arr = NULL;
        if (_tableType == GameStoreLayerTableGold)
        {
            arr = m_pGoldCells;
        }
        else if (_tableType == GameStoreLayerTableMarket)
        {
            arr = m_pMarketCells;
        }
        else
        {
            arr = m_pExhangeCells;
        }
        for (int i = 0; i < arr->count(); i++)
        {
            CCLayer* ly = (CCLayer*)arr->objectAtIndex(i);
            ly->removeFromParentAndCleanup(false);
        }
    }
    _tableView = CCTableView::create(this, ly_tableView->getContentSize());
    _tableView->setAnchorPoint(CCPointZero);
    _tableView->setPosition(CCPointZero);
    _tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    _tableView->setDirection(kCCScrollViewDirectionVertical);
    _tableView->retain();
    
    _tableView->reloadData();
    
    //    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(EPriorityStoreTable, _tableView);
    
    ly_tableView->addChild(_tableView);
}

void GameStoreLayer::buySuccess(int token)
{
    if (m_iToken == token)
    {
        GameData::getSharedGameData()->provideProduct(m_ProductType);
    }
}

void GameStoreLayer::hideWaitingLayer()
{
//    setTouchEnabled(true);
}

void GameStoreLayer::showWaitingLayer()
{
//    setTouchEnabled(false);
}

void GameStoreLayer::setFastBuyVisible(bool pVisible)
{
    m_bFastBuy = pVisible;
    m_sFastBuyBg->setVisible(pVisible);
    bn_fastBuy->setVisible(pVisible);
    bn_fastBuyClose->setVisible(pVisible);
    
    ly_ui->setVisible(!pVisible);
    ly_tableView->setVisible(!pVisible);
    bn_gold->setVisible(!pVisible);
    bn_market->setVisible(!pVisible);
    bn_exchange->setVisible(!pVisible);
    bn_exit->setVisible(!pVisible);
    sp_text->setVisible(!pVisible);
    if (getChildByTag(GameScoreNumberTag))
    {
        getChildByTag(GameScoreNumberTag)->setVisible(!pVisible);
    }
}

#endif
