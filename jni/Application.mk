APP_ABI      := armeabi armeabi-v7a x86
APP_PLATFORM := android-10
APP_CFLAGS += -Wno-error=format-security
APP_STL := stlport_shared
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -std=c++14
APP_ALLOW_MISSING_DEPS=true

# just for google ndk
#LOCAL_STATIC_LIBRARIES := cpufeatures
