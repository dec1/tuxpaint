
#include "svgtst.h"
#include "jc_utils_jni.h"


#include "CairoSurface.h"
#include "CairoDevice.h"

#include "PngFile.h"
#include "RSvg.h"

#include <thread>
#include <future>
#include <jc_utils.h>


string svgTst()
{

  //  jc::CairoDevice * Cd = new jc::CairoDevice(0);


    string cairo_ver = cairo_version_string();
    string CairoVer = "\n Cairo version: " +  cairo_ver + "\n\n";

    return CairoVer;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct InitRsvg
{
    InitRsvg()  { jc::RSvg::init(); }
    ~InitRsvg() { jc::RSvg::unInit(); }
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
JcImgData  renderItReally( const string Xml)
{
    InitRsvg  rsvgInit;

     std::cerr << "renderItReally - begin ";
    const std::vector<unsigned char>  svgBuffer = JcUtils::vecFromStr(Xml);

    std::cout << " [parse]" << std::flush;
    jc::RSvg  svgRenderer( svgBuffer );

    std::cout << " [render]" << std::flush;
    jc::CairoSurface  cairoSurface( svgRenderer.width(), svgRenderer.height() );
    jc::CairoDevice  cairoDevice( cairoSurface);

    svgRenderer.render( cairoDevice );

    std::vector<uint32_t> pd = pixel_data(cairoSurface);

    JcImgData Ret;
    Ret.data = pd;

    Ret.w = cairoSurface.width();
    Ret.h = cairoSurface.height();


    std::cerr << "renderItReally - finished ";
    return Ret;

}
//---------------------------------------------------------------------
JcImgData svg_renderIt(string Xml)
{
    std::cerr << "renderIt - begin ";

    JcImgData Ret;

    try
    {

        Ret = renderItReally(Xml);

     //   auto  renderResult = std::async(std::launch::async, renderItReally, Xml);       //  render in separate thread
        //auto  renderResult = std::async(std::launch::deferred, render, svgPath);    //  render in same thread
     //   Ret = renderResult.get();


    }
    catch( const std::exception& err )
    {
        std::cerr << "\n*** error: " << err.what() << std::endl;

    }

    std::cerr << "renderIt - finished ";
    return Ret;
}
//-------------------------------------------------------------------------
std::vector<uint32_t>  pixel_data(CairoSurface Cs, const int bytesPerPixel)
{

    int w = Cs.width();
    int h = Cs.height();
    int stride = Cs.stride();

    const int size = w*h;
    std::vector<uint32_t>  bytes(bytesPerPixel * size);
    //const unsigned char*  rowSurface = Cs.pixels();
    const uint8_t * rowSurface = Cs.pixels();

    for( int y=0; y < Cs.height(); ++y, rowSurface+=Cs.stride() )
    {
        for( int x=0; x < Cs.width(); ++x )
        {
            const unsigned char  blue   = rowSurface [4*x + 0];
            const unsigned char  green  = rowSurface [4*x + 1];
            const unsigned char  red    = rowSurface [4*x + 2];
            const unsigned char  alpha  = rowSurface [4*x + 3] ;    //  ignored

            int tst = y*h + (bytesPerPixel*x + 0);

            bytes[bytesPerPixel*(y*w + x) + 0] = red;
            bytes[bytesPerPixel*(y*w + x) + 1] = green;
            bytes[bytesPerPixel*(y*w + x) + 2] = blue;
            bytes[bytesPerPixel*(y*w + x) + 3] = alpha;
        }

    }

    // create an int for each pixel (ie each byte of int ~ a byte: argb)
    std::vector<uint32_t> ret;
    for( int i =0; i< bytes.size(); i=i+4)
    {
        int r = bytes[i];
        int g = bytes[i+1];
        int b = bytes[i+2];
        int a = bytes[i+3];

        int tst = 0xff00;


        // This is the order that Android Bitmap wants the bytes (https://developer.android.com/reference/android/graphics/Color.html)
        int pix =  b|  g<<8  | r <<16 | a<<24;

        ret .push_back(pix);
    }

    return ret;
}
////---------------------------------------------------------------------
//int  doIt( )
//{
//    try
//    {
//        const std::string  svgPath = "Clock.svg";
//
//        auto  renderResult = std::async(std::launch::async, render, svgPath);       //  render in separate thread
//        //auto  renderResult = std::async(std::launch::deferred, render, svgPath);    //  render in same thread
//        renderResult.get();
//
//        std::cout << std::endl;
//
//        return EXIT_SUCCESS;
//    }
//    catch( const std::exception& err )
//    {
//        std::cerr << "\n*** error: " << err.what() << std::endl;
//        return EXIT_FAILURE;
//    }
//}

////-------------------------------------------------------------------------
//std::vector<int>  pixel_data_int(CairoSurface Cs)
//{
//    // num_Ch = 3 for rgb, 4 for rgb
//    const int num_Ch = 4;
//
//    std::vector<int>  rowBuffer( Cs.width() );
//    const unsigned char*  rowSurface = Cs.pixels();
//    for( int y=0; y < Cs.height(); ++y, rowSurface+=Cs.stride() )
//    {
//        for (int x = 0; x < Cs.width(); ++x) {
//            const unsigned char blue    = rowSurface[num_Ch * x + 0];
//            const unsigned char green   = rowSurface[num_Ch * x + 1];
//            const unsigned char red     = rowSurface[num_Ch * x + 2];
//            const unsigned char alpha   = rowSurface[num_Ch * x + 3];
//
//            int pixel;
//            pixel = red | green >> 2 | blue >> 3 | alpha >> 4;
//            rowBuffer.push_back(pixel);
//        }
//    }
//
//    return rowBuffer;
//}
//size_t  streamSize( std::istream& stream )
//{
//    assert( stream.good() );
//
//    stream.seekg( 0, stream.end );
//    //const size_t  size = stream.tellg();
//    const std::istream::pos_type  size = stream.tellg();
//    if( size == std::istream::pos_type(-1) ) { throw std::runtime_error(std::string(__FUNCTION__)+"(): unexpected stream size"); }
//    assert( size >= 0 );
//    stream.seekg( 0, stream.beg );
//
//    return static_cast<size_t>(size);
//}
////---------------------------------------------------------------------
//std::vector<unsigned char>  loadSvg( const std::string& svgPath )
//{
//    std::ifstream  svgStream( svgPath, std::ifstream::binary );
//    if( !svgStream.good() ) { throw std::runtime_error( std::string(__FUNCTION__)+"(): failed to open \""+svgPath+"\"" ); }
//
//    std::vector<unsigned char>  svgBuffer( streamSize(svgStream) );
//    svgStream.read( reinterpret_cast<char*>(&(svgBuffer.front())), svgBuffer.size() );
//    if( !svgStream.good() ) { throw std::runtime_error( std::string(__FUNCTION__)+"(): failed to read \""+svgPath+"\"" ); }
//
//    return svgBuffer;
//}
////---------------------------------------------------------------------
//void  render( const std::string& svgPath )
//{
//    InitRsvg  rsvgInit;
//
//    std::cout << "\"" << svgPath << "\" ..." << std::flush;
//    // OutputDebugStringA( ("\"" + svgPath + "\":\n").c_str() );
//
//
//    std::cout << " [load]" << std::flush;
//    const std::vector<unsigned char>  svgBuffer = loadSvg(svgPath);
//
//    std::cout << " [parse]" << std::flush;
//    jc::RSvg  svgRenderer( svgBuffer );
//
//    std::cout << " [render]" << std::flush;
//    jc::CairoSurface  cairoSurface( svgRenderer.width(), svgRenderer.height() );
//    jc::CairoDevice  cairoDevice( cairoSurface);
//
//    svgRenderer.render( cairoDevice );
//
//    std::vector<jint> pd = pixel_data(cairoSurface);
//    //std::cout << " [save]" << std::flush;
//    //jc::PngFile(svgPath + ".png").save(cairoImage);
//
//    //std::cout << std::endl;
//}
