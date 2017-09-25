
#pragma once


#include <jni.h>
#include <string>
#include <memory>
#include <string>


#include <jc_img_data.h>

class JcJniEnv;

//-------------------------
class JcJniMan
{

public:

    // First Jni Method called .. at startup.. initialize Jvm etc
    static jint onLoad(JavaVM *Jvm);

    static int jniVersion(){ return JNI_VERSION_1_6;}

    // get a Java class from c++ (Thread Safe - even if called in thread created by c++)
    static jclass findClass(const char* name);

    // Unlike the JNIEnv pointer, the JavaVM pointer remains valid across multiple threads so it can be cached in a global variable.
    static JavaVM * jvm(){ return _Jvm;}



    static JNIEnv *getEnv();

    static void checkException();
    //static bool testJvm();

    static bool uiShowText(std::string Str, JNIEnv *Env = 0);
    static bool uiShowImg(JNIEnv *Env, JcImgData Id);
    


private:
    static JavaVM * _Jvm;
    static jobject _ClassLoader;
    static jmethodID _FindClassMethod;







};


