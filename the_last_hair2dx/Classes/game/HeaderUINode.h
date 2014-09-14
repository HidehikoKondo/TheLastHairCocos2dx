//
//  HeaderUINode.h
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#ifndef __ther_last_hair2dx__HeaderUINode__
#define __ther_last_hair2dx__HeaderUINode__

#include "cocos2d.h"
#include "GameRuleManager.h"

/**
 * ヘッダーUIノード
 */
class HeaderUINode : public cocos2d::CCNode
{
protected:
    unsigned long m_Timer;
    unsigned long m_QuestionCount;
    
    cocos2d::CCLabelBMFont * m_QuestionCountString;
    cocos2d::CCLabelBMFont * m_TimeString;
public:
    CREATE_FUNC(HeaderUINode);
    virtual bool init();
    
    /**
     * タイマーをリセットする。
     */
    void resetTimer();

    /**
     * ゲームモードを設定する
     */
    void setMode(GAME_MODE mode);
};

#endif /* defined(__ther_last_hair2dx__HeaderUINode__) */
