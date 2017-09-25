#pragma once


#include <cstdint>

//---------------------------------------
class JcUtils_Img
{

    // returns an int for with rgba vals  in the order that Android Bitmap wants the bytes (https://developer.android.com/reference/android/graphics/Color.html)
    static int32_t bitmapPixel(int red, int green, int blue, int alpha);
};


