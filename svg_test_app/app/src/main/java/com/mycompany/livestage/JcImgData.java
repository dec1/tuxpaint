package com.mycompany.livestage;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.util.Arrays;

import static android.graphics.Bitmap.Config.ARGB_8888;


///------------------------------------------------------
class JcImgData
{
    int w;
    int h;
    int[] data;
    Bitmap.Config Bc;
    //--------------------------------------------------------------
    JcImgData(int[] data1, int w1, int h1, Bitmap.Config Bc1)
    {
        w= w1;
        h= h1;
        // data = data1;
        data = Arrays.copyOf (data1, data1.length);
        Bc = Bc1;
    }
    //--------------------------------------------------------------
    JcImgData(byte[] data1, int w1, int h1, Bitmap.Config Bc1)
    {
        this(byteArrToIntArr(data1), w1, h1, Bc1);
    }
    //----------------------------------------------------------
    static int [] byteArrToIntArr(byte [] bytes)
    {

        int size = bytes.length;
        int [] ret = new int [size/4];

        for(int i=0, j=0; i< size-3; ++j, i = i+4)
        {
            byte blue    = bytes[i + 0];
            byte green   = bytes[i + 1];
            byte red     = bytes[i + 2];
            byte alpha   = bytes[i + 3];

            int pixel;
            pixel = red >>0 | green >> 2 | blue >> 3 | alpha >> 4;
            ret[j] = pixel;
        }

        return ret;
    }

    //---------------------------------------------------------
    //-------------------------------------
    static public JcImgData getTstImgData(Context Ctx)
    {


        Resources Res = Ctx.getResources();

        Bitmap Bm = BitmapFactory.decodeResource(Res, R.mipmap.act_new);
        int w = Bm.getWidth();
        int h = Bm.getHeight();

        int[] data = new int[w*h];
        Bm.getPixels(data, 0, w, 0,0 , w,h);


        int[] dataDeep = new int[w*h];
        for(int i=0; i< w*h; ++i)
            dataDeep[i] = data[i];

        JcImgData Ret = new JcImgData(dataDeep, w, h, Bm.getConfig());



        return Ret;

    }
    //-------------------------------------
    static public JcImgData getChessImgData(int blockSize)
    {
        int w = blockSize*8;
        int h = blockSize*8;

        boolean on = false;
        int pixOn =   (0xff) << 24 | (0x00) << 16 | (0x00) << 8 | (0x00);
        int pixOff =  (0xff) << 24 | (0xff) << 16 | (0xff) << 8 | (0xff);


        int[] data = new int[w*h];

        for(int j=0; j<h;++j)
        {
            for (int i = 0; i < w; ++i)
            {
                int idx = i + j * w;

                boolean startBlock = i < blockSize;
                boolean newBlockRow = startBlock && j%blockSize == 0;


                    if ( !newBlockRow && (i % blockSize == 0))
                    {
                            on = !on;
                    }

                data[idx] = on ? pixOn : pixOff;
                int halt = 1;
                ++halt;
            }
        }



        JcImgData Ret = new JcImgData(data, w, h, ARGB_8888);



        return Ret;

    }
    //-------------------------------------------------------------
    //-------------------------------------
    static public JcImgData getTinyImgData(Context Ctx)
    {
        Resources Res = Ctx.getResources();

        Bitmap Bm = BitmapFactory.decodeResource(Res, R.mipmap.tst_tiny);
        int w = Bm.getWidth();
        int h = Bm.getHeight();

        int[] data = new int[w*h];
        Bm.getPixels(data, 0, w, 0,0 , w,h);


        int[] dataDeep = new int[w*h];
        for(int i=0; i< w*h; ++i)
            dataDeep[i] = data[i];

        JcImgData Ret = new JcImgData(dataDeep, w, h, Bm.getConfig());
        return Ret;

    }
}
