//
//  QuestionCounterNode.h
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/08/21.
//
//

#ifndef __ther_last_hair2dx__QuestionCounterNode__
#define __ther_last_hair2dx__QuestionCounterNode__

#include "cocos2d.h"

class QuestionCounterNode : public cocos2d::CCNode
{
protected:
    long m_count;
    cocos2d::CCLabelBMFont * m_CountStrLablel;
    
    cocos2d::CCObject * m_target;
    cocos2d::SEL_CallFunc m_func;
    
    CC_SYNTHESIZE(long, m_CountMax, CountMax);
    
public:
    CREATE_FUNC(QuestionCounterNode);
    QuestionCounterNode();
    virtual ~QuestionCounterNode();
    virtual bool init();
    
    /**
     * カウント最大値に達すると呼ばれる
     */
    void setTarget(CCObject* target,cocos2d::SEL_CallFunc func);
    
    /**
     * カウントアップする
     */
    void countUp();
    
    /**
     * カウンターをリセットする
     */
    void resetCounter();

    /**
     * カウンターの数値を取得
     */
    long getCounterValue();
};

#endif /* defined(__ther_last_hair2dx__QuestionCounterNode__) */
