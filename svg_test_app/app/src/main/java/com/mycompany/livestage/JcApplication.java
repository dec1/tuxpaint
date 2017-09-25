package com.mycompany.livestage;

import android.app.Application;
import android.content.Context;
import android.util.Log;

import com.mycompany.livestage.JcMan;


public class JcApplication extends Application
{
    private static Context _Context;
    public static Context getContext(){ return _Context;}

    @Override
    public void onCreate()
    {
        super.onCreate();
        _Context = getApplicationContext();

        JcMan.inst().setApp(this);
    }
}

