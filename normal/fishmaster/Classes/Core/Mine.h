//
//  Mine.h
//  fish
//
//  
//
//

#ifndef __fish__Mine__
#define __fish__Mine__

#include <iostream>
#include "headerLibrary.h"
#include "Bullet.h"

enum MineStatus{
    Mine_Start = 0,
    Mine_Ready,
    Mine_Bomb,
    Mine_End
};

class Mine  : public FatherBullet
{
public:
    
    static Mine* create(CCSpriteBatchNode* pBatchNode);
    
    Mine();
    ~Mine();
    
    void start(CCPoint pPoint,CCLayer* pGameLayer);
    void startKnife(CCPoint pPoint,CCLayer* pGameLayer);
    void startEle(CCLayer* pGameLayer);
    void addEle();
    void remove();
    void startBomb();
    void bomb();
    void mineReady();
    
    CCSprite* m_sprite;
    
    MineStatus m_status;
    
   void addPower(int pAdd);
    
    int m_power_max;
    
    void updatePowerMax();
    
private:
    
    CCSpriteBatchNode*  m_batchNode;
    GameLayer*          m_gameLayer;
};



#endif /* defined(__fish__Mine__) */
