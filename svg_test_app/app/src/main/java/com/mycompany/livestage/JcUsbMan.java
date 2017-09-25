package com.mycompany.livestage;


import android.content.Context;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.util.Log;

import java.util.HashMap;
import java.util.Set;

// https://developer.android.com/guide/topics/connectivity/usb/host.html
// https://developer.android.com/reference/android/hardware/usb/package-summary.html
//-----------------------------------------------------------
public class JcUsbMan
{
    static boolean chris = true;

    protected JcMan _JcMan;
    public JcMan jcMan() { return _JcMan; }
    public JcActivityMain activityMain(){ return jcMan() != null ? jcMan().activityMain() : null;}

    //-----------------------------------------------------
    JcUsbMan(JcMan Jm)
    {
        _JcMan = Jm;
    }
    //------------------------------------------------
    static void logIt(String Mesg)
    {
        Log.e("Jc_Livestage", "...... " + Mesg);
    }
    //--------------------------------------------

    // Vendor and Product ids for jenetric scanners
    final static int VENDOR_ID  = 0x152a;  // 5418
    final static int PRODUCT_ID = 0x85c0;  // 34240
    //------------------------------
    static final String MY_USB_PERMISSION = "me_o_my_usb_permision";  // actual value doesn't matter
    //----------------------------------------------------------------------
    //----------------------------------------------------------------------
    static  BroadcastReceiver usbReceiver = new BroadcastReceiver() {

        public void onReceive(Context Ctx, Intent intent) {
            logIt("usbReceiver =    - begin ");

            String action = intent.getAction();
            if (MY_USB_PERMISSION.equals(action)) {
                synchronized (this)
                {
                    UsbDevice device = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);
                    boolean extra = intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false);

                    if(device == null || !extra)
                    {
                        logIt("Usb Error: couldnt get permission to device " );
                        return;
                    }

                    JcUsbMan.onPermisionUsb(Ctx, device);

                }
            }
        }
    };
    //----------------------------------------------------------------------
    //-------------------------------------------------------------------
    private static UsbManager _UsbMan = null;
    //---------------------------------------
    public static UsbManager usbMan(Context Ctx)
    {
        if(_UsbMan != null)
            return _UsbMan;

        UsbManager UsbMan = (UsbManager) Ctx.getSystemService(Ctx.USB_SERVICE);
        if (UsbMan == null)
            logIt("Usb Error: unable to get UsbManager." );

        _UsbMan = UsbMan;
        return _UsbMan;

    }
//    //-------------------------------------
//    static public void onImageScanned(int[] data, int w, int h)
//    {
//      //  JcActivityMain Am =  activityMain();
//      //  if(Am != null)
//      //      Am.cbOnImageScanned(data, w, h);
//        JcNativeMan.onImageReady(data, w, h);
//      int halt =1;
//    }
    //-------------------------------------------------------------------
    public static void onPermisionUsb(Context Ctx, UsbDevice Dev)
    {
        UsbManager UsbMan = usbMan(Ctx);

        String DevPath = Dev.getDeviceName();
        if (DevPath == null || DevPath.isEmpty())
        {
            logIt("Usb Error: usb device.getDeviceName() failed" );
            return;
        }


        UsbDeviceConnection Conn = UsbMan.openDevice(Dev);
        if (Conn == null)
        {
            logIt("Usb Error: usbManager.openDevice() failed");
            return;
        }

        int fd = Conn.getFileDescriptor();
        if (fd < 0)
        {
            logIt("Usb Error: unable to get getFileDescriptor.");
            return;
        }

        String StrDevInfo = "Got Permision to use USB Device: " + "VendorId: " + Dev.getVendorId()  + ", ProductId: " + Dev.getProductId() + ", DevPath: " + DevPath + ", fileDesc: " + fd ;


        logIt(StrDevInfo);

        onPermisionUsb(DevPath, fd);


    }
    //-------------------------------------------------------------------
    public static void onPermisionUsb(String DevPath, int fd)
    {

    }
    //----------------------------------------
    public static UsbDevice getDevice(Context Ctx)
    {

        UsbDevice Ret = null;

        UsbManager UsbMan = usbMan(Ctx);
        HashMap<String, UsbDevice> DevsByName = UsbMan.getDeviceList();

        Set<String> Keys = DevsByName.keySet();
        for(String Key : Keys)
        {
            UsbDevice Dev = DevsByName.get(Key);

            if(Dev == null)
                continue;

            int vid = Dev.getVendorId();
            int pid = Dev.getProductId();

            logIt("Vendor_ID = " + vid + ", " + "Product_ID = " + pid + ", Name = " + Key);


            if (Dev.getVendorId() == VENDOR_ID  && Dev.getProductId() == PRODUCT_ID)
            {

                Ret = Dev;
                logIt("....found our scanner");

            }
        }


        return Ret;

    }
    //-------------------------------------------------------------------
    public static void doIt(Context Ctx)
    {

        UsbDevice Dev = getDevice(Ctx);
        if(Dev == null)
        {
            logIt("Usb Error: couldn't find our scanner");
            return;
        }

        // register callback for when permission to use usbDev granted
        PendingIntent Intent = PendingIntent.getBroadcast(Ctx, 0, new Intent(MY_USB_PERMISSION), 0);
        IntentFilter filter = new IntentFilter(MY_USB_PERMISSION);
        Ctx.registerReceiver(usbReceiver, filter);

        // request permission to use usbDev
        UsbManager UsbMan = usbMan(Ctx);
        UsbMan.requestPermission(Dev, Intent);



    }
}

