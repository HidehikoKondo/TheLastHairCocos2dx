//
//  LastHairModel.cpp
//  the_last_hair2dx
//
//  Created by 大原幸夫 on 2014/09/13.
//
//

#include "LastHairModel.h"

USING_NS_CC;

#define DEF_DEFAULT_HAIR_WIDTH_RATE (1.0f)
#define DEF_DEFAULT_HAIR_HEIGHT_RATE (0.6f)

LastHairModel::LastHairModel()
:m_HairSprite(NULL)
,m_type(HT_ONE)
{
    
}
LastHairModel::~LastHairModel()
{
    
}

bool LastHairModel::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
    this->setHairType(HT_ONE);
    return true;
}

/**
 * 初期化する
 */
void LastHairModel::initialize()
{
    
}
/**
 * 毛の大きさを初期値に戻す
 */
void LastHairModel::resetSize()
{
    if(NULL == this->m_HairSprite)return;
    this->setContentSize(this->m_HairSprite->getContentSize());
    this->setAnchorPoint(ccp(0.5f, 0.0f));
    this->m_HairSprite->setPosition(ccp(this->getContentSize().width * 0.5f,0));
    this->m_HairSprite->setAnchorPoint(ccp(0.5f,0.0f));
    
    this->m_HairSprite->setScaleX(DEF_DEFAULT_HAIR_WIDTH_RATE);
    this->m_HairSprite->setScaleY(DEF_DEFAULT_HAIR_HEIGHT_RATE);
}
/**
 * 毛を伸ばす
 * @param stretchLength 伸ばす距離
 */
void LastHairModel::onStretch(float stretchLength)
{
    float minHeight = this->m_HairSprite->getContentSize().height * DEF_DEFAULT_HAIR_HEIGHT_RATE;
    float sumHeight = minHeight + stretchLength;
    this->m_HairSprite->setScaleY(sumHeight / this->m_HairSprite->getContentSize().height);
    
}

/**
 * 毛を縮めるアクション
 */
void LastHairModel::onActionCurlyHair()
{
    this->m_HairSprite->stopAllActions();
    
    CCArray * seq = CCArray::create();
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,0.25f));
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,DEF_DEFAULT_HAIR_HEIGHT_RATE));
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,0.25f));
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,DEF_DEFAULT_HAIR_HEIGHT_RATE));
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,0.25f));
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,DEF_DEFAULT_HAIR_HEIGHT_RATE));
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,0.25f));
    seq->addObject(CCScaleTo::create(0.06f, DEF_DEFAULT_HAIR_WIDTH_RATE,DEF_DEFAULT_HAIR_HEIGHT_RATE));
    this->m_HairSprite->runAction(CCSequence::create(seq));
}

/**
 * 毛を抜くアクション
 */
void LastHairModel::onActionLossOfHair()
{
    
}
/**
 * 毛が生えるアクション
 */
void LastHairModel::onActionHairGrows()
{
    this->m_HairSprite->stopAllActions();
    this->m_HairSprite->setScaleY(0);
    
    CCArray * seq = CCArray::create();
    seq->addObject(CCScaleTo::create(0.3f, DEF_DEFAULT_HAIR_WIDTH_RATE,DEF_DEFAULT_HAIR_HEIGHT_RATE));
    this->m_HairSprite->runAction(CCSequence::create(seq));
}

/**
 * 毛の種類設定
 * @param stretchLength 伸ばす距離
 */
void LastHairModel::setHairType(HAIR_TYPE value)
{
    this->m_type = value;
    
    if(this->m_HairSprite)
    {
        this->m_HairSprite->removeFromParent();
    }
    switch (value)
    {
        default:
        case HT_ONE:
            this->m_HairSprite = CCSprite::create("game/hair.png");
            break;
        case HT_TWO:
            this->m_HairSprite = CCSprite::create("game/hairtwin.png");
            break;
    }
    
    if(this->m_HairSprite)
    {
        this->addChild(this->m_HairSprite,10);
        this->resetSize();
    }
}

/**
 * 毛の種類取得
 * @param stretchLength 伸ばす距離
 */
HAIR_TYPE LastHairModel::getHairType()
{
    return this->m_type;
}
