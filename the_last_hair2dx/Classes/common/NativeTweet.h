//
//  NativeTweet.h
//  ther_last_hair2dx
//
//  Created by 大原幸夫 on 2014/08/24.
//
//

#ifndef ther_last_hair2dx_NativeTweet_h
#define ther_last_hair2dx_NativeTweet_h

class NativeTweet
{
public:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void openTweetDialog(const char* tweet);
#endif
    
};

#endif
