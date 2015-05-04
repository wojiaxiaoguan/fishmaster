//
//  headerLibrary.h
//  paigow-iphone
//
//  
//
//

#pragma once

#include "cocos2d.h"
#include "common.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace extension;

#define SceneReplaceTime 0.3f

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include <string.h>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <map>
using std::pair;
using std::map;

#include <deque>
using std::deque;

#include <algorithm>
#include <utility>
#include <cmath>
#include <time.h>


// 层事件优先级定义
enum
{
    EPriorityCommonTip      = -501,        //
    
    EPriorityLinking        = -500,
    
    EPriorityStore     = -301,        // Store
    
    EPriorityStoreTable     = -302,        // Store Table
    
    
    EPrioritySubStoreLayer     = -303,        // Store Table
    
};

#define TAG_GM_WHISPER_LAYER (8964)

#define Conn(x,y) x##y
#define XConn(x,y) Conn(x,y)

#define ToString(x) #x
#define XStr(x) ToString(x)
