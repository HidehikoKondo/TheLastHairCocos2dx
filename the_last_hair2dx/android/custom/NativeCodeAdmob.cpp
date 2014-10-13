
#include "NativeCodeAdmob.h"
#include "NativeCodeAdmobJni.h"

namespace AdmobExt
{
    void NativeCodeAdmob::showInterstitial()
    {
        ::NativeCodeAdmobJni::showInterstitialJni();
    }
    
    void NativeCodeAdmob::loadInterstitial()
    {
        ::NativeCodeAdmobJni::loadInterstitialJni();
    }
}