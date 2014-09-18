//
//  TweezeGameScene.h
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/07/06.
//
//

#ifndef __ther_last_hair2dx__TweezeGameScene__
#define __ther_last_hair2dx__TweezeGameScene__

#include "cocos2d.h"
#include "DialogLayer.h"
#include "LastHairModel.h"

#define DEF_MAX_SCORE 999999999

#define DEF_MAX_STAGE (10)
/**
 * ナンバー足しのゲームプレイ
 */
class TweezeGameScene : public cocos2d::CCLayer
{
protected:
    //抜いた本数
    unsigned long m_score;
    
    //お父さん
    cocos2d::CCSprite * m_GroundFother;
    
    //お父さんの毛
    LastHairModel * m_lastHair;
    bool m_lossFlg;
    
    //手
    cocos2d::CCSprite * m_Hand;
    //手の移動量
    float m_handMove;
    
    //抜いた本数ラベル
    cocos2d::CCLabelTTF * m_LossHairCountLabelMain;
    cocos2d::CCLabelTTF * m_LossHairCountLabelSub;
    
    /**
     * コンボヘアーアニメーション
     */
    void onAnimationComboHair();
    
    /**
     * 抜けた毛の本数
     */
    void countUpHair();
    
    /**
     * ラベルの再表示
     */
    void refleshCountLabe();
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    /**
     * コンストラクタ
     */
    TweezeGameScene();
    /**
     * デストラクタ
     */
    virtual ~TweezeGameScene();
    
    CREATE_FUNC(TweezeGameScene);
    
    /**
     * タップ開始
     */
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    /**
     * タップ移動
     */
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    /**
     * タップ終了
     */
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    /**
     * タップキャンセル
     */
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    /**
     * ゲームオーバー
     */
    virtual void showGameOverLayer();
    
};
#endif /* defined(__ther_last_hair2dx__TweezeGameScene__) */
