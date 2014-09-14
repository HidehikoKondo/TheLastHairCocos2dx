//
//  GameRuleManager.h
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#ifndef __ther_last_hair2dx__GameRuleManager__
#define __ther_last_hair2dx__GameRuleManager__

#include "cocos2d.h"

typedef enum _GAME_MODE
{
    GM_CHALENGE,
    GM_TIME_TRIAL
}GAME_MODE;

class GameRuleManager : public cocos2d::CCObject
{
    //ゲームモード
    CC_SYNTHESIZE(GAME_MODE, m_GameMode, GameMode);
    
public:
    GameRuleManager();
    ~GameRuleManager();
    
    /**
     * シングルトンインスタンス
     */
    static GameRuleManager * getInstance();
    
    /**
     * ランキングの情報を取得する
     */
    cocos2d::CCArray * getRankingList(GAME_MODE mode);

    /**
     * ランキングのスコアを登録する
     */
    void setRankingScore(GAME_MODE mode,long value);
    
    /**
     * ランキングの登録がされるか
     */
    bool isNewRecordScore(GAME_MODE mode,long value);
};

#endif /* defined(__ther_last_hair2dx__GameRuleManager__) */
