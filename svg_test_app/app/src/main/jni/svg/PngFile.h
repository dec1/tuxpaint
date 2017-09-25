#pragma once

#include "CairoSurface.h"
#include "png.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

#include <zconf.h>


namespace jc
{

    class PngFile
    {
    public:
        PngFile() = delete;
        //------------------------------------------------------------
        PngFile( const std::string& filePath )
            : m_filePath(filePath)
            , m_png(nullptr)
            , m_info(nullptr)
        {
            m_png = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, 
                                              (::png_voidp)this, 
                                              &PngFile::onError, 
                                              &PngFile::onWarning
                                             );
            if( !m_png )
            {
                throw std::runtime_error("png_create_write_struct() failed");
            }

            m_info = ::png_create_info_struct(m_png);
            if( !m_info )
            {
                ::png_destroy_write_struct( &m_png, (png_infopp)nullptr );
                throw std::runtime_error("png_create_info_struct() failed");
            }

        }
        //------------------------------------------------------------
        ~PngFile()
        {
            ::png_destroy_write_struct(&m_png, &m_info);
        }
        //------------------------------------------------------------
        void save( const CairoSurface& cairoSurface )
        {
            //if( setjmp(png_jmpbuf(m_png)) )
            //{
            //    assert( false );    //  TODO: refine error handling
            //}

            std::ofstream  ofs( m_filePath.c_str(), std::ios::binary );
            assert( ofs.good() );
            ::png_set_write_fn( m_png, static_cast<voidp>(&ofs), 
                                &PngFile::onWriteData, &PngFile::onFlushData
                              );

            assert( cairoSurface.content() == CAIRO_CONTENT_COLOR_ALPHA );
            ::png_set_IHDR( m_png, m_info, 
                            cairoSurface.width(), cairoSurface.height(), 8, PNG_COLOR_TYPE_RGB_ALPHA, 
                            PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT 
                          );
            ::png_set_sRGB_gAMA_and_cHRM( m_png, m_info, PNG_INFO_sRGB );

            std::vector<::png_bytep>  rowPointers( cairoSurface.height() );
            ::png_bytep  currentRow = const_cast<unsigned char*>( cairoSurface.pixels() );
            for( auto& rp : rowPointers )
            {
                rp = currentRow;
                currentRow += cairoSurface.stride();
            }
            ::png_set_rows( m_png, m_info, &(rowPointers.front()) );

            ::png_write_png( m_png, m_info, PNG_TRANSFORM_BGR, nullptr );
        }
        //------------------------------------------------------------
    private:
#if( PNG_LIBPNG_VER_DLLNUM == 14 )
        static void  onError()
        {
            throw std::runtime_error("(unspecified libpng14 error)");
        }
        //------------------------------------------------------------
        static void  onWarning()
        {
            std::cout << "(unspecified libpng14 warning)" << std::endl;
        }
        //------------------------------------------------------------
#else
        static void  onError(::png_structp png_ptr, ::png_const_charp error_msg)
        {
            throw std::runtime_error(error_msg);
        }
        //------------------------------------------------------------
        static void  onWarning(::png_structp png_ptr, ::png_const_charp warning_msg)
        {
            std::cout << "libpng warning: " << warning_msg << std::endl;
        }
        //------------------------------------------------------------
#endif

        static void  onWriteData(::png_structp png_ptr, ::png_bytep data, ::png_size_t length)
        {
            std::ofstream*  pOfs = static_cast<std::ofstream*>( ::png_get_io_ptr(png_ptr) );
            assert( pOfs != nullptr );

            pOfs->write( reinterpret_cast<char*>(data), length );
            if( !pOfs->good() )
            {
                ::png_error(png_ptr, "failed writing to file");
            }
        }
        //------------------------------------------------------------
        static void  onFlushData(::png_structp png_ptr)
        {
            std::ofstream*  pOfs = static_cast<std::ofstream*>( ::png_get_io_ptr(png_ptr) );
            assert( pOfs != nullptr );

            pOfs->flush();
            if( !pOfs->good() )
            {
                ::png_error(png_ptr, "failed flushing to file");
            }
        }
        //------------------------------------------------------------

    private:
        const std::string   m_filePath;
        ::png_structp       m_png;
        ::png_infop         m_info;
    };  //  class PngFile

}   //  namespace jc
