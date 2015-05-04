//
//  FishMatrix.h
//  fish
//
//  
//
//

#ifndef __fish__FishMatrix__
#define __fish__FishMatrix__

#include <iostream>


#include "cocos2d.h"
#include "common.h"
#include "Fish.h"

class GameLayer;


class FishMatrix : public cocos2d::CCSprite
{
public:
    enum FishMatrix_Type {
        FISH_MATRIX_CIRCLE,     //圆形
        FISH_MATRIX_SCATTER,    //散开
        FISH_MATRIX_RANK,       //行列
        FISH_MATRIX_ELLIPSE,    //椭圆
        FISH_MATRIX_HELIX,      //螺旋
        FISH_MATRIX_MAX         //最大
    };
    static FishMatrix *create(GameLayer *parent,FishMatrix_Type type = FISH_MATRIX_MAX);
    virtual void goFishMatrix(){}
    virtual void removeFromParent();
    cocos2d::CCArray * m_fishes;
    GameLayer * m_parent;
};


class FishMatrixCircle : public FishMatrix
{
public:
    static FishMatrixCircle* create(GameLayer *parent);
    virtual void goFishMatrix();
    void stop();
};


class FishMatrixScatter : public FishMatrix
{
public:
    static FishMatrixScatter* create(GameLayer *parent);
    virtual void goFishMatrix();
    void stop();
};



class FishMatrixRank : public FishMatrix
{
public:
    static FishMatrixRank* create(GameLayer *parent);
    virtual void goFishMatrix();
    void stop();
};



class FishMatrixEllipse : public FishMatrix
{
public:
    static FishMatrixEllipse* create(GameLayer *parent);
    virtual void goFishMatrix();
    void stop();
};



class FishMatrixHelix : public FishMatrix
{
public:
    static FishMatrixHelix* create(GameLayer *parent);
    virtual void goFishMatrix();
    void stop();
};


#endif /* defined(__fish__FishMatrix__) */
