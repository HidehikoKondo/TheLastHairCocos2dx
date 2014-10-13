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
#include "AppCCloudPlugin.h"
#include "NativeCodeAst.h"
#include "NativeCodeAdmob.h"

#define DEF_LEADER_BOARD   (1108)

#define DEF_APP_DL_URL_ANDROID ("http://goo.gl/VKAoCX")

USING_NS_CC;

using namespace CocosDenshion;
using namespace AstExt;

GameOverLayer::GameOverLayer()
:m_score(0)
{
    
}
GameOverLayer::~GameOverLayer()
{
    
}

GameOverLayer * GameOverLayer::create(unsigned long score)
{
    GameOverLayer * ret = new GameOverLayer();
    if(ret && ret->init(score))
    {
        ret->autorelease();
    }
    else
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

bool GameOverLayer::init(unsigned long score)
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
    
    CCLayer * layer = CCLayer::create();
    this->addChild(layer, 1);
    layer->setPosition(ccp(0,-size.height));
    layer->runAction(CCSequence::create(CCMoveTo::create(1.0f, ccp(0,0)),NULL));
    
    //馬鹿モーン
    CCSprite * bakamon = CCSprite::create("game/bakamon.png");
    this->addChild(bakamon,1);
    bakamon->setPosition(ccp(size.width * 0.5f,size.height * 0.4f));
    bakamon->setScale(0.5f);
    CCArray * seq1 = CCArray::create();
    CCArray * seq2 = CCArray::create();
    seq1->addObject(CCMoveTo::create(0.5f, ccp(size.width * 0.5f,size.height * 0.8f)));
    seq2->addObject(CCScaleTo::create(0.5f, 1.0f));
    bakamon->runAction(CCSpawn::createWithTwoActions(CCSequence::create(seq1),CCSequence::create(seq2)));
    
    CCMenu * menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    layer->addChild(menu);

    //ハイスコアの取得
    unsigned long hiscore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HiScore", score);

    if(hiscore <= score)
    {
        hiscore = score;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("HiScore", score);

        //ネットワーク上にデータ送信
        AppCCloudPlugin::Gamers::setLeaderBoard(DEF_LEADER_BOARD, static_cast<int>(hiscore));
    }
    char buff[50] = "";
    //最高記録
    sprintf(buff, "最高記録：%lu本抜き",hiscore);
    CCLabelTTF * HiScoreLabel = CCLabelTTF::create(buff, "Arial", 40);
    HiScoreLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.7f));
    layer->addChild(HiScoreLabel,1);
    //今回の記録
    sprintf(buff, "今回記録：%lu本抜き",score);
    CCLabelTTF * playScoreLabel = CCLabelTTF::create(buff, "Arial", 40);
    playScoreLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.625f));
    layer->addChild(playScoreLabel,1);
    
    //戻るボタン
    CCSprite * backNormal = CCSprite::create("game/endbutton.png");
    CCSprite * backSelect = CCSprite::create("game/endbutton.png");
    CCMenuItemSprite * label = CCMenuItemSprite::create(backNormal,backSelect, this, menu_selector(GameOverLayer::moveToTitle));
    
    label->setPosition(ccp(size.width * 0.5f,size.height * 0.55f));
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
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLog("ゲームオーバー　インタースティシャル表示");
    AdmobExt::NativeCodeAdmob::showInterstitial();
#endif
    
    //戻る音
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_TITLE_BACK);


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLog("ゲームオーバー　インタースティシャルロード");
    AdmobExt::NativeCodeAdmob::loadInterstitial();
#endif
    
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
