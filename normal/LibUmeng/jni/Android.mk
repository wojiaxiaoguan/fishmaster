LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

define walk
	$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(filter %.cpp, $(ALLFILES))
FILE_LIST += $(filter %.c, $(ALLFILES))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d)
LOCAL_C_INCLUDES := $(FILE_INCLUDES)

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static

#----------------- 友盟游戏统计分析 Start -----------------
LOCAL_WHOLE_STATIC_LIBRARIES += mobclickcpp_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
#----------------- 友盟游戏统计分析 End -----------------

include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,libMobClickCpp)

#----------------- 友盟游戏统计分析 Start -----------------
$(call import-module,curl/prebuilt/android)
#----------------- 友盟游戏统计分析 End -----------------