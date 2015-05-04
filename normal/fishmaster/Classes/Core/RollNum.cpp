//
//  RollNum.cpp
//  FishingJoy
//
//  
//
//

#include "RollNum.h"
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

#define NUMBERHEIGHT    30
#define NUMBERWIDTH     25
#define TEXTUREHEIGHT   300


RollNum::RollNum():m_nNumber(0), m_bUp(true), m_nCurTexH(0), m_nEndTexH(0), m_bRolling(false), m_pTexture(NULL)
{
    
}

RollNum::~RollNum()
{
    this->unscheduleAllSelectors();
}

bool RollNum::init()
{
    CCSpriteFrame *tpFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("number.png");
    m_pTexture = tpFrame->getTexture();
    //初始默认截取数字0的位置进行显示
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(m_pTexture, CCRectMake(0, 0, NUMBERWIDTH, NUMBERHEIGHT));
    this->initWithSpriteFrame(pFrame);
    this->setScale(1.0f);
    return true;
}

void RollNum::updateNumber(cocos2d::CCTime dt)
{
    if(m_bRolling && m_nCurTexH == m_nEndTexH)
    {
        //标记为数字滚动中，且滚动数字纹理到指定位置m_nEndTexH，注销updateNumber,停止滚动
        this->unschedule(schedule_selector(RollNum::updateNumber));
        m_bRolling = false;
        return;
    }

    //每次向上或向下滚动4px,在数字纹理中，每两两数字的上下间隔为4px,数字本身高度为16px
    if(m_bUp)
    {
        m_nCurTexH += 5;
        if(m_nCurTexH >= TEXTUREHEIGHT)
            //数字往增大方向滚动到纹理末尾，就从头开始，形成循环
            m_nCurTexH = 0;
    }
    else
    {
        m_nCurTexH -= 5;
        if(m_nCurTexH < 0)
            //数字往减小方向滚动到纹理末尾，就从尾部开始，形成循环
            m_nCurTexH = TEXTUREHEIGHT;
    }

    int h = m_nCurTexH;
    if(m_nCurTexH >= TEXTUREHEIGHT - NUMBERHEIGHT)
        //如果进入最后一个数字的高度范围，则从最后一个数字的位置开始
        h = TEXTUREHEIGHT - NUMBERHEIGHT;
    //截取指定范围的数字纹理
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(m_pTexture, CCRectMake(0, h, NUMBERWIDTH, NUMBERHEIGHT));
    //更新自己负责的位的展现的数字纹理
    this->setDisplayFrame(pFrame);   
    m_bRolling = true;
}

void RollNum::setNumber(int var, bool bUp)
{
    this->unschedule(schedule_selector(RollNum::updateNumber));
    m_nNumber = var;
    m_bUp = bUp;
    //计算当前位的数字纹理滚动到位置
    m_nEndTexH = m_nNumber * (NUMBERHEIGHT);
    //周期更新数字纹理的位置，形成滚动效果
    this->schedule(schedule_selector(RollNum::updateNumber), 0.02f);
}

int RollNum::getNumber()
{
    return m_nNumber;
}

////////////////////////////////////////////////////////////////////////////////////////////////

RollNumGroup *RollNumGroup::createWithGameLayer(GameLayer *pGameLayer, int nDigit)
{
    RollNumGroup *pRollNumGroup = new RollNumGroup();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("number.plist");
    if(pRollNumGroup && pRollNumGroup->initWithGameLayer(pGameLayer, nDigit))
    {
        //将自己设置为内存自动管理的对象
        pRollNumGroup->autorelease();
        return pRollNumGroup;
    }
    else
    {
        CC_SAFE_DELETE(pRollNumGroup);
        return NULL;
    }
}

RollNumGroup::RollNumGroup():m_pRollNumArray(NULL), m_nValue(0)
{
    
}

RollNumGroup::~RollNumGroup()
{
    CC_SAFE_RELEASE(m_pRollNumArray);
}

bool RollNumGroup::initWithGameLayer(GameLayer *pGameLayer, int nDigit)
{
    m_pGameLayer = pGameLayer;
    //装载数字纹理
//    CCSpriteFrame *tpFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("number.png");
//    CCTexture2D *pTex = tpFrame->getTexture();
//    m_pBatchNode = CCSpriteBatchNode::createWithTexture(pTex);
    //将积分榜添加到主游戏界面上
//    m_pGameLayer->addChild(m_pBatchNode, 100);
    this->setRollNumArray(CCArray::createWithCapacity(nDigit));
    for(int i = 0; i < nDigit; i++)
    {
        //创建积分榜中的每一个数字位
        RollNum *pRollNum = RollNum::create();
        m_pRollNumArray->addObject(pRollNum);
        //将数字位显示到主游戏界面上
//        m_pBatchNode->addChild(pRollNum);
        m_pGameLayer->addChild(pRollNum,0);
    }
    
    return true;
}

void RollNumGroup::setPosition(cocos2d::CCPoint pt)
{
    m_ptPosition = pt;//积分榜的个位的位置
    for(int i = 0; i < m_pRollNumArray->count(); ++i)
    {
        RollNum *pRollNum = (RollNum *)m_pRollNumArray->objectAtIndex(i);
        pRollNum->setPosition(pt);
        //坐标从右往左移动，间隔20.7px
        pt.x -= NUMBERWIDTH;
    }
}

void RollNumGroup::setValue(int nValue)
{
    //设置的数字与显示的一直时，直接返回
    if(m_nValue == nValue)
        return;
    //设置积分榜中得数字滚动的方向
    bool bUp = m_nValue < nValue;
    m_nValue = nValue;
    for(int i = 0; i < m_pRollNumArray->count(); ++i)
    {
        RollNum *pRollNum = (RollNum *)m_pRollNumArray->objectAtIndex(i);
        int num = nValue % 10;//取得与显示的积分榜中的末位上的数
        //将m_pRollNumArray 中的第一个RollNum定义为个位，第二位为十位，依次类推
        if(pRollNum->getNumber() != num)
            //调度相应位上数字滚动
            pRollNum->setNumber(num, bUp);
        //去掉预显示的积分数的末位，进入下一位数字显示调度
        nValue = nValue / 10;
    }
}




