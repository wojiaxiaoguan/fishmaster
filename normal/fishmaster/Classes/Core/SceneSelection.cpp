//
//  SceneSelection.cpp
//  fish
//
//  
//
//

#include "SceneSelection.h"

#define SCENE_UNLOCK_FLAG_STR ("sceneUnlockFlagStr")


SceneSelectionManager* SceneSelectionManager::sharedManager = NULL;

SceneSelectionManager* SceneSelectionManager::sharedSceneSelectionManager()
{
    if (sharedManager == NULL) {
        
        sharedManager = new SceneSelectionManager();
        static Cleaner cleaner;
        

    }
    return sharedManager;
    
}

SceneSelectionManager::SceneSelectionManager(){
    
    unlockFlag = CCUserDefault::sharedUserDefault()->getIntegerForKey(SCENE_UNLOCK_FLAG_STR, 1);
    
    arrSceneInfos = NULL;
    
    arrSceneInfos = CCArray::createWithContentsOfFileThreadSafe(CCFileUtils::sharedFileUtils()->fullPathForFilename("sceneInfo.plist").c_str());
    if (arrSceneInfos != NULL) {
        arrSceneInfos->retain();
    }
}

SceneSelectionManager::~ SceneSelectionManager(){
    CC_SAFE_RELEASE(arrSceneInfos);
}


int SceneSelectionManager::count() {
    if(arrSceneInfos != NULL) {
        return arrSceneInfos->count();
    }
    return 0;
}


CCDictionary* SceneSelectionManager::infoForScene( Scene index ) {
    if (index < 0 || index >= SceneNum) {
        return NULL;
    }
    
    int tag = (unlockFlag >> index) & 1;
    
    CCInteger *ccTag = CCInteger::create(tag);
    
  //  CCLog("index = %d tag = %d", index, tag);
    
    CCDictionary *dict = (CCDictionary*)arrSceneInfos->objectAtIndex(index);
    if (dict != NULL) {
        dict->setObject(ccTag, SCENE_LOCK_FLAG);
    }
    
    return dict;

}

void SceneSelectionManager::setSceneStatus(Scene index, SceneStatus status) {
    if (index < 0 || index >= SceneNum) {
        return;
    }
    
    unlockFlag |= ( status << index);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(SCENE_UNLOCK_FLAG_STR, unlockFlag);
    CCUserDefault::sharedUserDefault()->flush();
}

SceneStatus SceneSelectionManager::sceneStatus( Scene index ) {
    if (index < 0 || index >= SceneNum) {
        return SceneLocked;
    }
    return SceneStatus( (unlockFlag >> index) & 1 );

    
}
