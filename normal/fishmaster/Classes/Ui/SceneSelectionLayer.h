
#ifndef __fish__SceneSelectionLayer__
#define __fish__SceneSelectionLayer__

#include "headerLibrary.h"
#include "SceneSelection.h"

enum SceneItemTag {
    TagBG,
    TagTitle,
    TagDesc,
    TagExclusive,
    TagImage,
    TagMenu,
    TagLockTag,

    SceneItemTagNum
};


#define CCB_CLASS_NAME SceneSelectionLayer

class SceneSelectionManager;

class CCB_CLASS_NAME : public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener,
public CCTableViewDataSource,
public CCTableViewDelegate
{
public:
	CCB_CLASS_NAME();
	virtual ~ CCB_CLASS_NAME();
    
	static CCScene *scene();
    
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCB_CLASS_NAME, create);
    //解锁
    void onActionClicked(CCObject *pSender);
    
private:
	virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    
private:
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){}
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){}
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
	virtual CCSize cellSizeForTable(CCTableView *table);
    //CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    int calcTableOffset( int viewHeight, int cellHeight, int cellCount, int cellIndex );

    
private:
	void onEnter();
    
	void onExit();
	
    
    //退出
    void onReturnClicked(CCObject *pSender);
    
    //填充ui元素
    void fillUIElements();

    void doEnterScene(Scene s);
    void doUnlockScene(Scene s);
    
    void onUnlockSceneNotify(CCObject *obj);
    
private:
    CCTableView*	_tableView;
    
    CCSprite *cb_spSceneBG;
    CCSprite *cb_spScene;
    CCSprite *cb_spLockFlag;
    
    CCLabelTTF *cb_lblTitle;
    CCLabelTTF *cb_lblDesc;
    CCLabelTTF *cb_lblExclusive;
    
    CCLayer *cb_layerSceneTemplate;
    CCLayer *cb_layerContainer;
    CCLayer *cb_layerCellTemplate;
    
    CCMenu *cb_menuAction;
    CCMenuItemImage *cb_btnAction;
    
    CCMenu *cb_menuReturn;
    CCMenuItemImage *cb_btnReturn;
    
    bool isTouchInTableView;
    bool isTouchInMenu;
    
    SceneSelectionManager *manger;
    
};


class SceneTableView : public CCTableView {
public:
    static CCTableView* create(CCTableViewDataSource* dataSource, CCSize size);
    
    void relocateContainer(bool animated);
    void setOffsetInPixels( float pixel);
    
private:
    float offset;
};


class SceneCell : public CCTableViewCell, public CCTouchDelegate
{
public:
    SceneCell();
    virtual ~SceneCell();
    
    static SceneCell* create( CCLayer *tmpl);
    void fill(int index, SceneSelectionManager *manger );
protected:
    
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
    
    void initWithTemplate(CCLayer *tmpl);
    
    void addLabel( CCLabelTTF *tmpl  );

private:
    bool isActionClicked;
    CCMenu *menuAction;
};


class XConn(CCB_CLASS_NAME, BuilderLoad) : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(XConn(CCB_CLASS_NAME, BuilderLoad), loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCB_CLASS_NAME);
};


#endif /* defined(__fish__SceneSelectionLayer__) */
