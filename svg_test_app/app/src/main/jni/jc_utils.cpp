//
// Created by declan on 30/03/17.
//

#include "jc_utils.h"

#include <thread>
#include <sstream>

using std::thread;

//------------------------------------
string JcUtils::threadId_Str()
{

    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    string ret = ss.str();

    return " thread id: " + ret;
}