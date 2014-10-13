//
//  TitleScene.cpp
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#include "TitleScene.h"
#include "TweezeGameScene.h"
#include "RunkingScene.h"
#include "SimpleAudioEngine.h"
#include "NativeCodeAst.h"
#include "NativeCodeAdmob.h"
#include "SoundDef.h"
#include "AppCCloudPlugin.h"

using namespace cocos2d;
using namespace CocosDenshion;

/**
 * タイトル画面
 */
CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AstExt::NativeCodeAst::showAst();
#endif
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor * layer = CCLayerColor::create(ccc4(182, 255, 175, 255), size.width, size.height);
    this->addChild(layer,0);

    CCSprite* pSprite = CCSprite::create("title/title.png");
    pSprite->setTag(5000);
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height*0.85f) );
    
    CCMenu * StartMenu = CCMenu::create();
    StartMenu->setPosition(CCPointZero);
    this->addChild(StartMenu);

    //スタートボタン
    CCSprite* pChallengeImg = CCSprite::create("title/startbutton.png");
    pChallengeImg->setScale(2.0f);
    CCSprite* pChallengeImg_sel = CCSprite::create("title/startbutton.png");
    pChallengeImg_sel->setScale(2.05f);
    CCMenuItemSprite* challengeButton = CCMenuItemSprite::create(pChallengeImg,pChallengeImg_sel, this, menu_selector(TitleScene::NextScene));

    pChallengeImg->setPosition(ccp(pChallengeImg->getContentSize().width * 0.5f,
                                   pChallengeImg->getContentSize().height * 0.5f));
    pChallengeImg->setAnchorPoint(ccp(0.5f,0.5f));
    pChallengeImg_sel->setPosition(pChallengeImg->getPosition());
    pChallengeImg_sel->setAnchorPoint(ccp(0.5f,0.5f));
    
    challengeButton->setAnchorPoint(ccp(0.5f,0.5f));
    challengeButton->setPosition(ccp(size.width/2,size.height * 0.55f));
    challengeButton->setScale(0.5f);
    StartMenu->addChild(challengeButton);

    //ランキングボタン
    CCSprite* pRankingImg = CCSprite::create("title/rankbutton.png");
    pRankingImg->setScale(2.0f);
    CCSprite* pRankingImg_sel = CCSprite::create("title/rankbutton.png");
    pRankingImg_sel->setScale(2.05f);
    CCMenuItemSprite* rankingButton = CCMenuItemSprite::create(pRankingImg,pRankingImg_sel, this, menu_selector(TitleScene::moveSceneToRanking));

    pRankingImg->setPosition(ccp(pRankingImg->getContentSize().width * 0.5f,
                                   pRankingImg->getContentSize().height * 0.5f));
    pRankingImg->setAnchorPoint(ccp(0.5f,0.5f));
    pRankingImg_sel->setPosition(pRankingImg->getPosition());
    pRankingImg_sel->setAnchorPoint(ccp(0.5f,0.5f));
    
    rankingButton->setAnchorPoint(ccp(0.5f,0.5f));
    rankingButton->setPosition(ccp(size.width/2,size.height * 0.45f));
    rankingButton->setScale(0.5f);
    StartMenu->addChild(rankingButton);
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    return true;
}
/**
 * 選択画面にいく
 */
void TitleScene::NextScene(CCObject*obj)
{
    CCSprite *sprite = static_cast<CCSprite*>(this->getChildByTag(5000));
    sprite->stopAllActions();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AstExt::NativeCodeAst::hideAst();
#endif
    
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_START);
    
    CCDirector::sharedDirector()->replaceScene(
                                               CCTransitionSlideInR::create(0.25f,TweezeGameScene::scene())
                                               );
}

/**
 * ランキング
 */
void TitleScene::moveSceneToRanking(CCObject*obj)
{
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_START);
    
//    CCDirector::sharedDirector()->replaceScene(
//                                               CCTransitionSlideInR::create(0.25f,RunkingScene::scene())
//                                               );
    
    //リーダーボードの表示
    AppCCloudPlugin::Gamers::showGamersView();
}

void TitleScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
