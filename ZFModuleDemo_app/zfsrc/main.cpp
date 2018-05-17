/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFModuleDemo_lib.h"
#include "ZFImpl/default/ZFImpl_default_ZFModuleDemo_impl.h"

static void myTestCode(void);

ZFMAIN_ENTRY(params)
{
    // TODO: add your code here
    myTestCode();
    return 0;
}

static void myTestCode(void)
{
    zfblockedAlloc(ZFUIWindow, window);
    window->windowShow();

    zfblockedAlloc(ZFUITextView, textView);
    window->childAdd(textView);
    textView->layoutParam()->layoutAlignSet(ZFUIAlign::e_Center);
    textView->textSet(demoFunc());

    zfLogTrimT() << demoFunc();
    zfLogTrimT() << demoFuncFromImpl();
}

