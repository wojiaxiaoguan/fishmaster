

#ifndef FishingJoy_Bullet_h
#define FishingJoy_Bullet_h

#include "headerLibrary.h"
#include "Cannon.h"

class GameLayer;

#define GameDefaultBulletSpeed  450
#define ApBulletMaxReflect 3

class FatherBullet : public cocos2d::CCSprite
{
public:
    int bullet_score;      //子弹分数    andy
    int totalGetScore;     //总共获得的分数   andy
    int hit_rate;          //打击速度      andy
    void showTotalScoreAnimate();    //显示总分数动画   andy
    int hit_Percentage;      //子弹命中率
};

enum BulletStatus{
    Bullet_Fly = 0,
    Bullet_Hit,
    Bullet_Net,
    Bullet_End
};

class Bullet : public FatherBullet
{
    
public:
    static Bullet *createWithBulletType(CannonType bulletType, GameLayer *gameLayer, cocos2d::CCSpriteBatchNode *pBatchNodeBullet,int pScore, CCPoint pPos, bool pIsAp = false);
    
    Bullet();
    
    //超指定的方向发射子弹
    void shootTo(cocos2d::CCPoint targetDirection);
    void shootLaser(CCPoint targetDirection);
    
    //当击中鱼儿时，播放撒网动画
    void showNet();
    
    void rotate(float delta);
    
    bool isAP() { return m_bAP; };
    
    int m_speed; //bullet speed, pixels per second
    
    BulletStatus m_status;
    
    bool isHide;
    int m_reflectTimes;
    
    CC_SYNTHESIZE(int, m_nBulletType, BulletType);
    
private:
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
//    CC_SYNTHESIZE(Cannon *, m_pCannon, Cannon);
//    CC_SYNTHESIZE(CCSpriteBatchNode *, m_batchNodeBullet, BatchNodeBullet);
    
//    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSpriteBullet, SpriteBullet);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSpriteNet, SpriteNet);
    //创建子弹实例
    bool initWithBulletType(CannonType bulletType, GameLayer *gameLayer, cocos2d::CCSpriteBatchNode *pBatchNodeBullet,int pScore, CCPoint pPos, bool pIsAp = false);
    //撒网动画播放完成后抓鱼
    void netCatchFish();
    
    float getBulletMoveTime(CCPoint startPos, CCPoint endPos);
    
    //射击的子弹在超出屏幕后反弹
    void reflect();
    
    int frameCnt;
    char* bulletFile;
    char* netFile;
    
    int netFrameCnt;
    
    void removeSelf();
    
    CCPoint ptLastStart;
    
    cocos2d::CCAction*  m_bulletAction;
    cocos2d::CCAnimation* m_bulletAnimation;
    
    float rotateTime;
    bool m_bAP;
};

#endif
