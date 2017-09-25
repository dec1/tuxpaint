
#include "jc_jni_env_man.h"
#include "jc_jni_man.h"
#include "jc_utils.h"



//-----------------------------------------------
JNIEnv *JcJniEnvMan::getEnv()
{

    JavaVM * Jvm = JcJniMan::jvm();

    if(!Jvm)
        return nullptr;

    JNIEnv *Ret = nullptr;
    void ** Env_vp = reinterpret_cast<void **>(&Ret);
    int res = Jvm->GetEnv(Env_vp, JcJniMan::jniVersion());

    // only need JcEnv in JNI_EDETACHED case, but have to declare it outside switch
    JcJniEnv * JcEnv = nullptr;

    // jint ver = Ret->GetVersion();

    switch(res)
    {

        case(JNI_OK) :
            // in a thread started by java .. no need to attach (explicitly)
            break;

        case (JNI_EDETACHED):
            JcUtils::logIt("JcJniMan::getEnv() -> in detached native thread");
            break;

        case (JNI_EVERSION):
            JcUtils::logIt("JcJniMan::getEnv() -> Jvm->GetEnv() .. wrong JNI version requested");
            // could try calling again with earlier version
            break;

    }


    return Ret;
}
