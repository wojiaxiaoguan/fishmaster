//
//  SceneSelection.h
//  fish
//
//  
//
//

#ifndef __fish__SceneSelection__
#define __fish__SceneSelection__
#include "headerLibrary.h"
#include "common.h"

//场景信息
enum Scene{
    SceneMystical,
    SceneDream,
    SceneProfusion,
    SceneHistoric,
    SceneSeaMonsterNormal,
    SceneSeaMonsterDifficulty,
    SceneNum
};

enum SceneStatus{
     SceneLocked,
     SceneUnlocked,
     SceneStatusNum
};
#define SCENE_NAME ("name")
#define SCENE_DESC ("desc")
#define SCENE_EXCLUSIVE ("exclusive")
#define SCENE_IMAGE ("image")
#define SCENE_LOCK_FLAG ("isLocked")


//场景选择
class SceneSelectionManager  {
    
public:
    ~SceneSelectionManager();
    static SceneSelectionManager* sharedSceneSelectionManager();
    
    //场景数量
    int count();
    
    CCDictionary* infoForScene( Scene index );
    
    //默认为解锁
    void setSceneStatus(Scene index, SceneStatus = SceneUnlocked);
    SceneStatus sceneStatus( Scene index );
    
    
private:
    SceneSelectionManager();
    
private:
    
private:
    class Cleaner
    {
    public:
        Cleaner(){}
        ~Cleaner()
        {
            if(SceneSelectionManager::sharedSceneSelectionManager() != NULL) {
                delete SceneSelectionManager::sharedSceneSelectionManager();
            }
        }
    };
    
    
    
private:
    static SceneSelectionManager *sharedManager;
    
    CCArray *arrSceneInfos;
    unsigned int unlockFlag;
};



#endif /* defined(__fish__SceneSelection__) */

