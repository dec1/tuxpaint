
#include <string>
#include <vector>
#include <stdexcept>
#include <jc_img_data.h>

#include "CairoSurface.h"

#include "jni.h"

using std::string;
using jc::CairoSurface;



//----------------------------------
JcImgData svg_renderIt(string Xml);
// private
string svgTst();
std::vector<uint32_t>  pixel_data(CairoSurface Cs, const int bytesPerPixel = 4);

