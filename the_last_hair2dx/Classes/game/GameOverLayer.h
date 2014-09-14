//
//  GameOverLayer.h
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/08/20.
//
//

#ifndef __ther_last_hair2dx__GameOverLayer__
#define __ther_last_hair2dx__GameOverLayer__

#include "cocos2d.h"
#include "GameRuleManager.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
protected:
    cocos2d::CCSprite * m_GameOverString;
    
    long m_score;
    
public:
    GameOverLayer();
    virtual ~GameOverLayer();
    
    CREATE_FUNC(GameOverLayer);
    virtual bool init();

    /**
     * 記録の登録
     */
    void entoryRecord(GAME_MODE mode,long value);
    
    void moveToTitle();
    
    void onTweet();
    
};
#endif /* defined(__ther_last_hair2dx__GameOverLayer__) */
