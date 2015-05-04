LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
	../../Classes/config/CConfig.cpp \
	../../Classes/Core/Bullet.cpp \
	../../Classes/Core/Cannon.cpp \
	../../Classes/Core/Coin.cpp \
	../../Classes/Core/Fish.cpp \
	../../Classes/Core/FishGroup.cpp \
	../../Classes/Core/FishMatrix.cpp \
	../../Classes/Core/FishPath.cpp \
	../../Classes/Core/FlipCardBonus.cpp \
	../../Classes/Core/Helper.cpp \
	../../Classes/Core/Mine.cpp \
	../../Classes/Core/MyFishPath.cpp \
	../../Classes/Core/RollNum.cpp \
	../../Classes/Core/SceneSelection.cpp \
	../../Classes/Core/SeqLoginBonus.cpp \
	../../Classes/Data/GameData.cpp \
	../../Classes/Foundation/AppDelegate.cpp \
	../../Classes/Foundation/FishUtils.cpp \
	../../Classes/Foundation/pgPlatformFactory.cpp \
	../../Classes/Foundation/Sound.cpp \
	../../Classes/Ui/CCB_Template.cpp \
	../../Classes/Ui/CCRippleSprite.cpp \
	../../Classes/Ui/FlipCardBonusLayer.cpp \
	../../Classes/Ui/GameAwardLayer.cpp \
	../../Classes/Ui/GameLayer.cpp \
	../../Classes/Ui/GameStore.cpp \
	../../Classes/Ui/GameUpgrade.cpp \
	../../Classes/Ui/InitRechargeLayer.cpp \
	../../Classes/Ui/introLayer.cpp \
	../../Classes/Ui/RippleGrid3D.cpp \
	../../Classes/Ui/SceneSelectionLayer.cpp \
	../../Classes/Ui/SeqLoginBonusLayer.cpp \
	../../Classes/Ui/TaskDetailLayer.cpp \
	../../Classes/Ui/WaveRippleScene.cpp \
	../../Classes/common/ToolsOper.cpp\
	../../Classes/Platform/JniUtil.cpp\
	../../Classes/Platform/PlatformHandler.cpp  

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/Core \
                    $(LOCAL_PATH)/../../Classes/Ui \
                    $(LOCAL_PATH)/../../Classes/Data \
                    $(LOCAL_PATH)/../../Classes/Foundation \
	            $(LOCAL_PATH)/../../Classes/common \
		    $(LOCAL_PATH)/../../Classes/Platform \
                    $(LOCAL_PATH)/../../Classes/Network

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
