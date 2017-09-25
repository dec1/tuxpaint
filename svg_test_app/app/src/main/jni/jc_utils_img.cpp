//
// Created by declan on 30/03/17.
//

#include "jc_utils_img.h"

//--------------------------------------------------------------------------------
int32_t JcUtils_Img::bitmapPixel(int red, int green, int blue, int alpha)
{
    int pix = blue | green << 8 | red << 16 | alpha << 24;
    return pix;
}
//--------------------------------------------------------------------------------
