
package com.jenetric.livestage;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Environment;
import android.os.Handler;
import android.support.v4.util.ArrayMap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Spinner;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import static com.jenetric.livestage.JcImgData.getChessImgData;


//-------------------------------------------------------------------
public class JcActivityMain extends AppCompatActivity
{
    public static JcActivityMain inst(){ return JcMan.inst() != null ? JcMan.inst().activityMain() : null;}
    static boolean svgOn = false;
    //-------------------------------------------------------------------
    //native public boolean  cppScanIt(String StrIn, int num);
   // native public String cppInfoStr(String StrIn, int num);
   // native public boolean  cppRenderIt(String XmlStr);
   // native public void cppImgTst(int[] data, int w, int h);
   // native public void cppChessTst(int blockSize);
    //-------------------------------------

    protected String svgFile() { return "top_correction_pressure_left_hand.svg"; } //"Rect.svg";} //  "top_correction_pressure_left_hand.svg";}


    Button _Butt1;
        Button butt1(){ return _Butt1;}
    Button _Butt2;
        Button butt2(){ return _Butt2;}

    TextView _Tv;
    TextView tv(){ return _Tv;}

    ImageView _Iv;
    ImageView iv(){ return _Iv;}

    JcImgData _ImgData;

    Bitmap Bm;
    BitmapDrawable Bd;

    Spinner _SpinnerFnCall;
    Spinner spinnerFnCall(){ return _SpinnerFnCall;}
    public enum FnCall
    {
        Top_Corr_1("top_correction_pressure_left_hand"),
        Top_Corr_2("top_correction_left_hand_spread"),
        Top_Corr_3("top_correction_pressure_left_hand"),

        Bot_Roll_1("bottom_rolled_finger_ended_error"),
        Bot_Roll_2("bottom_rolled_finger_error_slowdown"),
        Bot_Roll_3("bottom_rolled_finger_error_speedup"),

        Circle("Circle"),
        Star("Star"),
        Rect("Rect"),

        None("None");

        FnCall(String Str){ Name = Str;}
        public String Name;
    }

    //--------------------------------------------------------------------


    static void logIt(String Mesg)
    {
        Log.e("Jc_Livestage", "...... " + Mesg);
    }
    //-----------------------------------------------
    static void loadIt(String LibName)
    {
        logIt("......loading " + LibName);
        System.loadLibrary(LibName);
    }
    //-----------------------------------------
    static
    {

        loadIt("crystax");
        loadIt("gnustl_shared");

//----------------------------------------------------

       // loadIt("dl");
        // loadIt("z");

        loadIt("tuxpaint_iconv");
        loadIt("tuxpaint_png");
        loadIt("tuxpaint_pixman");

        loadIt("tuxpaint_ffi");

        loadIt("SDL2");
        loadIt("tp_android_assets_fopen");
        loadIt("tuxpaint_intl");
        loadIt("tuxpaint_xml2");
        loadIt("tuxpaint_freetype");
        loadIt("tuxpaint_fontconfig");
        loadIt("tuxpaint_cairo");

        loadIt("tuxpaint_glib");

        loadIt("tuxpaint_harfbuzz_ng");
        loadIt("tuxpaint_gdk_pixbuf");
        loadIt("tuxpaint_pango");
        loadIt("tuxpaint_croco");
        loadIt("tuxpaint_rsvg");


//---------------------------------------------------------------------

        loadIt("livestage");

    }
    //-------------------------------------
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        JcMan.inst().setMainActivity(this);

        initLay();



        Resources Res = getResources();

        Bitmap Bm = BitmapFactory.decodeResource(Res, R.mipmap.ic_launcher);
        BitmapDrawable Bd = new BitmapDrawable(Res, Bm);
        _Iv.setImageDrawable(Bd);
        // _Iv.setImageResource(android.R.drawable.ic_dialog_email);

        //onButtClicked_1();
    }
    //-------------------------------------------------
    private void initLay()
    {
        LinearLayout LayMain = new LinearLayout(this);
        LayMain.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT,1));
        LayMain.setGravity(Gravity.CENTER_HORIZONTAL);

        setContentView(LayMain);

        ScrollView _Sv = new ScrollView(this);
        _Sv.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT));
        _Sv.setFillViewport(true);
        LayMain.addView(_Sv);

// Can only add one view to ScrollView so wrap others here
        LinearLayout _Wrap = new LinearLayout(this);
        _Wrap.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT));
        _Wrap.setOrientation(LinearLayout.VERTICAL);
        _Sv.addView(_Wrap);

        _Butt1 = new Button(this);
            _Butt1.setText("Call Chris");
            _Wrap.addView(_Butt1);
            _Butt1.setOnClickListener(new View.OnClickListener() { public void onClick(View v) { onButtClicked_1(); } });

        _Butt2 = new Button(this);
            _Butt2.setText("Render Svg");
            _Wrap.addView(_Butt2);
            _Butt2.setOnClickListener(new View.OnClickListener() { public void onClick(View v) { onButtClicked_2(); } });
//-------------------
        _SpinnerFnCall = initSpinnerFnCall();
            _Wrap.addView(_SpinnerFnCall);
//-------------------

        _Iv = new ImageView(this);
            _Wrap.addView(_Iv);

        _Tv = new TextView(this);
            _Wrap.addView(_Tv);
    }
    //----------------------------------------------------
    public static String currSvg()
    {
        svgOn = !svgOn;
        String File  = svgOn? "top_correction_pressure_left_hand.svg" : "top_correction_pressure_left_hand.svg";
        return File;

    }
//    public Handler mHandler = new Handler() {
//        public void handleMessage(Message msg) {
//            StopWatch.time.setText(formatIntoHHMMSS(elapsedTime)); //this is the textview
//        }
//    };
    //----------------------------------------------------
    private void onButtClicked_1()
    {
//        logIt("onButtClicked_1() - begin ");
//
//        Timer t = new Timer();
////Set the schedule function and rate
//        t.scheduleAtFixedRate(new TimerTask()
//        {
//              @Override
//              public void run()
//              {
//                  String Xml = JcFileMan.readFileAsset(JcMan.inst().activityMain(), currSvg());
//                  JcNativeMan.renderIt(Xml);
//              }
//
//        }, 0, 500);

    }
    //----------------------------------------------------
    private void onButtClicked_2()
    {
        logIt("onButtClicked_2() - begin ");

        String File = new String();
        int selIdx = spinnerFnCall().getSelectedItemPosition();
        switch(fnCallFromIdx(selIdx))
        {
            case Top_Corr_1:
                File = "top_correction_pressure_left_hand.svg";
                break;

            case Top_Corr_2:
                File = "top_correction_left_hand_spread.svg";
                break;

            case Top_Corr_3:
                File = "top_correction_pressure_left_hand.svg";
                break;

            case Bot_Roll_1:
                File = "bottom_rolled_finger_ended_error.svg";
                break;

            case Bot_Roll_2:
                File = "bottom_rolled_finger_error_slowdown.svg";
                break;

            case Bot_Roll_3:
                File = "bottom_rolled_finger_error_speedup.svg";
                break;


            case Circle:
                File = "Circle.svg";
                break;

            case Star:
                File = "Star.svg";
                break;

            case Rect:
                File = "Rect.svg";
                break;

        }

        String Xml = JcFileMan.readFileAsset(this, File);
        JcNativeMan.renderIt(Xml);
    }
    //-----------------------------------------
    public static FnCall fnCallFromIdx(int idx)
    {
        FnCall[] Arr = FnCall.values();
        return ( (idx >= 0) && (idx < Arr.length))? Arr[idx] : FnCall.None;
    }
    //----------------------------------------------
    private Spinner initSpinnerFnCall()
    {


        ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item);
        Spinner Spin = new Spinner(this);
        for (FnCall Fc : FnCall.values())
            if(Fc != FnCall.None)
                dataAdapter.add(Fc.Name);

       /* List<String> categories = new ArrayList<String>();
        categories.add("Automobile");
        categories.add("Business Services");
        categories.add("Computers");
        categories.add("Education");
        categories.add("Personal");
        categories.add("Travel");

        // Creating adapter for spinner
        ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, categories);
*/
        // Drop down layout style - list view with radio button
        dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        // attaching data adapter to spinner
        Spin.setAdapter(dataAdapter);

        return Spin;
    }

    //----------------------------------------------------
    private void setIv(int [] data, int w, int h, Bitmap.Config Bc)
    {
        try {
            Bm = Bitmap.createBitmap(data, w, h, Bc);
        }
        catch(IllegalArgumentException Ex)
        {
            int halt =1;


        }
        catch(ArrayIndexOutOfBoundsException Ex) {
            int halt2 = 1;
        }

      //  Bm.copyPixelsFromBuffer(IntBuffer.wrap(data));

        Bd = new BitmapDrawable(getResources(), Bm);
        _Iv.setImageDrawable(Bd);
    }
    //----------------------------------------------------
    private void setIv(JcImgData Id)
    {

        logIt("setIv() --- id.w=, id.h  " + Id.w + ", " + Id.h);
        if(Id != null)
            setIv(Id.data, Id.w, Id.h, Id.Bc);

        int tst=1;

    }

    //-------------------------------------
    public void cbOnRendered(int [] data, int w, int h)
    {
        logIt("---- cbOnRendered - begin ---- w= "+ w + " ,h= " + h);

        if(iv() == null)
            return;
        else
        {
            logIt("---- cbOnRendered - (1)" );

            _ImgData = new JcImgData(data, w, h, Bitmap.Config.ARGB_8888 );

            logIt("---- cbOnRendered - (2)" );

            // setIv(new MyImgData(data, w, h, Bitmap.Config.ARGB_8888));
            setIv(_ImgData);

            logIt("---- cbOnRendered - (3)" );
        }

        int tst =1;

        logIt("---- cbOnRendered - finished" );

    }
    //--------------------------------------------------------------------------
    //-------------------------------------------------------------------
    void testBitmapChess()
    {
        int blockSize = 50;
       // int w = blockSize*8;
       // int h = blockSize*8;

        JcImgData Id = getChessImgData(blockSize);

        onImageReady(Id.data, Id.w, Id.h );

    }
    //-------------------------------------------------------------------

    //-------------------------------------
    public void onImageReady(int[] data, int w, int h)
    {
        if(iv() == null)
            return;
        else
        {
            _ImgData = new JcImgData(data, w, h, Bitmap.Config.ARGB_8888 );
            setIv(_ImgData);
        }
    }
    //-------------------------------------
    public void onTextReady(String Str)
    {
        if(tv() != null)
            tv().setText(Str + "\n" + tv().getText());

    }
    //-------------------------------------
//    public void setBitmapFromData(int[] data, int w, int h)
//    {
//        if(iv() == null)
//            return;
//        else
//        {
//            _ImgData = new JcImgData(data, w, h, Bitmap.Config.ARGB_8888 );
//            setIv(_ImgData);
//        }
//    }



}
