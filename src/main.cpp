
#include <Geode/Geode.hpp>
#include <Geode/modify/CCTouchDispatcher.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;



static void showTroll() {
    auto scene = CCDirector::sharedDirector()->getRunningScene();

    if (!scene)
        return;


    auto image = CCSprite::create("shrek.png"_spr);

    if (!image) {
        log::error("Impossible de charger shrek.png");
        return;
    }

    auto screen = CCDirector::sharedDirector()->getWinSize();
    auto imageSize = image->getContentSize();

    if (imageSize.width <= 0 || imageSize.height <= 0) {
        log::error("Dimensions invalides pour shrek.png");
        return;
    }

    
    image->setPosition(screen / 2);

   
    image->setScaleX(screen.width / imageSize.width);
    image->setScaleY(screen.height / imageSize.height);

   
    image->setZOrder(999999);

    scene->addChild(image);

    auto sequence = CCSequence::create(

       
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

       
        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

   
        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

      
        CallFuncExt::create([image]() {
            image->removeFromParentAndCleanup(true);
        }),

        nullptr
    );

    image->runAction(sequence);
}




class $modify(TrollTouchDispatcher, CCTouchDispatcher) {

    void touches(
        CCSet* touches,
        CCEvent* event,
        unsigned int index
    ) {
        CCTouchDispatcher::touches(
            touches,
            event,
            index
        );

      
        if (index == 0) {
            log::info("TROLL : clic/tactile détecté");
            showTroll();
        }
    }
};




class $modify(TrollKeyboardDispatcher, CCKeyboardDispatcher) {

    bool dispatchKeyboardMSG(
        enumKeyCodes key,
        bool isKeyDown,
        bool isKeyRepeat,
        double timestamp
    ) {
        auto result =
            CCKeyboardDispatcher::dispatchKeyboardMSG(
                key,
                isKeyDown,
                isKeyRepeat,
                timestamp
            );

       
        if (isKeyDown && !isKeyRepeat) {
            log::info("TROLL : touche clavier détectée");
            showTroll();
        }

        return result;
    }
};
