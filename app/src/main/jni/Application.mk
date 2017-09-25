# APP_ABI      := armeabi-v7a x86

APP_PLATFORM := android-14
APP_CFLAGS += -Wno-error=format-security
APP_STL := c++_shared
# stlport_shared
APP_CPPFLAGS += -fexceptions
APP_ALLOW_MISSING_DEPS  :=  true

# Note: Uncomment the next line to build with ndk r14b in order to get older Androids support
NDK_TOOLCHAIN_VERSION := clang
                    # 4.9
                    # clang

