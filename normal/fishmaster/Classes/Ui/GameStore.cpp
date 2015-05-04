//
//  GameStore.cpp
//  fish
//
//  
//
//

#include "GameStore_cpp.h"
//#include "../thirdparty/IThirdParty.h"
//#include "../thirdparty/ThirdPartyFactory.h"
#include "PlatformHandler.h"
void GameStoreLayer::buyGoods(ProductType pType, const char *orderId, int token)
{
    DF_LOG("GameStoreLayer::buyGoods ProductType = %d,orderId=%s,token = %d",pType,orderId,token);
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    //Test by andy 2015-04-02
//    GameData* pData = GameData::getSharedGameData();
//    pData->provideProduct(pType);
#endif
    //del by andy 2015/03/16
//    IThirdParty* p3rdParty = ThirdPartyFactory::Inst()->thirdParty();
//    if (p3rdParty)
//    {
//        p3rdParty->payInit(this);
//        p3rdParty->payment(GameData::getSharedGameData()->getProductPrice(pType), 1, GameData::getSharedGameData()->getProductConstId(pType).c_str(), GameData::getSharedGameData()->getProductName(pType).c_str(), orderId, token);
//    }
#ifndef TEST_BAIBAO
    PlatformHandler::getInstance()->pay(pType);
#else
    GameData* pData = GameData::getSharedGameData();
    pData->provideProduct(pType);
#endif
}