//
//  RunkingScene.h
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#ifndef __ther_last_hair2dx__RunkingScene__
#define __ther_last_hair2dx__RunkingScene__

#include "cocos2d.h"

class RunkingScene : public cocos2d::CCLayer
{
protected:
    cocos2d::CCArray * m_rankingList;
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    
    /**
     * チャレンジモード用のランキング
     */
    virtual void makeChalengeRanking();
    
    /**
     * コンストラクタ
     */
    RunkingScene();
    /**
     * デストラクタ
     */
    ~RunkingScene();
    
    CREATE_FUNC(RunkingScene);
    
    
    void chengeViewChalenge(cocos2d::CCObject sender);
    /**
     * メインメニューに戻る
     */
    void moveToTopScene(cocos2d::CCObject sender);
};

#endif /* defined(__ther_last_hair2dx__RunkingScene__) */
