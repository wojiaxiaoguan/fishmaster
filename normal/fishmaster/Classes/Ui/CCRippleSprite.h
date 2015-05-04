//
//  pgeRippleSprite.h
//  rippleDemo
//
//
//  
//
// --------------------------------------------------------------------------
// import headers

#include "cocos2d.h"
#include "common.h"
#include <vector>

using namespace std;

// --------------------------------------------------------------------------
// defines

#define RIPPLE_DEFAULT_QUAD_COUNT_X             60
#define RIPPLE_DEFAULT_QUAD_COUNT_Y             40

#define RIPPLE_BASE_GAIN                        0.1f        // an internal constant

#define RIPPLE_CHILD_MODIFIER                   4.0f        // strength modifier

#define RIPPLE_BOUNCE 1

// --------------------------------------------------------------------------
// typedefs

typedef enum {
    RIPPLE_TYPE_RUBBER,                                     // a soft rubber sheet
    RIPPLE_TYPE_GEL,                                        // high viscosity fluid
    RIPPLE_TYPE_WATER,                                      // low viscosity fluid
} RIPPLE_TYPE;

typedef enum {
    RIPPLE_CHILD_LEFT,
    RIPPLE_CHILD_TOP,
    RIPPLE_CHILD_RIGHT,
    RIPPLE_CHILD_BOTTOM,
    RIPPLE_CHILD_COUNT
} RIPPLE_CHILD;

USING_NS_CC;

typedef struct _rippleData {
    bool                    parent;                         // ripple is a parent
    bool                    childCreated[ 4 ];              // child created ( in the 4 direction )
    RIPPLE_TYPE             rippleType;                     // type of ripple ( se update: )
    CCPoint                 center;                         // ripple center ( but you just knew that, didn't you? )
    CCPoint                 centerCoordinate;               // ripple center in texture coordinates
    float                   radius;                         // radius at which ripple has faded 100%
    float                   strength;                       // ripple strength
    float                   runtime;                        // current run time
    float                   currentRadius;                  // current radius
    float                   rippleCycle;                    // ripple cycle timing
    float                   lifespan;                       // total life span
} rippleData;


#define DEFAULT_RIPPLES_COUNT (5)

typedef struct __autoRippleData {
    int radius;
    float strength;
    float cycle;
    float lifeSpan;
    
    CCPoint pos;
    
   void show() { printf("Radius:%d Strength:%f Cycle:%f LifeSpan:%f Pos:(%f,%f)",
                        radius, strength, cycle, lifeSpan, pos.x, pos.y);
   }
    
}AutoRippleData;

// --------------------------------------------------------------------------
// interface

class pgeRippleSprite : public CCSprite, public CCTargetedTouchDelegate {
public:
   //static methods:
    static pgeRippleSprite* create(const char * filename);
    static pgeRippleSprite* create(CCRenderTexture* rtt, float scale);
    
    pgeRippleSprite();
    ~pgeRippleSprite();
    bool initWithFile(const char* filename);
    bool initWithRendertexture(CCRenderTexture* rtt, float scale);
    
    //自动涟漪
    void autoRipplesParents();
    void autoRipplesChildren();
    
    void tesselate();
    //void addRipple(CCPoint pos, RIPPLE_TYPE type, float strength);
    void addRipple(RIPPLE_TYPE type, AutoRippleData *ripple);
    void addRippleChild(rippleData* parent, RIPPLE_CHILD type);
    void update(float dt);
    CCTexture2D* spriteTexture();
    
    virtual void draw();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    bool isPointInsideSprite(CCPoint pos);
    bool isTouchInsideSprite(CCTouch* pTouch);
    
    //生成自动涟漪
    void createAutoRipples();
    
    //生成值
    int genValue( int min, int max);
    float genValue( float min, float max);
    
    
       
    CCTexture2D*            m_texture;
    int                     m_quadCountX;                   // quad count in x and y direction
    int                     m_quadCountY;
    int                     m_VerticesPrStrip;              // number of vertices in a strip
    int                     m_bufferSize;                   // vertice buffer size
    CCPoint*                m_vertice;                      // vertices
    CCPoint*                m_textureCoordinate;            // texture coordinates ( original )
    CCPoint*                m_rippleCoordinate;             // texture coordinates ( ripple corrected )
    bool*                   m_edgeVertice;                  // vertice is a border vertice
    vector<rippleData*>     m_rippleList;                   // list of running ripples
    
    
    CCPoint screenSize;
    float scaleRTT;
    float runTime;
    
    int m_uTextureLocation;
    
    AutoRippleData _arrAutoRipples[DEFAULT_RIPPLES_COUNT];
    AutoRippleData *_curAutoRipple;
    AutoRippleData _defRipple;
};

