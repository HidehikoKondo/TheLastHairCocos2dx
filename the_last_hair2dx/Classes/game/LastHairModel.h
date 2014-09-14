//
//  LastHairModel.h
//  the_last_hair2dx
//
//  Created by 大原幸夫 on 2014/09/13.
//
//

#ifndef __the_last_hair2dx__LastHairModel__
#define __the_last_hair2dx__LastHairModel__

#include "cocos2d.h"

typedef enum _HAIR_TYPE
{
    HT_ONE,
    HT_TWO
}HAIR_TYPE;

class LastHairModel : public cocos2d::CCNode
{
protected:
    cocos2d::CCSprite * m_HairSprite;
    
    HAIR_TYPE m_type;
public:
    LastHairModel();
    virtual ~LastHairModel();
    CREATE_FUNC(LastHairModel);
    virtual bool init();
    
    /**
     * 初期化する
     */
    virtual void initialize();
    
    /**
     * 毛の大きさを変更する
     */
    virtual void resetSize();
    /**
     * 毛を伸ばす
     * @param stretchLength 伸ばす距離
     */
    virtual void onStretch(float stretchLength);
    
    /**
     * 毛を縮めるアクション
     */
    virtual void onActionCurlyHair();
    
    /**
     * 毛を抜くアクション
     */
    virtual void onActionLossOfHair();
    
    /**
     * 毛が生えるアクション
     */
    virtual void onActionHairGrows();
    
    /**
     * 毛の種類設定
     * @param stretchLength 伸ばす距離
     */
    virtual void setHairType(HAIR_TYPE value);

    /**
     * 毛の種類取得
     * @param stretchLength 伸ばす距離
     */
    virtual HAIR_TYPE setHairType();
};

#endif /* defined(__the_last_hair2dx__LastHairModel__) */
