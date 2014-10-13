
#ifndef NativeCodeAdmob_h
#define NativeCodeAdmob_h

namespace AdmobExt {
    class NativeCodeAdmob {
    public:
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        // 広告表示開始用と、停止用、そして初期化用の3つのメソッドを定義
        static void showInterstitial();
        static void loadInterstitial();
#endif
        
    };
}

#endif