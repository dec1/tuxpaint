package com.mycompany.livestage;


public class JcNativeMan
{
// all Java <-> C++ traffic should go through this class


// (1) Java -> C++ (via JcNativeMan.cpp)
//-----------------------------------------------------
// (1a) java (native) wrapper methods. All java code should only call c++ (native) methods through these wrappers.

    // static public boolean   registerJvm()       { return cppRegisterJvm();}
    //  static public boolean   testJvm()           { return cppTestJvm();}



    static public boolean   renderIt(String XmlStr)                    { return cppRenderIt(XmlStr);}
//-----------------------------------------------------


// (1b) Native methods implemented in C++ (JcNativeMan.cpp) - no Java implementation

    // static public native boolean cppRegisterJvm();
    //static public native boolean cppTestJvm();

    static public native boolean cppRenderIt(String XmlStr);

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
// (2) C++ -> Java (Native) Callback Methods
    static public void onImageReady(int[] data, int w, int h) { if (JcActivityMain.inst() != null ) JcActivityMain.inst().onImageReady(data, w, h);}

    static public void onTextReady(String Str) { if (JcActivityMain.inst() != null ) JcActivityMain.inst().onTextReady(Str);}


}
