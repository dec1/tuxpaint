
# make clean "install" dir
rm -rf ./install
mkdir -p ./install/include
mkdir -p ./install/libs


# copy to "install include" all .h files from the 5 sub dirs 
cd jni
find . \( -type f \( -path '*/cairo-*/*'   -o -path '*/glib-*/*' -o -path '*/*libpng/*' -o -path '*/librsvg-*/*' -o -path '*/gdk-pixbuf-*/*' \) \) -name *.h | xargs -i cp --parents {} ../install/include


# copy libs to install/libs
cd ../libs
find . \( -type f \(    -name '*tuxpaint_xml2*' \
                     -o -name '*tuxpaint_iconv.*' \
                     -o -name '*tuxpaint_fontconfig.*' \
                     -o -name '*tuxpaint_png.*' \
                     -o -name '*tuxpaint_freetype.*' \
                     -o -name '*tuxpaint_pixman.*' \
                     -o -name '*tuxpaint_cairo.*' \
                     -o -name '*tuxpaint_ffi.*' \
                     -o -name '*SDL2.*' \
                     -o -name '*tp_android_assets_fopen.*' \
                     -o -name '*tuxpaint_intl.*' \
                     -o -name '*tuxpaint_glib.*' \
                     -o -name '*tuxpaint_harfbuzz_ng.*' \
                     -o -name '*tuxpaint_gdk_pixbuf.*' \
                     -o -name '*tuxpaint_pango.*' \
                     -o -name '*tuxpaint_croco.*' \
                     -o -name '*tuxpaint_rsvg.*' \
 \) \) \
                      | xargs -i cp --parents {} ../install/libs


