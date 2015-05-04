//
//  RippleGrid3D.h
//  RippleDemo
//
//  
//
//

#ifndef __RippleDemo__RippleGrid3D__
#define __RippleDemo__RippleGrid3D__
#include "headerLibrary.h"
USING_NS_CC;

#define vertext_len 3

class RippleGrid3D:public CCGrid3D
{
protected:
    ccVertex3F* m_pBufNext;
    ccVertex3F* m_pBufLast;
    float* m_pBuf;
    
    int m_width;
    int m_height;
public:
    RippleGrid3D();
    ~RippleGrid3D();
    bool initWithSize(const CCSize& gridSize);
    
    virtual void update(float dt);
    static RippleGrid3D* create(const CCSize& gridSize);
    
    void dropStone(int x, int y, int stoneSize, int stoneWeight);
};

#endif /* defined(__RippleDemo__RippleGrid3D__) */
