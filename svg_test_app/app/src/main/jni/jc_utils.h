#pragma once

#include <vector>
#include <string>
#include <android/log.h>

using string = std::string;

//-----------------------------------------------------
class JcUtils
{
public:

    static void logIt(const char * mesg){ __android_log_print(ANDROID_LOG_ERROR, "jc_livestage: ", mesg);}
    static void logIt(string str){logIt(str.c_str());}
    static void logThread(string str){logIt(str + threadId_Str());}
    static string threadId_Str();
//---------------------------------------------------------------------
    static std::vector<unsigned char>  vecFromStr(string str)
    {
        std::vector<unsigned char> Vec(str.begin(), str.end());
        return Vec;
    }

};

