//
//  Fish.h
//  MyGame
//
//  
//
//

#ifndef __MyGame__Fish__
#define __MyGame__Fish__

#include "cocos2d.h"
#include "common.h"
#include "Bullet.h"
//#include "FishPath.h"
#include <iostream>

class GameLayer;
class CCFishBezierTo;



class Fish : public cocos2d::CCSprite
{
public:
    enum FishType{
        FISH_XIAOGUANGYU = 0,
        FISH_XIAOCAOYU,
        FISH_REDAIYU,
        FISH_DAYANJINYU,
        FISH_SHUIMU,
        FISH_SHANWEIYU,
        FISH_REDAIZIYU,
        FISH_XIAOCHOUYU,
        FISH_HETUN,
        FISH_WUZEI,
        FISH_SHITOUYU,
        FISH_SHENXIANYU,
        FISH_WUGUI,
        FISH_DENGLONGYU,
        FISH_SHIBANYU,
        FISH_HUDIEYU,
        FISH_LINGDANGYU,
        FISH_JIANYU,
        FISH_MOGUIYU,
        FISH_FEIYU,
        FISH_LONGXIA,
        FISH_HAITUN,     //美人鱼
        FISH_DAYINSHA,
        FISH_LANJING,     //龙王
//        FISH_HUANGJINGJINGYU,
//        FISH_HUANGJINGYU,
//        FISH_BYMOGUIYU,
//        FISH_BYWUGUI,
        FISH_ZHENZHUBEI,
//        FISH_LANSHA,
        FISH_XIAOFEIYU,
        FISH_ALILAN,
//        FISH_HAIMA,
        FISH_ZHADANFISH,
        FISH_NORMAL_TYPEMAX,
        /*--new--*/
        FISH_XIAOHUANGCI,
        FISH_LANGUANGYU,
        FISH_QICAIYU,
        FISH_YINGWULUO,
        FISH_TIAOWENYU,
        FISH_GANGKUIYU,
        FISH_HAIGUAI,
        FISH_HGZHADAN,
        FISH_All_TYPEMAX
    };
    
    enum SpecialAttr{
        SPEC_HLYQ = 1,
        SPEC_HYLL,
        SPEC_TLYQ,
        SPEC_DASIXI,
        SPEC_ZDYQ,
        SPEC_YWYQ,
        SPEC_NONE
    };
    
    
    //static Fish* create(GameLayer *parent);
    static Fish* createSpecificFish(GameLayer *parent,FishType type,bool withPath=true);
    static Fish* createSpecFish(GameLayer *parent);
    static void lockFish(FishType type,bool lck);
    static void lockFishRing(SpecialAttr type, bool lck);
    static FishType getRefreshFishType();
    static int getRefreshFishNum(FishType type);
    static bool isFishLocked(FishType type);
    Fish(FishType type);
    virtual ~Fish(void);
    
    void goFish();
    int attackFish(FatherBullet *pBullet, float rate = 0);
    FishType getFishType(){return m_fishType;}
    virtual void setOpacity(GLubyte opacity);
    virtual void setColor(const ccColor3B& color3);
    void fishDeadCBK();
    void fishStopCBK();
    void unLockAndRelease();
    void updateShine(cocos2d::CCTime dt);
    void setSpec(SpecialAttr spec);
    cocos2d::CCPoint m_lastPoint;
    cocos2d::ccColor3B m_originColor;
    cocos2d::CCArray * m_fishPath;
    FishType m_fishType;
    int m_speedTime;
    int m_genCornNum;
    int m_fishCD;
    SpecialAttr m_spec;
    
protected:
    
    static const char * getFishFilePrefix(FishType type);
    void generateFrameAnimation();
    CCFishBezierTo* generateBezierPath(cocos2d::CCPoint start, cocos2d::CCPoint c1, cocos2d::CCPoint c2, cocos2d::CCPoint end,float t);
    virtual void generateFishPath();
    void generateCoin(int num = 1);
    void generateNum(int num);
    void playDeadSound();
    bool willDead(float rate);
    int dealWithTLYQ();
    int dealWithHLYQ();
    int dealWithZDYQ();
    int dealWithYWYQ();
    int dealWithZhadanFish();
    int killFish(FatherBullet *pBullet);
    
   
    
    
    
    float m_activeFrameDelay;
    float m_deadFrameDelay;
    cocos2d::CCAction*  m_fishAction;
    cocos2d::CCAnimation* m_activeFrameAnimation;
    cocos2d::CCAnimation* m_deadFrameAnimation;
    cocos2d::CCSprite * m_specSprite;
    
    int m_activeFrameCount;
    int m_deadFrameCount;
    
    float m_scoreRate;
    int m_attackRate;
    FatherBullet *m_attackBullet;
    GameLayer * m_parent;
    
    static int _freshRateArray[FISH_All_TYPEMAX];
    static bool _fishLockArray[FISH_All_TYPEMAX];
    static bool _fishRingLockArray[Fish::SPEC_NONE];
};

class FishInterface
{
public:
    virtual void removeFish(Fish *pf) = 0;
};

class SeaMonsterInterface
{
public:
    virtual void onGetDamage() = 0;
};

#endif /* defined(__MyGame__Fish__) */
