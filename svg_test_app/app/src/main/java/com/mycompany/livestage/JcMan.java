package com.mycompany.livestage;


import android.app.Application;
import android.util.Log;

public class JcMan {

    //---------------------------------------
    static
    {
        //JcNativeMan.registerJvm();
    }
    //--------------------------------------
    private JcFileMan  _FileMan  = new JcFileMan(this);
    private JcUsbMan   _UsbMan   = new JcUsbMan(this);

    public JcFileMan fileMan()  {return _FileMan;}
    public JcUsbMan  usbMan()   {return _UsbMan;}
    //------------------------------------
    static private JcMan _Instance = new JcMan();
    //------------------------------------
    static public  JcMan inst() { return _Instance;}

    //----------------------------------------------------------
    private JcActivityMain _ActivityMain;
    public void setMainActivity(JcActivityMain Av)
    {
        _ActivityMain= Av;
    }
    public JcActivityMain activityMain(){return _ActivityMain;}

    private Application _App;
    public void setApp(Application App){_App= App;}
    public Application app(){return _App;}

    public static boolean isDebugVersion(){ return BuildConfig.DEBUG;}
    //---------------------------------------
    static public void logError(String Mesg){ logMesg("...Jc_Livestage...Error ", Mesg);}
    static public void logMesg(String Mesg){ logMesg("...Jc_Livestage... ", Mesg);}
    static public void logError(String Tag, String Mesg){ Log.e(Tag, Mesg);}

    static public void logMesg(String Tag, String Mesg)
    {
        if(isDebugVersion())
            Log.e(Tag, Mesg);
    }
    //-----------------------------------------------------
}
