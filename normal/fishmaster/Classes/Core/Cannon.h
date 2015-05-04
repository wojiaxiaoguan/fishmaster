//
//  Cannon.h
//
//  
//
//

#ifndef FishingJoyStep1_Cannon_h
#define FishingJoyStep1_Cannon_h

#include "headerLibrary.h"

/*类型声明，避免过多依赖其他头文件 参考[HC1]*/
class GameLayer;

enum CannonType{
    Red_Cannon2 = 1,
    Red_Cannon3,
    Red_Cannon4,
    Gold_Cannon2,
    Gold_Cannon3,
    Gold_Cannon4,
    Power_Cannon,
    Laser_Cannon,
    Knife_Cannon, // 新超能武器-刀阵旋风 使用子弹的方式
    Ele_Cannon // 电磁风暴
};

#define ExpNumberTag          502
#define BonusTimeNumberTag    501
#define CannonScoreNumberTag    500
#define CannonSpecDuringTime  12
#define CannonSwitchTag 99
#define CannonFireTag   102

class Cannon : public cocos2d::CCObject{
public:
    /*静态创建炮台函数
     cannonType 要创建的炮台类型，根据cannon.plist文件，确定可支持的类型可选值：1、2、3、4、5、6、7
     pGameLayer 游戏世界的指针
     pBatchNode 在游戏世界中用来装载炮台的容器
     */
    static Cannon* createWithCannonType(GameLayer* pGameLayer,cocos2d::CCSpriteBatchNode* pBatchNode,CCSprite* pCannonSprite);
    /*调度炮台转向到用户触摸屏幕的方向
     然后发炮
     pt 用户触摸屏幕的点
     */
    bool rotationAndFire(cocos2d::CCPoint pt);
    //发射子弹
    bool fire();
    //获取当前大炮的类型id
    int getConnonType();
    
    virtual ~Cannon();
    
    //加减炮的单发分数，返回值为是否需要重新创建新等级的大炮
    bool incCannonScore();
    bool decCannonScore();
   
    
    void startSpecCannon(CannonType cannonType);
    void endSpecCannon();
    
    CannonType m_nCannonType;//被指定的炮台类型
    
    CCPoint getCannonHolePos();
    CCPoint getLaserPos();
    
public:
    int cannon_score;
    int cannon_score_max;
    
    bool isHideBullet;
    
    bool isSepcailCannon;
    
    
    int SpecLeftTime;
    
    unsigned long m_lLastAddAp;
private:
    
    bool isCooldown;
    
    Cannon();//私有化，防止被错误的实例化
    Cannon(const Cannon &obj);//私有化，防止被浅复制
    /*构造函数，被initWithCannonType调用实例化*/
    Cannon(GameLayer *gameLayer,CCSpriteBatchNode *pBatchNode,CCSprite* pCannonSprite);
    
    CCPoint m_pos;
    
    CCSpriteBatchNode * m_pBatchNode;
    
    CannonType normal_cannonType;
    char * cannonName;
    
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
    
    //GameLayer *m_pGameLayer;//游戏世界，在发射子弹时需要
    float m_fRotation;//计算后保存炮台需要转动的方向 
    cocos2d::CCSprite *m_pSprite;//炮台精灵实例
    cocos2d::CCPoint m_pDirection; //用户触摸屏幕的点，存储炮台转向，子弹发射的目的方向

    /*被公共方法 createWithCannonType 调用，真正处理炮台实例化 
     pBatchNode 在游戏世界中用来装载炮台的容器
     */
    bool initWithCannonType(CannonType pCannonType);
    
    void removeSwEffect();
    
    void cooldown();
    void doFire();
};

#endif

/*
 [HC1]:以指针代替嵌入对象或引用 http://blog.sina.com.cn/s/blog_40965d3a0101eajn.html
 */
