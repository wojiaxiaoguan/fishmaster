//
//  platformFactory.h
//  paigow-ipad
//
//  
//
//

#ifndef __paigow_ipad__platformFactory__
#define __paigow_ipad__platformFactory__

#include "pgPlatform.h"

typedef enum enOSType {
    ILLVALID_OS_TYPE,
    OS_iOS,
    OS_Windows,
    OS_Android,
    OS_TYPE_NUM
}LocalOSType;



class IPlatformFactory {
public:
    
    //默认为ios
   static IPlatform *sharedPlatform( LocalOSType type = OS_iOS ) ;
};




#endif /* defined(__paigow_ipad__platformFactory__) */
