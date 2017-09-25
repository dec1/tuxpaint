

#include "jc_utils_jni.h"
using std::string;

//------------------------------------------------------------------------------
//jstring JcUtils_Jni::jstr_from_cstr_utf8(JNIEnv *env, const char *str) { return jstr_from_cstr_enc(env, str, "UTF-8"); }
//------------------------------------------------------------------------------
jstring JcUtils_Jni::jstr_from_cstr_enc(JNIEnv *Env, const char *str, const char *enc)
{

    jstring jstr;
    jbyteArray bytes = 0;
    int len;

    if (Env->EnsureLocalCapacity(2) < 0)
        return NULL; // out of memory error


    jclass Class_java_lang_String= Env->FindClass("java/lang/String");
    jmethodID MID_String_init = Env->GetMethodID(Class_java_lang_String, "<init>", "([BLjava/lang/String;)V" );


    len = strlen(str);
    bytes = Env->NewByteArray(len);
    if (bytes != 0)
    {
        Env->SetByteArrayRegion(bytes, 0, len, (jbyte *) str);
        const jstring charsetName = Env->NewStringUTF(enc);

        jstr = static_cast<jstring>( Env->NewObject(Class_java_lang_String, MID_String_init, bytes, charsetName));

        Env->DeleteLocalRef(charsetName);
    }


    Env->DeleteLocalRef(bytes);
    Env->DeleteLocalRef(Class_java_lang_String);

    return jstr;

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//string JcUtils_Jni::str_from_jstr_utf8(JNIEnv *env, jstring jstr)
//------------------------------------------------------------------------------
string JcUtils_Jni::str_from_jstr_enc(JNIEnv *Env, jstring jstr, const char * enc)
{
    jbyteArray bytes = 0;
    jthrowable exc;
    string str;

    if (Env->EnsureLocalCapacity(2) < 0)
        return str; // out of memory error

    jclass Class_java_lang_String= Env->FindClass("java/lang/String");
    jmethodID MID_String_getBytes = Env->GetMethodID(Class_java_lang_String, "getBytes", "(Ljava/lang/String;)[B");


    const jstring charsetName = Env->NewStringUTF(enc);
    jobject ob = Env->CallObjectMethod(jstr, MID_String_getBytes, charsetName);


    bytes = static_cast<jbyteArray>(ob);
    exc = Env->ExceptionOccurred();
    jint len  = -1;
    if (!exc)
    {
        len = Env->GetArrayLength(bytes);

        char * mem = (char *) malloc(len + 1);

        if (mem != 0)
        {
            Env->GetByteArrayRegion(bytes, 0, len, reinterpret_cast<jbyte *> (mem));
            mem[len]=0; // null terminate the string
            str = string(mem);
        }

        free(mem);

    }


    int strlen = str.length();
    if(strlen!= 199) // for "Rect.svg"
        int halt =1;
    //std::cerr<<" ...............str.length() = " <<strlen << " , len = " << len;
    // std::cerr<<" ...............str = " <<str;

    Env->DeleteLocalRef(ob);
    Env->DeleteLocalRef(charsetName);
    //Env->DeleteLocalRef(bytes);
    Env->DeleteLocalRef(Class_java_lang_String);

    return str;

}

//-----------------------------------------------------------
vector<jint> JcUtils_Jni::vec_from_jintArr(JNIEnv *Env, jintArray arr)
{

    int size = Env->GetArrayLength(arr);
    vector<jint> vec(size);
    Env->GetIntArrayRegion(arr, 0, size, vec.data());

    jint buf[size];
    Env->GetIntArrayRegion(arr, 0, size, buf);



    return vec;

}
//-----------------------------------------------------------
vector<jint> JcUtils_Jni::jintVec_from_uint32tVec(JNIEnv *Env, vector<uint32_t > vec)
{
//    return reinterpret_cast<vector<jint>>(vec);
    //return (vector<jint>)(vec);
      vector<jint> ret(vec.size());
      for(int i=0; i<vec.size();++i)
         ret.at(i) = vec.at(i);

        return ret;
}
//-----------------------------------------------------------
jintArray JcUtils_Jni::jintArr_from_uint32tVec(JNIEnv *Env, vector<uint32_t > vec)
{
    return jintArr_from_jintVec(Env, jintVec_from_uint32tVec(Env, vec));
}
//-----------------------------------------------------------
jintArray JcUtils_Jni::jintArr_from_jintVec(JNIEnv *Env, vector<jint> vec)
{
    int size = vec.size();

    jintArray Ret = Env->NewIntArray(size);
    if (!Ret) {
        std::cerr << " couldnt allocate new  jintArray";
        return 0;
    }

    Env->SetIntArrayRegion(Ret, 0, size, vec.data());

    return Ret;
}
//--------------------------------------------------
void JcUtils_Jni::passVecToJava(std::vector<jint> Vec, JNIEnv * Env, jobject Jobj, const char * methodName, const char * methodDesc)
{

    int size = Vec.size();


    // get class (obj) of Java class
    jclass clazz = Env->GetObjectClass(Jobj);

    // Get the method id of the instance method: eg env->GetMethodID(clazz, "cbSetBitmapFromData", "([I)V");
    jmethodID callback = Env->GetMethodID(clazz, methodName, methodDesc);


    jintArray  jarr  = Env->NewIntArray(size);

    Env->SetIntArrayRegion(jarr, 0, size, Vec.data());
    Env->CallVoidMethod(Jobj, callback, jarr);//, w, h);

    Env->ReleaseIntArrayElements(jarr, Vec.data(), 0);

}
