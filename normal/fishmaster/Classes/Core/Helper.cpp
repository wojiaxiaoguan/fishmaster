//
//  Helper.cpp
//  fish
//
//  
//
//

#include "Helper.h"
#include "Sound.h"
USING_NS_CC;

//Implementation NumSprite

NumSprite* NumSprite::create(int num, NumberType pType)
{
    char str[256] = {0};
    char name[32];
    NumSprite* n = new NumSprite;
    n->initWithSpriteFrameName("nup_X.png");
    n->autorelease();
    if (pType == GameNumberGameLayerTime)
    {
        sprintf(str, "%02d", num);
    }
    else
    {
        sprintf(str,"%d",num);
    }
    
    float width = 0;
    float height = 0;
    
    for (int i=0; i < sizeof(str); i++) {
        if(str[i] == 0)
            break;
        if (pType == GameNumberGameLayerGold) {
            sprintf(name,"nup_%c.png",str[i]);
        } else if (pType == GameNumberStoreLayerGold) {
            sprintf(name,"r%c.png",str[i]);
        } else if (pType == GameNumberStoreSubLayerGold) {
            sprintf(name,"bs%c.png",str[i]);
        } else if (pType == GameNumberGameLayerTime) {
            sprintf(name,"bs%c.png",str[i]);
        } else if (pType == GameNumberSotreUp) {
            sprintf(name,"nup_%c.png",str[i]);
        } else if (pType == GameNumberYingxin) {
            sprintf(name,"r%c.png",str[i]);
        }
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
        CCSprite *p = CCSprite::create();
        p->initWithSpriteFrame(frame);
        n->addChild(p);
        p->setAnchorPoint(CCPointZero);
        p->setPosition(ccp(p->getContentSize().width*i,0));
        
        height = p->getContentSize().height;
        width = p->getContentSize().width*(i+1);
        
        
    }
    n->setContentSize(CCSize(width,height));
    return n;
}


void NumSprite::setOpacity(GLubyte opacity)
{
    CCObject *pcd = NULL;
    CCArray *n = getChildren();
    CCARRAY_FOREACH(n,pcd) {
        ((CCSprite*)pcd)->setOpacity(opacity);
    }
}



GoldSprite* GoldSprite::create(int num)
{
    //const char *pfile = "qianbi.png";
    GoldSprite* n = new GoldSprite;
    n->initWithSpriteFrameName("nup_X.png");
    n->autorelease();
    n->m_num = num;
    n->updateGold(CCTime());
    /*
    for (int i=0; i < num; i++) {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pfile);
        CCSprite *p = CCSprite::create();
        p->initWithSpriteFrame(frame);
        n->addChild(p);
        p->setPosition(ccp(0,p->getContentSize().height*i));
    }
    */

    return n;
}


void GoldSprite::setOpacity(GLubyte opacity)
{
    CCObject *pcd = NULL;
    CCArray *n = getChildren();
    CCARRAY_FOREACH(n,pcd) {
        ((CCSprite*)pcd)->setOpacity(opacity);
    }
}


void GoldSprite::goAnimate()
{
    this->schedule(schedule_selector(GoldSprite::updateGold), 0.1, m_num, 0);
}

void GoldSprite::updateGold(cocos2d::CCTime dt)
{
    int num = 0;
    CCArray *pa = getChildren();
    if(pa != NULL)
        num = pa->count();
    int height1,height2;
    
    CCArray *aniframe = CCArray::createWithCapacity(5);
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("qianb_0.png");
    CCSprite *p = CCSprite::create();
    p->initWithSpriteFrame(frame);
    p->setAnchorPoint(ccp(0,0));
    
    height1 = frame->getOriginalSize().height;
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("qianb_1.png");
    aniframe->addObject(frame);
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("qianb_3.png");
    aniframe->addObject(frame);
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("qianb_4.png");
    aniframe->addObject(frame);
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("qianb.png");
    aniframe->addObject(frame);
    
    height2 = frame->getOriginalSize().height;
    
    addChild(p);

    p->setPosition(ccp(0,height2 * num));

    CCAnimation * animation = CCAnimation::createWithSpriteFrames(aniframe,0.02);//通过集合创建动画
    p->runAction(CCAnimate::create(animation));
}

int GoldSprite::getWidth()
{
    CCArray  * p = getChildren();
    if(p == NULL)
        return 0;
    return ((CCSprite*) (p->objectAtIndex(0)))->getContentSize().width;
}

void GoldSprite::stepOver()
{
    if(getPosition().x <=0) {
        removeFromParent();
    } else {
        CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(GoldSprite::stepOver));
        runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(0,0)),CCMoveBy::create(0.2, ccp(-getWidth(),0)),callFunc,NULL));
    }
}



GoldControl* GoldControl::create()
{
    GoldControl *n = new GoldControl;
    n->initWithSpriteFrameName("nup_X.png");
    n->autorelease();
    n->m_golds = new CCArray;

    return n;
}

GoldControl::GoldControl()
{
}

void GoldControl::updateGolds(cocos2d::CCTime dt)
{

    int cur_num = getChildrenCount();
    //CCPoint curr = getPosition();
    
    if (cur_num >= 5 || (cur_num > 0 && m_golds->count() == 0)) {
        unschedule(schedule_selector(GoldControl::updateGolds));
        schedule(schedule_selector(GoldControl::moveGolds), 0.4	);
        return;
    }
    
    
    if (m_golds->count() > 0) {
        GoldSprite* pg = (GoldSprite*)m_golds->objectAtIndex(0);
        addChild(pg);
        pg->setPosition(ccp((cur_num++)*pg->getWidth() + pg->getWidth(), 6));
        pg->goAnimate();
        m_golds->removeObjectAtIndex(0);
    }
    
}


void GoldControl::moveGolds(cocos2d::CCTime dt)
{
    CCArray* p = getChildren();
    if(p!=NULL && p->count() !=0){
        ((GoldSprite*)p->objectAtIndex(0))->removeFromParent();
    }
    
    p = getChildren();
    if (p == NULL || p->count() == 0) {
        m_golds->removeAllObjects();
        unschedule(schedule_selector(GoldControl::moveGolds));
        setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/7,CCDirector::sharedDirector()->getVisibleSize().height/17));
        return;
    }
    
    if(p!=NULL && p->count() !=0){
        int wid = ((GoldSprite*)p->objectAtIndex(0))->getWidth();
        //CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(GoldControl::animateDone));
        //runAction(CCSequence::create(CCMoveBy::create(0.3,ccp(-wid,0)),callFunc,NULL));
        runAction(CCMoveBy::create(0.3,ccp(-wid,0)));
    }
}

void GoldControl::AddGold(int num)
{
    GoldSprite *n = GoldSprite::create(num);
    
    if (m_golds->count() == 0) {
        schedule(schedule_selector(GoldControl::updateGolds), 0.7,kCCRepeatForever,0.1);
    }
    m_golds->addObject(n);

}


CenterRoll* CenterRoll::create(int score)
{
    CenterRoll * n = new CenterRoll();
    n->init();
    n->generateFrameAnimation();
    n->autorelease();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    n->setAnchorPoint(CCPoint(0.5, 0.5));
    n->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    CCSize contentSize = n->getContentSize();
    n->m_pnum = NumSprite::create(score);
    CCSize spn = n->m_pnum->getContentSize();

    DF_LOG("getContentSize() " ,spn.width);
     n->addChild(n->m_pnum);
    n->m_pnum->setAnchorPoint(CCPoint(0.5, 0.5));
    n->m_pnum->setPosition(ccp(contentSize.width / 2, contentSize.height / 2 ));
   
    
    return n;
}


void CenterRoll::generateFrameAnimation()
{
    char str[32];
    
    
    bzero(str,sizeof(str));
//    CCArray *aniframe = CCArray::createWithCapacity(10);
    sprintf(str, "centerRoll_%d.png", 1);
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
    initWithSpriteFrame(frame);
    setContentSize(frame->getOriginalSize());
    
//    for(int i=1;i <=1;i++){
//        sprintf(str,"centerRoll_%d.png",i);  //通过下标动态创建精灵
//        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//        
//        if(i==1){//默认添加第一帧图到界面上
//            initWithSpriteFrame(frame);
//            setContentSize(frame->getOriginalSize());
//            //setPosition(ccp(0,0));
//        }
//        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
//        
//        m_frameAnimation = CCAnimation::createWithSpriteFrames(aniframe,1.0);//通过集合创建动画
//        m_frameAnimation->retain();
//    }
}

void CenterRoll::goAnimation()
{
    this->setScale(0.1);
    CCScaleTo* pScaleTo = CCScaleTo::create(0.5, 1.0);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(NumSprite::removeFromParent));
    runAction(CCSequence::create(pScaleTo, CCDelayTime::create(1),callFunc,NULL));
//    CCRepeat *p = CCRepeat::create(CCSequence::create(CCMoveBy::create(0.05,ccp(0,20)),
//                                       CCMoveBy::create(0.05,ccp(0,-20)),
//                                       CCMoveBy::create(0.05,ccp(0,-20)),
//                                       CCMoveBy::create(0.05,ccp(0,20)),
//                                       CCMoveBy::create(0.05,ccp(0,20)),
//                                       CCMoveBy::create(0.05,ccp(0,-20)),
//                                       CCMoveBy::create(0.05,ccp(0,-20)),
//                                       CCMoveBy::create(0.05,ccp(0,20)),
//                                       CCMoveBy::create(0.05,ccp(0,20)),
//                                       CCMoveBy::create(0.05,ccp(0,-20)),
//                                       CCMoveBy::create(0.05,ccp(0,-20)),
//                                       CCMoveBy::create(0.05,ccp(0,20))
//                                       ,NULL),1);
//    m_pnum->runAction(p);
    Sound::Instance()->playEffect("addGold.mp3");
}




double multiply(CCPoint sp,CCPoint ep,CCPoint op)
{
    return((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y));
}

bool intersect(CCPoint us,CCPoint ue,CCPoint vs,CCPoint ve)
{
    return( (MAX(us.x,ue.x)>=MIN(vs.x,ve.x))&& //排斥实验
           (MAX(vs.x,ve.x)>=MIN(us.x,ue.x))&&
           (MAX(us.y,ue.y)>=MIN(vs.y,ve.y))&&
           (MAX(vs.y,ve.y)>=MIN(us.y,ue.y))&&
           (multiply(vs,ue,us)*multiply(ue,ve,us)>=0)&& //跨立实验
           (multiply(us,ve,vs)*multiply(ve,ue,vs)>=0));
}

bool isRectInterset(CCPoint a1,CCPoint b1,CCPoint c1,CCPoint d1,CCPoint a2,CCPoint b2,CCPoint c2,CCPoint d2)
{
    return intersect(a1, b1, a2, b2) ||
    intersect(a1, b1, b2, c2) ||
    intersect(a1, b1, c2, d2) ||
    intersect(a1, b1, d2, a2) ||
    
    intersect(b1, c1, a2, b2) ||
    intersect(b1, c1, b2, c2) ||
    intersect(b1, c1, c2, d2) ||
    intersect(b1, c1, d2, a2) ||
    
    intersect(c1, d1, a2, b2) ||
    intersect(c1, d1, b2, c2) ||
    intersect(c1, d1, c2, d2) ||
    intersect(c1, d1, d2, a2) ||
    
    intersect(d1, a1, a2, b2) ||
    intersect(d1, a1, b2, c2) ||
    intersect(d1, a1, c2, d2) ||
    intersect(d1, a1, d2, a2);
    
}

bool isLineInterset(int px1, int py1, int px2, int py2,int qx1, int qy1, int qx2, int qy2)
{
    return ( ((px2-px1)*(qy1-py1) - (qx1-px1)*(px2-px1)) * ((qx2-px1)*(py2-py1) - (px2-px1)*(qy2-py1)) ) >=0;
}

bool isCCSpriteInterset(CCSprite* p1, CCSprite* p2)
{
    CCSize s1 = p1->getContentSize();
    
    //special for laser
    CCPoint bottomLeft1 = CCPointApplyAffineTransform(ccp(60, 0), p1->nodeToParentTransform());
    CCPoint bottomRight1 = CCPointApplyAffineTransform(ccp(90, 0), p1->nodeToParentTransform());
    CCPoint topLeft1 = CCPointApplyAffineTransform(ccp(90, s1.height), p1->nodeToParentTransform());
    CCPoint topRight1 = CCPointApplyAffineTransform(ccp(60, s1.height), p1->nodeToParentTransform());

//    CCPoint bottomLeft1 = CCPointApplyAffineTransform(ccp(0, 0), p1->nodeToParentTransform());
//    CCPoint bottomRight1 = CCPointApplyAffineTransform(ccp(s1.width, 0), p1->nodeToParentTransform());
//    CCPoint topLeft1 = CCPointApplyAffineTransform(ccp(s1.width, s1.height), p1->nodeToParentTransform());
//    CCPoint topRight1 = CCPointApplyAffineTransform(ccp(0, s1.height), p1->nodeToParentTransform());
    
    CCSize s2 = p2->getContentSize();
    
    CCPoint bottomLeft2 = CCPointApplyAffineTransform(ccp(0, 0), p2->nodeToParentTransform());
    CCPoint bottomRight2 = CCPointApplyAffineTransform(ccp(s2.width, 0), p2->nodeToParentTransform());
    CCPoint topLeft2 = CCPointApplyAffineTransform(ccp(s2.width, s2.height), p2->nodeToParentTransform());
    CCPoint topRight2 = CCPointApplyAffineTransform(ccp(0, s2.height), p2->nodeToParentTransform());
    
    return isRectInterset(bottomLeft1, bottomRight1, topLeft1, topRight1, bottomLeft2, bottomRight2, topRight2, topLeft2);
}

