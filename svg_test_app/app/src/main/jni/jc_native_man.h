

#include <jni.h>
#include <string>

//
// .cpp contains implementations of (native) functions declared in "JcNativeMan.java"
//  .. no further declarations necessary here

class JcNativeMan
{

public:
    //static  bool    registerJvm (JNIEnv *Env);
    //static  void    setJvm (JavaVM * Jvm);
    static  bool    threadTst (JNIEnv *Env, jclass Cls);

    static  bool    scan       (JNIEnv *Env, jclass Cls, jstring DevPath, int fileDesc);
    static  bool    streamStart(JNIEnv *Env, jclass Cls, jstring DevPath, int fileDesc);
    static  bool    scanChris  (JNIEnv *Env, jclass Cls, jstring DevPath, int fileDesc);

    static  bool    streamStop (JNIEnv *Env, jclass Cls);

    static  bool    renderIt    (JNIEnv *Env, jclass Cls, jstring XmlStr);
    static  jstring infoStr     (JNIEnv *Env, jclass Cls, jstring StrIn, int num);
    static  void    chessTst    (JNIEnv *Env, jclass Cls, int blockSize);
    static  void    imgTst      (JNIEnv *Env, jclass Cls, jintArray dataIn, int w, int h);

    static  bool    fileTst        (JNIEnv *Env, jclass Cls, jstring Path);
    static  bool    iopTst         (JNIEnv *Env, jclass Cls, jstring Path);

};