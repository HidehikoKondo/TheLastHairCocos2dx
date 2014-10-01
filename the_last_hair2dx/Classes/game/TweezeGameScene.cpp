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
#include "GameOverLayer.h"

//波平の高さオフセット(中心から)
#define DEF_NAMIHEI_Y_OFFSET (-150)

//波平の毛の高さオフセット(中心から)
#define DEF_HAIR_Y_OFFSET (250)

#define DEF_FONT_SIZE (64)
#define DEF_LOSS_LABEL_Y_OFFSET (-150)
#define DEF_COMBO_LABEL_Y_OFFSET (-200)

#define DEF_HAND_X_OFFSET (0)
#define DEF_HAND_Y_OFFSET (250)
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
    this->m_LossHairCountLabelMain = CCLabelTTF::create("999999999 本抜き ", "Arial", DEF_FONT_SIZE,CCSizeMake(640,DEF_FONT_SIZE*1.15),kCCTextAlignmentRight);
    this->m_LossHairCountLabelMain->setColor(ccc3(0x00, 0x00, 0x00));
    this->addChild(this->m_LossHairCountLabelMain, 110);
    this->m_LossHairCountLabelMain->setAnchorPoint(ccp(1.0,0.0));
    this->m_LossHairCountLabelMain->setPosition(ccp(size.width - 3 ,size.height + DEF_LOSS_LABEL_Y_OFFSET + 3));
    this->m_LossHairCountLabelSub = CCLabelTTF::create("999999999 本抜き ", "Arial", DEF_FONT_SIZE,CCSizeMake(640,DEF_FONT_SIZE*1.15),kCCTextAlignmentRight);
    this->addChild(this->m_LossHairCountLabelSub, 100);
    this->m_LossHairCountLabelSub->setAnchorPoint(ccp(1.0,0.0));
    this->m_LossHairCountLabelSub->setPosition(ccp(size.width,size.height + DEF_LOSS_LABEL_Y_OFFSET));
    
    //音声ファイル読み込み
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_COMBO);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    this->refleshCountLabe();
    
    return true;
}

/**
 * コンボヘアーアニメーション
 */
void TweezeGameScene::onAnimationComboHair()
{
    //毛の抜ける音
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_COMBO);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite * comboString = CCSprite::create("game/umiheicombo.png");
    this->addChild(comboString,100);
    comboString->setPosition(ccp(size.width * 0.5f,size.height + DEF_COMBO_LABEL_Y_OFFSET));
    
    CCArray * seq1 = CCArray::create();
    CCArray * seq2 = CCArray::create();
    seq1->addObject(CCMoveBy::create(2.0f, ccp(0,40)));
    seq1->addObject(CCCallFunc::create(comboString, callfunc_selector(CCSprite::removeFromParent)));
    seq2->addObject(CCFadeOut::create(2.0f));
    comboString->runAction(CCSpawn::createWithTwoActions(CCSequence::create(seq1),CCSequence::create(seq2)));
}

/**
 * 抜けた毛の本数
 */
void TweezeGameScene::countUpHair()
{
    //通常の毛
    this->m_score++;
    
    this->refleshCountLabe();

}
/**
 * ラベルの再表示
 */
void TweezeGameScene::refleshCountLabe()
{
    char buff[30] = "";
    sprintf(buff, "%ld本抜き",this->m_score);
    this->m_LossHairCountLabelMain->setString(buff);
    this->m_LossHairCountLabelSub->setString(buff);
    
}

/**
 * タップ開始
 */
bool TweezeGameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->m_Hand->setVisible(true);
    
    this->m_handMove = 0.0f;
    this->m_lossFlg = false;

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->m_Hand->setPosition(ccp(size.width + DEF_HAND_X_OFFSET,
                                  size.height*0.5f + DEF_HAND_Y_OFFSET + this->m_handMove));
    
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
    if(this->m_handMove < -100 ) this->m_handMove = -100;
    
    this->m_Hand->setPosition(ccp(size.width + DEF_HAND_X_OFFSET,
                                  size.height*0.5f + DEF_HAND_Y_OFFSET + this->m_handMove));
    
    //ゲームオーバー判定
    if(rand()%255 == 0)
    {
        CCLOG("GAME_OVER");
        this->showGameOverLayer();
    }
    
    //毛の抜ける範囲
    if(this->m_lossFlg == false && this->m_handMove > DEF_LOSS_OF_LENGTH)
    {
        this->m_lossFlg = true;
        this->m_lastHair->resetSize();

        //毛の抜ける音
        SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_LOSS_HAIR);
        
        if(HT_ONE == this->m_lastHair->getHairType())
        {
            this->countUpHair();
        }
        else
        {
            //２本毛
            this->m_score*=2;
            
            this->refleshCountLabe();
            
            this->onAnimationComboHair();
        }
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
        
        if(rand()%32 == 0)
        {
            this->m_lastHair->setHairType(HT_TWO);
        }
        else
        {
            this->m_lastHair->setHairType(HT_ONE);
        }
        //毛が生えてくる
        this->m_lastHair->onActionHairGrows();
        this->m_lastHair->setPosition(ccpAdd(this->m_GroundFother->getPosition(),
                                             ccp(0,DEF_HAIR_Y_OFFSET)));
    }
    else
    {
        //毛が抜けていない
        this->m_lastHair->onActionCurlyHair();

        //毛の抜ける音
        SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_MISS);
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

/**
 * ゲームオーバー
 */
void TweezeGameScene::showGameOverLayer()
{
    this->setTouchEnabled(false);
    GameOverLayer *Over = GameOverLayer::create(this->m_score);
    this->addChild(Over,100000);

    //ゲームオーバーの音
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_GAME_OVER);
}

