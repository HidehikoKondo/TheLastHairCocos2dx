//
//  TweezeGameScene.cpp
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/07/06.
//
//

#include "TweezeGameScene.h"
#include "SimpleAudioEngine.h"
#include "NativeCodeAst.h"
#include "SoundDef.h"
#include "GameRuleManager.h"
#include "GameOverLayer.h"

#define DEF_NAMIHEI_Y_OFFSET (-100)

#define DEF_HAIR_Y_OFFSET (200)

#define DEF_FONT_SIZE (64)
#define DEF_LOSS_LABEL_Y_OFFSET (-100)

#define DEF_HAND_X_OFFSET (0)
#define DEF_HAND_Y_OFFSET (200)
#define DEF_HAND_SCALE_RATE (1.05f)

#define DEF_LOSS_OF_LENGTH (240.0f)

using namespace cocos2d;
using namespace CocosDenshion;

/**
 * コンストラクタ
 */
TweezeGameScene::TweezeGameScene()
:m_GroundFother(NULL)
,m_lastHair(NULL)
,m_Hand(NULL)
,m_score(0)
,m_handMove(0)
,m_LossHairCountLabelMain(NULL)
,m_LossHairCountLabelSub(NULL)
,m_lossFlg(false)
{
}
/**
 * デストラクタ
 */
TweezeGameScene::~TweezeGameScene()
{
}

CCScene* TweezeGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TweezeGameScene *layer = TweezeGameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TweezeGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor * backGround = CCLayerColor::create(ccc4(165, 255, 227,0xFF),size.width,size.height);
    backGround->setPosition(CCPointZero);
    this->addChild(backGround,0);
    
    //お父さん
    this->m_GroundFother = CCSprite::create("game/namiheihead.png");
    this->addChild(this->m_GroundFother,10);
    this->m_GroundFother->setPosition(ccp(size.width * 0.5f,size.height * 0.5f + DEF_NAMIHEI_Y_OFFSET));
    
    //お父さんの毛
    this->m_lastHair = LastHairModel::create();
    this->addChild(this->m_lastHair,20);
    this->m_lastHair->setPosition(ccpAdd(this->m_GroundFother->getPosition(),
                                         ccp(0,DEF_HAIR_Y_OFFSET)));
    
    //手
    this->m_Hand = CCSprite::create("game/finger.png");
    this->m_Hand->setAnchorPoint(ccp(1.0f,0.0f));
    this->m_Hand->setScale(DEF_HAND_SCALE_RATE);
    this->addChild(this->m_Hand,30);
    this->m_Hand->setPosition(ccp(size.width + DEF_HAND_X_OFFSET,
                                  size.height* 0.5f + DEF_HAND_Y_OFFSET));
    this->m_Hand->setVisible(false);
    
    //抜いた数
    this->m_LossHairCountLabelMain = CCLabelTTF::create("999999999 本抜き ", "Arial", DEF_FONT_SIZE,CCSizeMake(640,DEF_FONT_SIZE*1.05),kCCTextAlignmentRight);
    this->m_LossHairCountLabelMain->setColor(ccc3(0x00, 0x00, 0x00));
    this->addChild(this->m_LossHairCountLabelMain, 110);
    this->m_LossHairCountLabelMain->setAnchorPoint(ccp(1.0,0.0));
    this->m_LossHairCountLabelMain->setPosition(ccp(size.width - 3 ,size.height + DEF_LOSS_LABEL_Y_OFFSET + 3));
    this->m_LossHairCountLabelSub = CCLabelTTF::create("999999999 本抜き ", "Arial", DEF_FONT_SIZE,CCSizeMake(640,DEF_FONT_SIZE*1.05),kCCTextAlignmentRight);
    this->addChild(this->m_LossHairCountLabelSub, 100);
    this->m_LossHairCountLabelSub->setAnchorPoint(ccp(1.0,0.0));
    this->m_LossHairCountLabelSub->setPosition(ccp(size.width,size.height + DEF_LOSS_LABEL_Y_OFFSET));
    
    //音声ファイル読み込み
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_GAME_OVER);
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_GOOD);
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_RUSH);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    return true;
}


/**
 * タップ開始
 */
bool TweezeGameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->m_Hand->setVisible(true);
    
    this->m_handMove = 0.0f;
    this->m_lossFlg = false;
    
    return true;
}
/**
 * タップ移動
 */
void TweezeGameScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint moveVec = pTouch->getLocation() - pTouch->getStartLocation();
    
    this->m_handMove = moveVec.y;
    
    this->m_Hand->setPosition(ccp(size.width + DEF_HAND_X_OFFSET,
                                  size.height*0.5f + DEF_HAND_Y_OFFSET + this->m_handMove));
    
    //毛の抜ける範囲
    if(this->m_handMove > DEF_LOSS_OF_LENGTH)
    {
        this->m_lossFlg = true;
        this->m_lastHair->resetSize();
    }
    
    if(this->m_lossFlg)
    {
        //毛を移動する
        this->m_lastHair->setPosition(ccpAdd(this->m_GroundFother->getPosition(),
                                             ccp(0,DEF_HAIR_Y_OFFSET + this->m_handMove)));
    }
    else
    {
        //毛をのばす
        this->m_lastHair->onStretch(this->m_handMove);
    }
}
/**
 * タップ終了
 */
void TweezeGameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->m_Hand->setVisible(false);
    
    if(this->m_lossFlg)
    {
        //毛が抜けている
        
        //毛が生えてくる
        this->m_lastHair->onActionHairGrows();
        this->m_lastHair->setPosition(ccpAdd(this->m_GroundFother->getPosition(),
                                             ccp(0,DEF_HAIR_Y_OFFSET)));
    }
    else
    {
        //毛が抜けていない
        this->m_lastHair->onActionCurlyHair();
    }
    
    this->m_handMove = 0.0f;
}
/**
 * タップキャンセル
 */
void TweezeGameScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->m_Hand->setVisible(false);
    
}


