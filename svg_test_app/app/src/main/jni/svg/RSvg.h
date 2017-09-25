#pragma once

#include "CairoDevice.h"
#include "glib/glib.h"
#include "rsvg.h"
#include "rsvg-cairo.h"
#include <stdexcept>



namespace jc
{

    class RSvg
    {
    public:
        ///  Initializes rsvg library
        static void  init()
        {
            //::rsvg_init();      //  deprecated, TODO: use ::g_type_init() instead
            // ::g_type_init();
            //::gtk_init( argc, argv );
        }
        //------------------------------------------------------------
        ///  De-initializes rsvg library
        static void  unInit()
        {
            // ::rsvg_term();      //  deprecated?
        }
        //------------------------------------------------------------
    public:
        RSvg() = delete;
        GError * Err = 0;
        //------------------------------------------------------------
        ///  Loads SVG file into renderer
        RSvg( const std::string& filePath )
            : m_renderer( ::rsvg_handle_new_from_file(filePath.c_str(), nullptr) )  //  TODO: GError
        {
            if( !m_renderer ) { throw std::runtime_error("rsvg_handle_new_from_file(std::string&) failed"); }

            ::rsvg_handle_get_dimensions(m_renderer, &m_dimensions);
        }


        //------------------------------------------------------------
        ///  Loads SVG from memory into renderer
        RSvg( const std::vector<unsigned char>& svgData )
            : m_renderer( ::rsvg_handle_new_from_data(&(svgData.front()), svgData.size(), &Err) )    //  TODO: GError
        {



            string data(svgData.begin(), svgData.end());


            if( !m_renderer )
            {
                string str = "RSvg(vector) :m_renderer   failed: ";
                str += Err->message;
                str += " svgData = ";


                str += data;

                throw std::runtime_error(str);
            }
            else
            {

                std::cerr << "---- RSvg(vector)  :m_renderer   ok---------------- ";
               // std::cerr<<" svgData = " << data;
            }

            ::rsvg_handle_get_dimensions(m_renderer, &m_dimensions);
        }
        //------------------------------------------------------------
        ~RSvg()
        {
          //  ::rsvg_handle_free( m_renderer );
            ::g_object_unref( m_renderer );
        }
        //------------------------------------------------------------
        int  width() const
        {
            return m_dimensions.width;
        }
        //------------------------------------------------------------
        int  height() const
        {
            return m_dimensions.height;
        }
        //------------------------------------------------------------
        ///  Renders a drawing element (or all if nullptr) to a given device
        void  render( CairoDevice& device, const char* elementId=nullptr )
        {
            const gboolean  renderOk = ::rsvg_handle_render_cairo_sub(m_renderer, device, elementId);
            if( !renderOk ) { throw std::runtime_error("rsvg_handle_render_cairo_sub() failed"); }
        }
        //------------------------------------------------------------
    private:
        ::RsvgHandle*           m_renderer;
        ::RsvgDimensionData     m_dimensions;
    };  //  class RSvg

}   //  namespace jc
