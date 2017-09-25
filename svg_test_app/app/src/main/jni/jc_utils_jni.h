#pragma once


#include <jni.h>
#include <string>
#include <vector>
#include <iostream>

using string = std::string;
template <typename T> using vector = std::vector<T>;

//-----------------------------------
class JcUtils_Jni
{
public:

//------------------------------------------------------------------


    static jstring jstr_from_str(JNIEnv *Env, string str)  { return jstr_from_cstr_utf8(Env, str.c_str()); }
    static jstring jstr_from_cstr(JNIEnv *Env, const char *str)  { return jstr_from_cstr_utf8(Env, str); }
    static jstring jstr_from_cstr_utf8(JNIEnv *Env, const char *str)  { return jstr_from_cstr_enc(Env, str, "UTF-8"); }
    static jstring jstr_from_cstr_enc(JNIEnv *Env, const char *str, const char* enc);  // use specified encoding eg "UTF-8"

//------------------------------------------------------------------------------

    static std::string cppString(JNIEnv *Env, jstring js)               { return str_from_jstr_utf8(Env, js); }
    static std::string str_from_jstr_utf8(JNIEnv *Env, jstring jstr)    { return str_from_jstr_enc(Env, jstr, "UTF-8"); }
    static std::string str_from_jstr_enc(JNIEnv *Env, jstring jstr, const char * enc);


    static std::vector<jint> vec_from_jintArr(JNIEnv *Env, jintArray arr);
    static jintArray jintArr_from_jintVec(JNIEnv *Env, vector<jint> vec);

    //-----------------------------------------------------------
    static std::vector<jint> jintVec_from_uint32tVec(JNIEnv *Env, vector<uint32_t > vec);
    static jintArray jintArr_from_uint32tVec(JNIEnv *Env, vector<uint32_t > vec);

    // call a Java: Obj.method(vec) , where methodDesc is a "descriptor" for the signature
    // see https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html
    // eg "([III)V" is the method descriptor for a java method of signature "void someMethod(int[], int, int)"
    // Note: For now this is just an illustrative eg. Later can make it more useful by making it a Variadic fn (http://en.cppreference.com/w/cpp/utility/variadic)
    static void passVecToJava(vector<jint>, JNIEnv * Env, jobject Obj, const char * methodName, const char * methodDesc);

};
//------------------------------------------------------------


