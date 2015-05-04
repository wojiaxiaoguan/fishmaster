//  CCRippleSprite.cpp
//  RippleDemo-x
//
//  
//
//

#include "CCRippleSprite.h"
#include "../Foundation/AppDelegate.h"
#include <string>

using namespace std;

pgeRippleSprite* pgeRippleSprite::create(const char * filename)
{
    pgeRippleSprite *pSprite = new pgeRippleSprite();
    if (pSprite && pSprite->initWithFile(filename)) {
        pSprite->autorelease();
        return pSprite;
    }
    else
    {
        delete pSprite;
        pSprite = NULL;
        return NULL;
    }
}


pgeRippleSprite::pgeRippleSprite()
:m_texture(NULL),
m_quadCountX(0),
m_quadCountY(0),
m_VerticesPrStrip(0),
m_bufferSize(0),
m_vertice(NULL),
m_textureCoordinate(NULL),
m_rippleCoordinate(NULL),
m_edgeVertice(NULL),
scaleRTT(0),
screenSize(CCPointZero),
runTime(0)
{
 
    srand(time(NULL));
}
pgeRippleSprite::~pgeRippleSprite()
{
    rippleData* runningRipple;
    
    free(m_vertice);
    free(m_textureCoordinate);
    free(m_rippleCoordinate);
    free(m_edgeVertice);
    
    for (int count = 0; count < m_rippleList.size(); count++) {
        runningRipple = m_rippleList.at(count);
        free(runningRipple);
    }
    
    m_texture->release();
    
}


bool pgeRippleSprite::initWithFile(const char* filename)
{
    bool bRet = true;
    
    do {
        
        if (!CCSprite::init()) {
            bRet = false;
            break;
        }
        
        scaleRTT = 1.0f;
        
        createAutoRipples();
        
        
        //load texture
        m_texture = CCTextureCache::sharedTextureCache()->addImage(filename);
        m_texture->retain();
        
        //reset internal data
        m_vertice = NULL;
        m_textureCoordinate = NULL;
        //builds the vertice and texture-coordinate array
        m_quadCountX = RIPPLE_DEFAULT_QUAD_COUNT_X;
        m_quadCountY = RIPPLE_DEFAULT_QUAD_COUNT_Y;
        this->tesselate();
        
       screenSize = ccp(m_texture->getContentSize().width / scaleRTT,
                        m_texture->getContentSize().height / scaleRTT);
       
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));

        
    } while (0);
    
    
    this->schedule(schedule_selector(pgeRippleSprite::autoRipplesParents),3.0f);
    return bRet;

}


void pgeRippleSprite::tesselate()
{
    int vertexPos = 0;
    CCPoint normalized;
    
    // clear buffers ( yeah, clearing nil buffers first time around )
    free( m_vertice );
    free( m_textureCoordinate );
    free( m_rippleCoordinate );
    free( m_edgeVertice );
    
    // calculate vertices pr strip
    m_VerticesPrStrip = 2 * ( m_quadCountX + 1 );
    
    // calculate buffer size
    m_bufferSize = m_VerticesPrStrip * m_quadCountY;
    
    // allocate buffers
    m_vertice = (CCPoint*)malloc( m_bufferSize * sizeof( CCPoint ) );
    m_textureCoordinate = (CCPoint*)malloc( m_bufferSize * sizeof( CCPoint ) );
    m_rippleCoordinate = (CCPoint*)malloc( m_bufferSize * sizeof( CCPoint ) );
    m_edgeVertice = (bool*)malloc( m_bufferSize * sizeof( bool ) );
    
    // reset vertice pointer
    vertexPos = 0;
    
    // create all vertices and default texture coordinates
    // scan though y quads, and create an x-oriented triangle strip for each
    for ( int y = 0; y < m_quadCountY; y ++ ) {
        
        // x counts to quadcount + 1, because number of vertices is number of quads + 1
        for ( int x = 0; x < ( m_quadCountX + 1 ); x ++ ) {
            
            // for each x vertex, an upper and lower y position is calculated, to create the triangle strip
            // upper + lower + upper + lower
            for ( int yy = 0; yy < 2; yy ++ ) {
                
                // first simply calculate a normalized position into rectangle
                normalized.x = ( float )x / ( float )m_quadCountX;
                normalized.y = ( float )( y + yy ) / ( float )m_quadCountY;
                
                // calculate vertex by multiplying rectangle ( texture ) size
                m_vertice[vertexPos] = ccp(normalized.x * m_texture->getContentSize().width / scaleRTT, normalized.y *
                                           m_texture->getContentSize().height / scaleRTT );
                
                // adjust texture coordinates according to texture size
                // as a texture is always in the power of 2, maxS and maxT are the fragment of the size actually used
                // invert y on texture coordinates
                m_textureCoordinate[vertexPos] = ccp(normalized.x * m_texture->getMaxS(), m_texture->getMaxT() - normalized.y *
                                                     m_texture->getMaxT());
                
                // check if vertice is an edge vertice, because edge vertices are never modified to keep outline consistent
                m_edgeVertice[ vertexPos ] = (
                                              ( x == 0 ) ||
                                              ( x == m_quadCountX ) ||
                                              ( ( y == 0 ) && ( yy == 0 ) ) ||
                                              ( ( y == ( m_quadCountY - 1 ) ) && ( yy > 0 ) ) );
                
                // next buffer pos
                vertexPos ++;
                
            }
        }
    }
 
}
//void pgeRippleSprite::addRipple(CCPoint pos, RIPPLE_TYPE type, int radius, float strength, float cycle, float lifeSpan)

void pgeRippleSprite::addRipple(RIPPLE_TYPE type, AutoRippleData *ripple)
{
    if (ripple == NULL) {
        return;
    }
    
    rippleData* newRipple;
    
    // allocate new ripple
    newRipple = (rippleData*)malloc( sizeof( rippleData ) );
    
    // initialize ripple
    newRipple->parent = true;
    
    for ( int count = 0; count < 4; count ++ ) {
        newRipple->childCreated[ count ] = false;
    }
    
    newRipple->rippleType = type;
    newRipple->center = ripple->pos;
    newRipple->centerCoordinate = ccp(ripple->pos.x / m_texture->getContentSize().width * m_texture->getMaxS() / scaleRTT ,
                                      m_texture->getMaxT() - (ripple->pos.y / m_texture->getContentSize().height * m_texture->getMaxT()/scaleRTT));
    newRipple->radius = ripple->radius;
    newRipple->strength = ripple->strength;
    newRipple->runtime = 0;
    newRipple->currentRadius = 0;
    newRipple->rippleCycle = ripple->cycle;
    newRipple->lifespan = ripple->lifeSpan;
    
    // add ripple to running list
    m_rippleList.push_back(newRipple);
    
    
}
void pgeRippleSprite::addRippleChild(rippleData* parent, RIPPLE_CHILD type)
{
    rippleData* newRipple;
    CCPoint pos;
    
    //CGSize screenSize = [CCDirector sharedDirector].winSize;
    
    // allocate new ripple
    newRipple = (rippleData*)malloc( sizeof( rippleData ) );
    
    // new ripple is pretty much a copy of its parent
    memcpy( newRipple, parent, sizeof( rippleData ) );
    
    // not a parent
    newRipple->parent = false;
    
    // mirror position
    switch ( type ) {
        case RIPPLE_CHILD_LEFT:
            pos = ccp( -parent->center.x, parent->center.y );
            break;
        case RIPPLE_CHILD_TOP:
            pos = ccp( parent->center.x, screenSize.y + ( screenSize.y - parent->center.y ) );
            break;
        case RIPPLE_CHILD_RIGHT:
            pos = ccp( screenSize.x + ( screenSize.x - parent->center.x ), parent->center.y );
            break;
        case RIPPLE_CHILD_BOTTOM:
        default:
            pos = ccp( parent->center.x, -parent->center.y );
            break;
    }
    
    newRipple->center = pos;
    newRipple->centerCoordinate = ccp(pos.x / m_texture->getContentSize().width * m_texture->getMaxS(),
                                      m_texture->getMaxT() - (pos.y / m_texture->getContentSize().height * m_texture->getMaxT()));
    newRipple->strength *= RIPPLE_CHILD_MODIFIER;
    
    // indicate child used
    parent->childCreated[ type ] = true;
    
    // add ripple to running list
    m_rippleList.push_back(newRipple);
}

void pgeRippleSprite::update(float dt)
{
    
    runTime += dt;

    rippleData* ripple;
    CCPoint pos;
    float distance, correction;
    //CGSize screenSize = [CCDirector sharedDirector].winSize;
    
    // test if any ripples at all
    if ( m_rippleList.size() == 0 ) return;
    
    // ripples are simulated by altering texture coordinates
    // on all updates, an entire new array is calculated from the base array
    // not maintainng an original set of texture coordinates, could result in accumulated errors
    memcpy( m_rippleCoordinate, m_textureCoordinate, m_bufferSize * sizeof( CCPoint ) );
    
    // scan through running ripples
    // the scan is backwards, so that ripples can be removed on the fly
    for ( int count = ( m_rippleList.size() - 1 ); count >= 0; count -- ) {
        
        // get ripple data
        ripple = m_rippleList[count];
        
        // scan through all texture coordinates
        for ( int count = 0; count < m_bufferSize; count ++ ) {
            
            // dont modify edge vertices
            if ( m_edgeVertice[ count ] == false ) {
                
                // calculate distance
                // you might think it would be faster to do a box check first
                // but it really isnt,
                // ccpDistance is like my sexlife - BAM! - and its all over
                distance = ccpDistance( ripple->center, m_vertice[ count ] );
                
                // only modify vertices within range
                if ( distance <= ripple->currentRadius ) {
                    
                    // load the texture coordinate into an easy to use var
                    pos = m_rippleCoordinate[ count ];
                    
                    // calculate a ripple
                    switch ( ripple->rippleType ) {
                            
                        case RIPPLE_TYPE_RUBBER:
                            // method A
                            // calculate a sinus, based only on time
                            // this will make the ripples look like poking a soft rubber sheet, since sinus position is fixed
                            correction = sinf( 2 * M_PI * ripple->runtime / ripple->rippleCycle );
                            break;
                            
                        case RIPPLE_TYPE_GEL:
                            // method B
                            // calculate a sinus, based both on time and distance
                            // this will look more like a high viscosity fluid, since sinus will travel with radius
                            correction = sinf( 2 * M_PI * ( ripple->currentRadius - distance ) / ripple->radius * ripple->lifespan / ripple->rippleCycle );
                            break;
                            
                        case RIPPLE_TYPE_WATER:
                        default:
                            // method c
                            // like method b, but faded for time and distance to center
                            // this will look more like a low viscosity fluid, like water
                            
                            correction = ( ripple->radius * ripple->rippleCycle / ripple->lifespan ) / ( ripple->currentRadius - distance );
                            if ( correction > 1.0f ) correction = 1.0f;
                            
                            // fade center of quicker
                            correction *= correction;
                            
                            correction *= sinf( 2 * M_PI * ( ripple->currentRadius - distance ) / ripple->radius * ripple->lifespan / ripple->rippleCycle );
                            break;
                            
                    }
                    
                    // fade with distance
                    correction *= 1 - ( distance / ripple->currentRadius );
                    
                    // fade with time
                    correction *= 1 - ( ripple->runtime / ripple->lifespan );
                    
                    // adjust for base gain and user strength
                    correction *= RIPPLE_BASE_GAIN;
                    correction *= ripple->strength;
                    
                    // finally modify the coordinate by interpolating
                    // because of interpolation, adjustment for distance is needed,
                    correction /= ccpDistance( ripple->centerCoordinate, pos );
                    pos = ccpAdd( pos, ccpMult( ccpSub( pos, ripple->centerCoordinate ), correction ) );
                    
                    // another approach for applying correction, would be to calculate slope from center to pos
                    // and then adjust based on this
                    
                    // clamp texture coordinates to avoid artifacts
                    pos = ccpClamp( pos, CCPointZero, ccp( m_texture->getMaxS(), m_texture->getMaxT() ) );
                    
                    // save modified coordinate
                    m_rippleCoordinate[ count ] = pos;
                    
                }
            }
        }
        
        // calculate radius
        ripple->currentRadius = ripple->radius * ripple->runtime / ripple->lifespan;
        
        // check if ripple should expire
        ripple->runtime += dt;
        if ( ripple->runtime >= ripple->lifespan ) {
            
            // free memory, and remove from list
            free( ripple );
            m_rippleList.erase(m_rippleList.begin() + count);
            
        } else {
            
#ifdef RIPPLE_BOUNCE
            // check for creation of child ripples
            if ( ripple->parent == true ) {
                
                // left ripple
                if ( ( ripple->childCreated[ RIPPLE_CHILD_LEFT ] == false ) && ( ripple->currentRadius > ripple->center.x ) ) {
                    this->addRippleChild(ripple, RIPPLE_CHILD_LEFT);
                }
                
                // top ripple
                if ( ( ripple->childCreated[ RIPPLE_CHILD_TOP ] == false ) && ( ripple->currentRadius > screenSize.y - ripple->center.y ) ) {
                    this->addRippleChild(ripple, RIPPLE_CHILD_TOP);
                }
                
                // right ripple
                if ( ( ripple->childCreated[ RIPPLE_CHILD_RIGHT ] == false ) && ( ripple->currentRadius > screenSize.x - ripple->center.x ) ) {
                    this->addRippleChild(ripple, RIPPLE_CHILD_RIGHT);
                }
                
                // bottom ripple
                if ( ( ripple->childCreated[ RIPPLE_CHILD_BOTTOM ] == false ) && ( ripple->currentRadius > ripple->center.y ) ) {
                    this->addRippleChild(ripple, RIPPLE_CHILD_BOTTOM);
                }
                
                
                
            }
#endif
            
        }
        
    }
    

}
CCTexture2D* pgeRippleSprite::spriteTexture()
{
    return m_texture;
}



void pgeRippleSprite::draw()
{
    
    if (!this->isVisible()) {
        return;
    }
    
    CC_NODE_DRAW_SETUP();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );
	
    ccGLBindTexture2D(m_texture->getName() );
    // vertex
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, (void*) m_vertice);
    
    // if no ripples running, use original coordinates ( Yay, dig that kewl old school C syntax )
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, ( m_rippleList.size() == 0 ) ? m_textureCoordinate : m_rippleCoordinate);
    //    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, (m_textureCoordinate));
    
    // draw as many triangle fans, as quads in y direction
    for ( int strip = 0; strip < m_quadCountY; strip++ ) {
        glDrawArrays( GL_TRIANGLE_STRIP, strip * m_VerticesPrStrip, m_VerticesPrStrip );
    }
 
}





bool pgeRippleSprite::isPointInsideSprite(cocos2d::CCPoint pos)
{
    float maxX = m_texture->getContentSize().width / scaleRTT;
    float maxY = m_texture->getContentSize().height / scaleRTT;
    
    
    if(pos.x < 0 || pos.y < 0 ||
       pos.x > maxX || pos.y > maxY) {
        return false;
    }
    else {
        return true;
    }
 
}

bool pgeRippleSprite::isTouchInsideSprite(cocos2d::CCTouch *pTouch)
{
    CCPoint pos;
    pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    pos = this->convertToNodeSpace(pos);
    
    return this->isPointInsideSprite(pos);
}

#pragma mark - touch events

bool pgeRippleSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!this->isTouchInsideSprite(pTouch)) {
        return false;
    }
    
    this->ccTouchMoved(pTouch, pEvent);
    return true;
}



void pgeRippleSprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    _defRipple.pos = pTouch->getLocationInView();
    _defRipple.pos = CCDirector::sharedDirector()->convertToGL(_defRipple.pos);
    _defRipple.pos = this->convertToNodeSpace(_defRipple.pos);
   this->addRipple( RIPPLE_TYPE_WATER, &_defRipple );
    
}


void pgeRippleSprite::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //no-op
}


void pgeRippleSprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
   //no-op
}


void pgeRippleSprite::onEnterTransitionDidFinish()
{
    CCSprite::onEnterTransitionDidFinish();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


void pgeRippleSprite::onExit()
{
    CCSprite::onExit();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

#define MIN_QUAD_COUNT_X (20)
#define MAX_QUAD_COUNT_X (60)

#define MIN_QUAD_COUNT_Y (10)
#define MAX_QUAD_COUNT_Y (40)

#define MIN_RADIUS (150)
#define MAX_RADIUS (400)

#define MIN_STRENGTH (0.8f)
#define MAX_STRENGTH (2.0f)

#define MIN_CYCLE (0.1f)
#define MAX_CYCLE (0.3f)

#define MIN_LIFESPAN (1.0f)
#define MAX_LIFESPAN (2.0f)

#define MIN_CHILD_MODIFIER (2.0f)
#define MAX_CHILD_MODIFIER (5.0f)

//#define MIN_POS_X (0)
//#define MAX_POS_X (1136)
//
//#define MIN_POS_Y (0)
//#define MAX_POS_Y (640)


//#define RIPPLE_DEFAULT_RADIUS                   384//100
#define RIPPLE_DEFAULT_RIPPLE_CYCLE             0.25f       // timing on ripple ( 1/frequenzy )
#define RIPPLE_DEFAULT_LIFESPAN                 1.4f        // entire ripple lifespan
#define RIPPLE_DEFAULT_STRENGTH                 1.f


int pgeRippleSprite::genValue( int min, int max) {
    int value = rand() % (max -  min);
    return value + min;
}


float pgeRippleSprite::genValue( float min, float max) {
    
    int base = ( max * 100 - min * 100);
    int value = rand() % base;
    return min + value / 100.f;
}

void pgeRippleSprite::createAutoRipples() {
    
//    _defRipple.radius = RIPPLE_DEFAULT_RADIUS;
    _defRipple.radius = AppDelegate::SCREEN_HEIGHT / 2;
    _defRipple.cycle = RIPPLE_DEFAULT_RIPPLE_CYCLE;
    _defRipple.lifeSpan = RIPPLE_DEFAULT_LIFESPAN;
    _defRipple.strength = RIPPLE_DEFAULT_STRENGTH;

    
    for (int i = 0; i < DEFAULT_RIPPLES_COUNT; i++) {
        _arrAutoRipples[i].radius = genValue(MIN_RADIUS, MAX_RADIUS);
        _arrAutoRipples[i].strength = genValue(MIN_STRENGTH, MAX_STRENGTH);
        _arrAutoRipples[i].cycle = genValue(MIN_CYCLE, MAX_CYCLE);
        _arrAutoRipples[i].lifeSpan = genValue(MIN_LIFESPAN, MAX_LIFESPAN);
        _arrAutoRipples[i].pos = ccp(genValue(0, AppDelegate::SCREEN_WIDTH),  // x
                                     genValue(0, AppDelegate::SCREEN_HEIGHT)); // y
        

    }

}

void pgeRippleSprite::autoRipplesParents() {
    
  //  this->unschedule(schedule_selector(pgeRippleSprite::autoRipplesParents));
    int count = rand()%DEFAULT_RIPPLES_COUNT;

    for (int i = 0; i < count; i++) {
        float delay = genValue(0.0f, 3.0f);
        this->scheduleOnce(schedule_selector(pgeRippleSprite::autoRipplesChildren), delay);

    }
    
}

void pgeRippleSprite::autoRipplesChildren() {
   //  this->unschedule(schedule_selector(pgeRippleSprite::autoRipplesChildren));
    _curAutoRipple = &_arrAutoRipples[rand()%DEFAULT_RIPPLES_COUNT];
    addRipple(RIPPLE_TYPE_WATER, _curAutoRipple);
}