#include "jc_native_man.h"
#include "jc_jni_man.h"

#include <jc_utils_jni.h>
#include <jc_img_data.h>
#include <jc_utils.h>





#include <utility_tst.h>
#include <fstream>

using std::string;

//---------------------------------------------------------------------------------------
#define _comma_ ,
#define MyJni0(Type, Name) JNIEXPORT Type JNICALL Java_com_jenetric_livestage_JcNativeMan_##Name(JNIEnv *Env, jclass Cls)

#define MyJni(Type, Name, Parms) JNIEXPORT Type JNICALL Java_com_jenetric_livestage_JcNativeMan_##Name(JNIEnv *Env, jclass Cls, Parms)
// eg MyJni(bool, cppScanIt, jstring DevPath _comma_ jint fileDesc)
//  ->  JNIEXPORT bool JNICALL Java_com_jenetric_livestage_JcNativeMan_cppScanIt(JNIEnv *Env, jclass Cls, jstring DevPath _comma_ jint fileDesc)

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
/*
JavaVM* gJvm = nullptr;
static jobject gClassLoader;
static jmethodID gFindClassMethod;
//-------------------------------------
JNIEnv* getEnv() {
    JNIEnv *env;
    int status = gJvm->GetEnv((void**)&env, JNI_VERSION_1_6);
    if(status < 0) {
        status = gJvm->AttachCurrentThread(&env, NULL);
        if(status < 0) {
            return nullptr;
        }
    }
    return env;
}
//-----------------------------------------
jclass findClass(const char* name)
{
    jclass cls = static_cast<jclass>(getEnv()->CallObjectMethod(gClassLoader, gFindClassMethod, getEnv()->NewStringUTF(name)));
    return cls;
}
//-----------------------------------------
void tryIt()
{


}*/
//--------------------------------------------------------------
//--------------------------------------------------------------
// Map the "global" C++ implementations of the JcNativeMan.java -> JcNativeMan.cpp
extern "C"
{

    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *Jvm, void *reserved)
    {
        JcJniMan::onLoad(Jvm);
    }

    MyJni(bool, cppRenderIt, jstring XmlStr)
        { return JcNativeMan::renderIt (Env, Cls, XmlStr);}

}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

//void JcNativeMan::setJvm(JavaVM * Jvm)
//{
//    JcJniMan::setJvm(Jvm);
//}
//----------------------------------------------------------
//bool JcNativeMan::registerJvm(JNIEnv *Env)
//{
//    JcJniMan::registerJvm(Env);
//}





#include "svg/svgtst.h"

//----------------------------------------------------------------------
bool JcNativeMan::renderIt(JNIEnv *Env, jclass Cls, jstring XmlStr)
{

    std::cerr << "---- renderSvg  - begin ----------------";

    string str = JcUtils_Jni::str_from_jstr_utf8(Env, XmlStr);
    JcImgData Id = svg_renderIt(str);

    if(Id.isEmpty()) {
        std::cerr << "---- renderSvg - Ret.isEmpty  ----------------";
        return false;

    }

    else
        std::cerr << "---- renderSvg - Ret.isNotEmpty ----------------";


    JcJniMan::uiShowImg(Env, Id);


}






