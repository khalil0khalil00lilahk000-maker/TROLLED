
#include <Geode/Geode.hpp>
#include <Geode/modify/CCTouchDispatcher.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;


// ============================================================
// TROLL
// ============================================================

static void showTroll() {
    auto scene = CCDirector::sharedDirector()->getRunningScene();

    if (!scene)
        return;

    // Chargement de la ressource du mod
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

    // Centre de l'écran
    image->setPosition(screen / 2);

    // Plein écran
    image->setScaleX(screen.width / imageSize.width);
    image->setScaleY(screen.height / imageSize.height);

    // Au-dessus de tout
    image->setZOrder(999999);

    scene->addChild(image);

    // ========================================================
    // 5 APPARITIONS
    // Chaque apparition dure 2 secondes
    // ========================================================

    auto sequence = CCSequence::create(

        // Apparition 1
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

        // Apparition 2
        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

        // Apparition 3
        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

        // Apparition 4
        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

        // Apparition 5
        CCFadeIn::create(0.12f),
        CCDelayTime::create(2.0f),
        CCFadeOut::create(0.12f),

        // Suppression finale
        CallFuncExt::create([image]() {
            image->removeFromParentAndCleanup(true);
        }),

        nullptr
    );

    image->runAction(sequence);
}


// ============================================================
// SOURIS / TACTILE
// ============================================================

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

        // Premier événement tactile / souris
        if (index == 0) {
            log::info("TROLL : clic/tactile détecté");
            showTroll();
        }
    }
};


// ============================================================
// CLAVIER
// ============================================================

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

        // N'importe quelle touche du clavier
        if (isKeyDown && !isKeyRepeat) {
            log::info("TROLL : touche clavier détectée");
            showTroll();
        }

        return result;
    }
};
