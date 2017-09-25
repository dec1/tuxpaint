

#include "jc_jni_man.h"
#include "jc_utils_jni.h"
#include "jc_utils.h"
#include "jc_jni_env_man.h"


using std::string;

//-------------------------------------------------
//-------------------------------------------------
JavaVM * JcJniMan::_Jvm = nullptr;
jobject JcJniMan::_ClassLoader = nullptr;
jmethodID JcJniMan::_FindClassMethod=nullptr;
//-------------------------------------------------
//-------------------------------------------------

jint JcJniMan::onLoad(JavaVM *Jvm)
{
    _Jvm = Jvm;

    auto env = getEnv();

    // Needed for FindClass
    // http://yangyingchao.github.io/Android-JNI-FindClass-Error/
    // Solution 2 (Solution 1 doesnt seem t work), with addition of "NewGlobalRef" below

    auto NmClass = env->FindClass("com/jenetric/livestage/JcNativeMan");
    jclass NmClassClass = env->GetObjectClass(NmClass);
    auto classLoaderClass = env->FindClass("java/lang/ClassLoader");
    auto getClassLoaderMethod = env->GetMethodID(NmClassClass, "getClassLoader",
                                                 "()Ljava/lang/ClassLoader;");


    // Strictly speaking would need to call DeleteLocalRef(_ClassLoader), to free when no longer needed
    // ..but will be needed till closing app (at which point it becomes superfluous), so wont bother
    _ClassLoader = env->NewGlobalRef(env->CallObjectMethod(NmClass, getClassLoaderMethod));

    _FindClassMethod = env->GetMethodID(classLoaderClass, "findClass",
                                        "(Ljava/lang/String;)Ljava/lang/Class;");

    return JNI_VERSION_1_6;
}
//-------------------------------------
jclass JcJniMan::findClass(const char* name)
{
    JNIEnv * Env = getEnv();
    jstring methodName = JcUtils_Jni::jstr_from_cstr(Env, name);

    jobject Obj = Env->CallObjectMethod(_ClassLoader, _FindClassMethod, methodName);
    jclass Cls = static_cast<jclass>(Obj);

    Env->DeleteLocalRef(methodName);

    return Cls;
}
//-----------------------------------------------
JNIEnv *JcJniMan::getEnv()
{
    return JcJniEnvMan::getEnv();
}
//-----------------------------------------------
void JcJniMan::checkException()
{
    JNIEnv * Env = getEnv();
    if(!Env)
    {
        JcUtils::logIt("JcJniMan::checkException .. couldnt get Env");
        return;
    }

    if (Env->ExceptionCheck())
        Env->ExceptionDescribe();
}
//-----------------------------------------------
bool JcJniMan::uiShowText(string Str, JNIEnv *Env)
{
    if(!Env)
        Env = getEnv();

    if(!Env)
       return false;

    jstring jstr  = JcUtils_Jni::jstr_from_str(Env, Str);
    jclass Cls = findClass("com/jenetric/livestage/JcNativeMan");


    jmethodID method = Env->GetStaticMethodID(Cls, "onTextReady", "(Ljava/lang/String;)V");
    if(!method)
        return false;

    Env->CallStaticVoidMethod(Cls, method, jstr);


    Env->DeleteLocalRef(jstr);
    Env->DeleteLocalRef(Cls);

    return true;

}

//-----------------------------------------------
bool JcJniMan::uiShowImg(JNIEnv *Env, JcImgData Id)
{
    if(!Env)
        return false;

    jclass Cls = findClass("com/jenetric/livestage/JcNativeMan");
    jmethodID method = Env->GetStaticMethodID (Cls, "onImageReady", "([III)V");
    if(!method)
        return false;

    jintArray  jia  = JcUtils_Jni::jintArr_from_uint32tVec(Env, Id.data);

    Env->CallStaticVoidMethod(Cls, method, jia, Id.w, Id.h);

    Env->DeleteLocalRef(Cls);
    Env->DeleteLocalRef(jia);

    return true;

}

