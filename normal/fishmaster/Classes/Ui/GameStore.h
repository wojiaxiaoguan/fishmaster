//
//  GameStore.h
//  fish
//
//  
//
//

#ifndef __fish__GameStore__
#define __fish__GameStore__

#include <iostream>
#include "headerLibrary.h"
#include "GameData.h"
#include "Helper.h"



#define GameGoldCellRowTag1 1
#define GameGoldCellRowTag2 2
//#define GameGoldCellRowTag3 3
#define GameMarketCellRowTag1 11
#define GameMarketCellRowTag2 12
#define GameExchangeCellRowTag1 21
#define GameExchangeCellRowTag2 22
#define GameExchangeCellRowTag3 23
#define GameExchangeCellRowTag4 24


#define GameTableCellAddTag  20

enum StoreTableType{
    GameStoreLayerTableGold = 1,
    GameStoreLayerTableMarket,
    GameStoreLayerTableExchange
};

#define GameScoreNumberTag  21

/**
 * Store UI
 */
class GameStoreLayer : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCTableViewDataSource,
public CCTableViewDelegate,
public CCNodeLoaderListener
{
public:
	GameStoreLayer();
	virtual ~GameStoreLayer();
    
	static CCScene *scene(bool pFastVisible);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameStoreLayer, create);
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    /**
     * cell size for a given index
     *
     * @param idx the index of a cell to get a size
     * @return size of a cell at given index
     */
    CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    CCSize cellSizeForTable(CCTableView *table);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    unsigned int numberOfCellsInTableView(CCTableView *table);
    
    void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
    void scrollViewDidScroll(CCScrollView* view){};
    void scrollViewDidZoom(CCScrollView* view){};
    
    void buySuccess(int token);
    void hideWaitingLayer();
    void showWaitingLayer();
    
    void setToken(int pToken) { m_iToken = pToken; };
    void setProductType(ProductType pType) { m_ProductType = pType; };
    
    void setFastBuyVisible(bool pVisible);
    bool getFastBuy() { return m_bFastBuy; };
    
    void buyGoods(ProductType pType, const char* orderId, int token);
    
    
    void fastBuyCallback(CCObject *pSender);
    void fastCloseCallback(CCObject* pSender);
    

    
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
private:
	void onEnter();
    
	void onExit();
private:
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pGoldCells, GoldCells);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pMarketCells, MarketCells);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pExhangeCells, ExhangeCells);
    
    void goldSwSel(CCObject *pSender);
    void marketSwSel(CCObject *pSender);
    void exchangeSwSel(CCObject *pSender);
    void exitSel(CCObject *pSender);
    
    
    
    void fillUIElements();
    
    CCLayer* ly_tableView;
    
    CCMenu* menu_store;
    CCMenu* menu_first;
    

    CCMenuItemImage* bn_gold;
    CCMenuItemImage* bn_market;
    CCMenuItemImage* bn_exchange;
    CCMenuItemImage* bn_exit;
    
    CCTableView*	_tableView;
    StoreTableType _tableType;
    
    CCSprite* sp_playerGold;
    CCSprite* sp_text;
    
    bool m_bTouchedMenu;
    bool m_bTouchedFirst;

    bool m_bTouchedTable;
    
    void renewTableView();
    
    int m_iToken;
    ProductType m_ProductType;
    
    CCLayer*    ly_ui;
    CCSprite*   m_sFastBuyBg;
    CCMenuItemImage*    bn_fastBuy;
    CCMenuItemImage*    bn_fastBuyClose;
    bool        m_bFastBuy;
    
    
};


class GameStoreLayerBuilderLoad : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameStoreLayerBuilderLoad, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameStoreLayer);
};



class GameSubStoreLayer : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener
{
public:
    GameSubStoreLayer();
    virtual ~GameSubStoreLayer();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameSubStoreLayer, create);
    
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void onButtonClick(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
private:
	virtual void onEnter();
    
	virtual void onExit();
    
    NumSprite* _num_dia_sell_cnt;
    NumSprite* _num_dia_total_price;
    
    void exitSel(CCObject *pSender);
    void onSpGfBuy(CCObject *pSender);
    void onSpGfSale(CCObject *pSender);
    void onSpGfExchange(CCObject *pSender);
    
    bool m_bTouchedMenu;
    
    bool addOrReduceDiamondSellCount(bool isAdd);
    
    void sellDiamond(DiamondType pType);
    void buyGift(int pIndex);
    bool buyCard(CardType pType);
    
    
public:
    void reFresh();
    int m_item_index; //start from 1
    
    int m_dia_sell_cnt;
    
    CCLayer* ly_gift_detail;
    CCSprite* sp_gift_detail;
    //CCSprite* sp_gf_buy;
    
    
    CCLayer* ly_diamond_detail;
    CCSprite* ly_diamond_detail_bg;
    CCSprite* sp_dia_detail;
    //CCSprite* sp_dia_buy;
    CCSprite* sp_num_single;
    CCSprite* sp_num_total;
    CCSprite* sp_num_cnt;
    CCMenuItem* sp_sale;
    CCMenuItem* sp_exchange;
    
    
    CCLayer* ly_exchange_detail;
    CCSprite* sp_exc_detail;
    CCSprite* sp_exc_prompt;
    //CCSprite* sp_exc_buy;
    CCSprite* sp_yellow_single;
    CCSprite* sp_yellow_total;
    CCSprite* sp_blue_single;
    CCSprite* sp_blue_total;
    CCSprite* sp_red_single;
    CCSprite* sp_red_total;
    CCSprite* sp_green_single;
    CCSprite* sp_green_total;
    CCSprite* sp_pearl_single;
    CCSprite* sp_pearl_total;
    //del by andy 2015-04-02
    //CCMenu* sub_menu;
    
    CCMenu *subBuyMenu;
    bool m_bTouchedInBuyMenu;
    
    CCMenu *subSaleMenu;
    bool m_bTouchedInSaleMenu;
    
    CCMenu *subExchangeMenu;
    bool m_bTouchedInExchangeMenu;
    
    CCControlButton * m_dim_add;
    CCControlButton* m_dim_dec;
    
    CCControlButton * m_gif_exit;
    CCControlButton* m_gif_enter;
    
    
    CCControlButton * m_dim_exit;
    CCControlButton* m_dim_enter;
    
    CCControlButton * m_exchange_exit;
    CCControlButton* m_exchange_enter;
   
    
    
};


class GameSubStoreLayerBuilderLoad : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSubStoreLayerBuilderLoad, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameSubStoreLayer);
};


class tableCell : public cocos2d::extension::CCTableViewCell
,public CCTouchDelegate
{
public:
    tableCell();
    virtual ~tableCell();
    
    static tableCell* createGoldCell( CCLayer *cell);
    static tableCell* createMarketCell( CCLayer *cell);
    static tableCell* createExchangeCell( CCLayer *cell);
    
    GameStoreLayer* m_root_layer;
    
protected:
    int touchIndex; // from left to right 1,2,3,4
    bool isTouchMove;
    CCPoint touchPoint; // fix touch move
    
    //转换到世界坐标
    CCRect convertToWorldSpace(CCNode *pNode);
    
protected:
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void draw();
    
private:
    void initGoldWithLayer(CCLayer *cell);
    void initMarketWithLayer( CCLayer *cell);
    void initExchangeWithLayer( CCLayer *cell);
    
    void fillDiamondItem(CCSprite *pDia,DiamondType pType);
    void fillCardItem(CCSprite *pCard,CardType pType);
    
    StoreTableType m_type;
    
    
    GameSubStoreLayer* addDetailLayer();
    void touchGoldCell(int row,int col);
    
    void touchMarketCell(int row,int col);
    
    void touchExchangeCell(int row,int col);
};

#endif /* defined(__fish__GameStore__) */
