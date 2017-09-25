#pragma once

#include "cairo.h"

#include <stdexcept>



namespace jc
{

    class CairoSurface
    {
    public:
        CairoSurface() = delete;

        CairoSurface( int width, int height )
            : m_surface( ::cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height) )
        {
            if( !m_surface ) { throw std::runtime_error("cairo_image_surface_create() failed"); }
        }

        ~CairoSurface()
        {
            ::cairo_surface_destroy( m_surface );
        }

        operator ::cairo_surface_t*()
        {
            return m_surface;
        }

        int width() const
        {
            return ::cairo_image_surface_get_width(m_surface);
        }

        int height() const
        {
            return ::cairo_image_surface_get_height(m_surface);
        }

        int stride() const
        {
            return ::cairo_image_surface_get_stride(m_surface);
        }

        int content() const
        {
            return ::cairo_surface_get_content(m_surface);
        }

        const unsigned char*  pixels() const
        {
            return ::cairo_image_surface_get_data(m_surface);
        }

    private:
        ::cairo_surface_t*  m_surface;
    };  //  class CairoSurface

}   //  namespace jc
