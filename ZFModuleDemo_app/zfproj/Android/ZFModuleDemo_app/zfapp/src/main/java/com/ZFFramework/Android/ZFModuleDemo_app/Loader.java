package com.ZFFramework.Android.ZFModuleDemo_app;

import com.ZFFramework.Android.ZF_impl.ZFLoader;

public class Loader extends ZFLoader {

    static {
        System.loadLibrary("ZFModuleDemo_app");
    }

}

