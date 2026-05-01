package com.ZFFramework.ZFModuleDemo_app;

import android.app.Application;

public class ZFApplication extends Application {
    static {
        System.loadLibrary("ZFModuleDemo_app");
    }
}
