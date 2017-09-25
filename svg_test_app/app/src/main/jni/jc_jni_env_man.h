#pragma once

#include <jni.h>



class JcJniEnv;

/// Env ~ java thread
//-----------------------------------------------
// Wrapper for calls to getEnv()
// returns current Env if there is one (ie on main/java thread)

// otherwise creates a new JNIEnv* and attaches it to a new Java thread
// doing so enables c++ to call Java fns from this thread.
// boost::thread_specific_ptr and JcJniEnv  are instrumental in this bookkeeping
// thread_specific_ptr ensures ~JcJniEnv() gets called, and ~JcJniEnv() ensures cleanup happens
class JcJniEnvMan
{

public:
    static JNIEnv *getEnv();

};



