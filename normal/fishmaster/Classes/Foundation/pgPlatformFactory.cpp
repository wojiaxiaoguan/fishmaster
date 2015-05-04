//
//  platformFactory.cpp
//  paigow-ipad
//
//  
//
//

#include "pgPlatformFactory.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//#include "ios.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#endif


IPlatform *IPlatformFactory::sharedPlatform( LocalOSType type ) {
   static IPlatform platform ;
    switch (type ) {
        case OS_iOS:
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//			static iOS ios;
//			return &ios;
#endif
        }
        break;
            
        case OS_Windows:
        case OS_Android:
            
        default:
            break;
    }
    

    //placeholder
    return &platform;
}