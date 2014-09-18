//
//  GameOverLayer.cpp
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/08/20.
//
//

#include "GameOverLayer.h"
#include "TitleScene.h"
#include "SoundDef.h"
#include "SimpleAudioEngine.h"
#include "NativeTweet.h"

#define DEF_APP_DL_URL_ANDROID ("http://goo.gl/VKAoCX")

USING_NS_CC;

using namespace CocosDenshion;

GameOverLayer::GameOverLayer()
:m_score(0)
{
    
}
GameOverLayer::~GameOverLayer()
{
    
}

bool GameOverLayer::init()
{
    if(!CCLayerColor::init())
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    this->setColor(ccc3(0, 0, 0));
    this->setOpacity(0xBF);
    
    CCSprite * back = CCSprite::create("game/house.png");
    this->addChild(back,0);
    back->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
    
    CCMenu * menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    //戻るボタン
    CCSprite * backNormal = CCSprite::create("game/endbutton.png");
    CCSprite * backSelect = CCSprite::create("game/endbutton.png");
    CCMenuItemSprite * label = CCMenuItemSprite::create(backNormal,backSelect, this, menu_selector(GameOverLayer::moveToTitle));
    
    label->setPosition(ccp(size.width * 0.5f,size.height * 0.6f));
    menu->addChild(label);
    
    return true;
}
/**
 * 記録の登録
 */
void GameOverLayer::entoryRecord(long value)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    this->m_score = value;
    
    //文言
    char buff[30];
    sprintf(buff,"%2ld",value);
    
    CCLabelBMFont * recordLabel  = CCLabelBMFont::create(buff, "base/little_number.fnt", 400, kCCTextAlignmentCenter);
    recordLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
    this->addChild(recordLabel);
    
}

void GameOverLayer::moveToTitle()
{
    //戻る音
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_TITLE_BACK);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.25f, TitleScene::scene()));
}

/**
 * tweetする
 */
void GameOverLayer::onTweet()
{
    std::string tweetStr;

    tweetStr += "[TEN] \'Chalenge Mode\' ";

    //文言
    char buff[30];
    sprintf(buff,"%2ld",this->m_score);
    
    tweetStr += buff;
    tweetStr += " ";
    
    //アプリDLの短縮URL
    tweetStr += DEF_APP_DL_URL_ANDROID;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeTweet::openTweetDialog(tweetStr.c_str());
#endif
}
