

#ifndef __FishingJoyStep1__RollNum__
#define __FishingJoyStep1__RollNum__

#include <iostream>
#include "cocos2d.h"
#include "common.h"

class GameLayer;

/**
 数字的每个位，主要控制这个位上得数字的滚动
 */
class RollNum : public cocos2d::CCSprite
{
public:
    RollNum();
    virtual ~RollNum();
    CREATE_FUNC(RollNum);
    
    //设置要滚动到得数字，以及滚动的方向
    void setNumber(int var, bool bUp);
    int getNumber();
private:
    bool init();
    CC_SYNTHESIZE(bool, m_bUp, UpDirection);
    int m_nNumber;
    int m_nCurTexH;//当前显示数字纹理的位置
    int m_nEndTexH;//数字纹理的高度
    bool m_bRolling;//标记当前这个数字是否在滚动
    cocos2d::CCTexture2D *m_pTexture;//数字纹理
    //不断更新数字纹理显示的位置，达到滚动数字的效果
    void updateNumber(cocos2d::CCTime dt);
};

/**
 管理数字的每个位，包括控制每个位的位置，及解析数字的每个位，调度RollNum进行显示
 */
class RollNumGroup : public cocos2d::CCObject
{
public:
    RollNumGroup();
    virtual ~RollNumGroup();
    static RollNumGroup *createWithGameLayer(GameLayer *pGameLayer, int nDigit);
    //设置显示的数字，内部会将数字分解成单个数，然后逐个调用对应的setNumber方法
    void setValue(int nValue);
    //初始化各个数字的位置，参数指定最右边的那个数字的位子
    void setPosition(cocos2d::CCPoint pt);
private:
//    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
    //存储数字的每个位
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pRollNumArray, RollNumArray);
    cocos2d::CCPoint m_ptPosition;
    int m_nDigit;//展示数字的位数
    int m_nValue;//被展示的数字
    bool initWithGameLayer(GameLayer *pGameLayer, int nDigit);
};

#endif /* defined(__FishingJoyStep1__RollNum__) */
