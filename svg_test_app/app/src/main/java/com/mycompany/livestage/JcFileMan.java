package com.mycompany.livestage;


import android.content.Context;
import android.os.Environment;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;

public class JcFileMan
{

    protected JcMan _JcMan;
    public JcMan jcMan() { return _JcMan; }
    //-----------------------------------------------------
    JcFileMan(JcMan Jm)
    {
        _JcMan = Jm;
    }
    //------------------------------------------------------
    //-------------------------------------
    static public String readFileAsset(Context Ctx, String FileName)
    {
        ArrayList<String> Lines = new ArrayList<String>();

        //  if(isDebugVer())
        //     lgMan().logMesg("--- Reading Asset: " + FileName);

        long startTime = System.nanoTime();


        InputStream Fis = null;
        try{
            Fis = Ctx.getAssets().open(FileName);
            BufferedReader r = new BufferedReader(new InputStreamReader(Fis, "UTF-8"));
            String Line;
            while ((Line = r.readLine()) != null)
                Lines.add(Line);


        }
        catch(IOException e)
        {
            JcMan.logError("--- Error while reading Asset: " + FileName);
        }

        finally
        {
            if(Fis != null)
                try {
                    Fis.close();
                    JcMan.logMesg(" closed asset file after reading: " + FileName);
                }
                catch(IOException e) {
                    JcMan.logError("Error... IOException closing asset file: " + FileName);
                    e.printStackTrace();
                }
        }

        // pack lines into single string
        String Ret = new String();

        for(String Line: Lines)
            Ret += Line + "\n";

        return Ret;

    }
    //-------------------------------------------------------------------------------------
    //------------------------------------------
    static boolean writeToFile(String Dir, String File, String Txt)
    {

        java.io.File dir = new File(Dir);
        dir.mkdirs();


        // File F = Environment.getExternalStorageDirectory();

        File file = new File(Dir + "/" + File);

        // Must catch FileNotFoundException and IOException

        boolean ret = false;
        try
        {
            FileOutputStream f = new FileOutputStream(file);
            PrintWriter pw = new PrintWriter(f);
            pw.println(Txt);
            //  pw.println("and the horse you rode in on.");
            pw.flush();
            pw.close();
            f.close();
            ret = true;
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
            JcMan.logError("writeToFile() - File not found");

        }
        catch (IOException e)
        {
            e.printStackTrace();
            JcMan.logError("writeToFile() - I/O exception");
        }

        return ret;
    }
    //---------------------------------------------------
    static public void tstFileAccess(Context Ctx)
    {
        File esp = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DCIM);           //  /storage/emulated/0/DCIM
        File esdow = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);    //  /storage/emulated/0/Documents
        File esr = Environment.getRootDirectory();                                                      //  /system
        File esdata = Environment.getDataDirectory();                                                   //  /data

        File es = Environment.getExternalStorageDirectory();                   //  /storage/emulated/0
        File efd = Ctx.getExternalFilesDir(Environment.DIRECTORY_DOCUMENTS);  //  /storage/emulated/0/Android/data/com.jenetric.livestage/files/Documents


        boolean ret1 = writeToFile(esp.getAbsolutePath(), "tst.txt", "hi from java");
        boolean ret2 = writeToFile(esdow.getAbsolutePath(), "tst.txt", "hi from java");
        boolean ret3 = writeToFile(esr.getAbsolutePath(), "tst.txt", "hi from java");
        boolean ret4 = writeToFile(esdata.getAbsolutePath(), "tst.txt", "hi from java");
        boolean ret5 = writeToFile(es.getAbsolutePath(), "tst.txt", "hi from java");
        boolean ret6 = writeToFile(efd.getAbsolutePath(), "tst.txt", "hi from java");

        boolean ret7 = writeToFile("/storage/emulated/0/Android/data/com.jenetric.livestage", "tst.txt", "hardcoded me");

    }

}
