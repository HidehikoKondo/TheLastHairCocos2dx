
#include "NativeCodeAdmobJni.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

// CLASS_NAMEの部分はJavaのクラス名となりますので、
// <スラッシュ区切りのpkgname>/NativeCodeAst のようにします
#define  CLASS_NAME "net/udonko/thelasthair/the_last_hair"



void NativeCodeAdmobJni::showInterstitialJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showInterstitialJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeCodeAdmobJni::loadInterstitialJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loadInterstitialJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
