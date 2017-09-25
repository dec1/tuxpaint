#pragma once

#include "CairoSurface.h"
#include "cairo.h"
#include <stdexcept>



namespace jc
{

    class CairoDevice
    {
    public:
        CairoDevice() = delete;

        CairoDevice( CairoSurface& surface )
            : m_device( ::cairo_create(surface) )
        {
            if( !m_device ) { throw std::runtime_error("cairo_create() failed"); }
        }

        ~CairoDevice()
        {
            ::cairo_destroy( m_device );
        }

        operator cairo_t*()
        {
            return m_device;
        }

    private:
        ::cairo_t*  m_device;
    };  //  class CairoDevice

}   //  namespace jc
