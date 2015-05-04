//
//  Sound.h
//  paigow-ipad
//
//
//

#ifndef __paigow_ipad__Sound__
#define __paigow_ipad__Sound__

#include "headerLibrary.h"
#include "SimpleAudioEngine.h"
#include <map>
using namespace std;

class Sound : CCObject {
public:
    Sound();
    virtual ~Sound();
    static Sound* Instance();
    
private:
    CCDictionary *dic_sound;
    
public:
    void initSound();

    void playMusic(const char* file);
//    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    int playEffect(const char* file, bool aLoop = false);
    
    
    void stopEffect(int aEffectId);
    
    // 设置是否播放语音
    void switchSound();
    
    bool getIsCloseSound()
    {
        return isCloseSound_;
    };
     void setCloseSound(bool aIsClose);
private:
   
    
    
private:
    bool   isCloseSound_;
};

#endif /* defined(__paigow_ipad__Sound__) */
